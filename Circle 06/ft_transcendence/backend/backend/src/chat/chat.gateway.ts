import {
  ConnectedSocket,
  MessageBody,
  SubscribeMessage,
  WebSocketGateway,
  WebSocketServer,
  WsException,
} from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import { ChatService } from './chat.service';
import { Message, Channel, Role } from '@prisma/client';
import { Request, UseGuards } from '@nestjs/common';
import {
  CreateChannelPayload,
  ModifyArrayPayload,
  UpdateChannelNamePayload,
  UpdateChannelPasswordPayload,
  DeleteChannelPayload,
  CreateMessagePayload,
  SendMessage,
  GetMessagesInChannelPayload,
  ChatWithFriend,
} from './chat.interface';
import { UsersService } from 'src/users/users.service';
import { JwtService } from '@nestjs/jwt';
import { ParticipantService } from './participant.service';
import { UtilsService } from './utils.service';
import { join } from 'path';
import { AuthService } from '../auth/auth.service';
import { CookieService } from 'src/cookie/cookie.service';
import { PayloadDTO } from 'src/auth/dto/JWTPayload.dto';
import { channel } from 'diagnostics_channel';
import { Mutex } from 'async-mutex';
import { MessageService } from './message.service';
import { SocketAuthGuard } from 'src/auth/guards/socket.guard';

@WebSocketGateway({
  cors: {
    origin: process.env.FE_URL,
    credentials: true,
  },
  namespace: 'chat',
  path: '/api/socket.io',
})
export class ChatGateway {
  @WebSocketServer()
  server: Server;

  clientConnected: Map<string, Socket> = new Map();
  socketToUserID: Map<string, number> = new Map();
  UserIDtoSocketID: Map<number, string> = new Map();
  constructor(
    private ChatService: ChatService,
    private usersService: UsersService,
    private participantService: ParticipantService,
    private messageService: MessageService,
    private authService: AuthService,
    private utilsService: UtilsService,
    private channelCreationMutex: Mutex,
  ) {}

  async handleConnection(client: Socket) {
		try {
			console.log('Client chat connected: ' + client.id);
			this.clientConnected.set(client.id, client);
			const token = CookieService.extractValueFromCookies(
				client.request,
				'Authorization',
			);
      const payload: PayloadDTO =
			await this.authService.cookieService.verifyJWTToken(token);
      this.socketToUserID.set(client.id, payload.id);
      await this.utilsService.handleReconnectingSocketRooms(
        this.server,
        client,
        this.socketToUserID,
      );
    } catch (err) {
      console.log(err);
      client.disconnect();
    }
  }

  async handleDisconnect(client: Socket) {
		try {
			console.log('Client disconnected: ' + client.id);
			this.UserIDtoSocketID.delete(this.socketToUserID.get(client.id));
			this.clientConnected.delete(client.id);
			this.socketToUserID.delete(client.id);
		} catch (error) {
			console.log(error);
		}
  }

  /* ####################################################################### */
  /* ############################## MESSAGE ################################ */
  /* ####################################################################### */
  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('createMessage')
  async createMessage(client: Socket, payload: CreateMessagePayload) {
		try {
			const tempJSON = JSON.parse(payload.toString());
			this.utilsService.checkKeys(tempJSON, 'channel_id', 'messageBody');
			tempJSON.channel_id = parseInt(tempJSON.channel_id);
			const sender_id: number = this.socketToUserID.get(client.id);
      if (
        (await this.utilsService.isUserAllowedToSend(
          sender_id,
          tempJSON.channel_id,
        )) === false
      ) {
        return;
      }
      const message: Message = await this.messageService.createMessage(
        sender_id,
        tempJSON.channel_id,
        tempJSON.messageBody,
      );
      const channel = await this.ChatService.getChannelByID(
        tempJSON.channel_id,
      );
      const roomName = channel.isDirect ? channel.name : channel.id.toString();
      await this.utilsService.sendMessageInSocketRoom(
        client,
        this.server,
        message,
        roomName,
      );
    } catch (error) {
      console.log('Error creating message:', error);
    }
  }

  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('getMessagesInChannel')
  async getMessagesInChannel(
    client: Socket,
    payload: GetMessagesInChannelPayload,
  ) {
		try {
			const tempJSON = JSON.parse(payload.toString());
			this.utilsService.checkKeys(tempJSON, 'channel_id');
			tempJSON.channel_id = parseInt(tempJSON.channel_id);
			if (await this.utilsService.isUserInChannel(
				this.socketToUserID.get(client.id),
				tempJSON.channel_id
			) === false){
				return;
			}
			if ((await this.participantService.getParticipant(
				this.socketToUserID.get(client.id),
				tempJSON.channel_id
			)).isBanned === true){
				return;
			}
			await this.messageService
				.getAllMessagesInChannel(tempJSON.channel_id)
				.catch((err) => {
					console.log(err);
				})
				.then((messages) => {
					client.emit('messagesInChannel', JSON.stringify(messages));
				});
		} catch (error) {
			console.log(error);
		}
  }

  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('getTopMessagesInChannel')
  async getTopMessagesInChannel(
    client: Socket,
    payload: GetMessagesInChannelPayload,
  ) {
		try {
			const tempJSON = JSON.parse(payload.toString());
			this.utilsService.checkKeys(tempJSON, 'channel_id');
			tempJSON.channel_id = parseInt(tempJSON.channel_id);
			if (await this.utilsService.isUserInChannel(
				this.socketToUserID.get(client.id),
				tempJSON.channel_id
			) === false){
				return;
			}
			if ((await this.participantService.getParticipant(
				this.socketToUserID.get(client.id),
				tempJSON.channel_id
			)).isBanned === true){
				return;
			}
			await this.messageService
				.getAllMessagesInChannel(tempJSON.channel_id)
				.then((messages) => {
					client.emit('messagesInChannel', JSON.stringify(messages));
				});
		} catch (error) {
			console.log(error);
		}
  }

  /* ####################################################################### */
  /* ############################# CHANNELS ################################ */
  /* ####################################################################### */

  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('createChannel')
  async createChannel(client: Socket, payload: any) {
    /*Create the channel in DB*/
    try {
			const tempJSON = JSON.parse(payload.toString());
			this.utilsService.checkKeys(tempJSON, 'name', 'isDirect', 'isPublic');
      const password = 'password' in tempJSON ? tempJSON.password : '';
      const ownerID: number = this.socketToUserID.get(client.id);
      tempJSON.otherUserID = parseInt(tempJSON.otherUserID);
      if (tempJSON.name.length === 0 || tempJSON.name.length > 20) {
        console.log('Channel name is too long or empty');
        return;
      }
      const channel = await this.ChatService.createChannel(
        tempJSON.name,
        ownerID,
        tempJSON.isDirect,
        tempJSON.isPublic,
        password,
      );
      const roomName = this.utilsService.createSocketRoom(
        client,
        channel,
        ownerID,
        tempJSON.otherUserID,
      );
      if (tempJSON.isDirect === true) {
        // if channel is direct, add the other user to it
        await this.ChatService.addUserToChannel(
          tempJSON.otherUserID,
          channel.id,
          Role.MEMBER,
        );
        if (this.UserIDtoSocketID.get(tempJSON.otherUserID))
          this.server.sockets.sockets
            .get(this.UserIDtoSocketID.get(tempJSON.otherUserID))
            .join(roomName); //join the other user to the room
      }
    } catch (error) {
      console.log('Error creating Channel:', error);
    }
    //code the logic to create socket room for the channel and the owner to it
  }

  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('chatWithUser')
  async chatWithUser(client: Socket, payload: ChatWithFriend) {
		try {
      // console.log('!!!!!!!!!!!!!!!!!!!!!! CHATWITHUSER!!!!!!!!!!!!!!!!!')
    	const tempJSON = JSON.parse(payload.toString());
			this.utilsService.checkKeys(tempJSON, 'other_user_id');
			const user_id = this.socketToUserID.get(client.id);
			tempJSON.other_user_id = parseInt(tempJSON.other_user_id);
      await this.channelCreationMutex.acquire();
      // console.log(`${tempJSON.other_user_id} , ${user_id}`)
      var channel = await this.ChatService.getDirectChannelBetweenTwoUsers(
        user_id,
        tempJSON.other_user_id,
      );
      if (!channel) {
        console.log('Channel does not exist');
        const ownerUserInfo = await this.usersService.getData(
          user_id,
          'username',
        );
        const otherUserUserInfo = await this.usersService.getData(
          tempJSON.other_user_id,
          'username',
        );
        // console.log(`${ownerUserInfo.username}+${otherUserUserInfo.username}`);
        const payload: CreateChannelPayload = {
          name: `${ownerUserInfo.username}+${otherUserUserInfo.username}`,
          ownerID: user_id,
          isDirect: true,
          isPublic: false,
          password: '',
          otherUserID: tempJSON.other_user_id.toString(),
        };
        await this.createChannel(client, JSON.stringify(payload));
        channel = await this.ChatService.getDirectChannelBetweenTwoUsers(
          user_id,
          tempJSON.other_user_id,
        );
        // console.log("Created channel !!!!!!!!!!!")
      }
      this.server.to(client.id).emit(
        'chatWithUserRes',
        JSON.stringify({
          channel_id: channel.id,
        }),
      );
      await this.channelCreationMutex.release();
    } catch (error) {
      await this.channelCreationMutex.release();
    }
  }

  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('getAllPublicChannels')
  async getAllPublicChannels(client: Socket) {
    try {
			await this.ChatService.getAllPublicChannels().then((channels) => {
				client.emit('allPublicChannels', JSON.stringify(channels));
			});
		} catch (error) {
			console.log(error);
		}
  }

  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('getAllPublicChannelsNotJoined')
  async getAllPublicChannelsNotJoined(client: Socket) {
		try {
			await this.ChatService.getAllPublicChannelsNotJoined(
				this.socketToUserID.get(client.id),
			).then((channels) => {
				client.emit('allPublicChannelsNotJoined', JSON.stringify(channels));
			});
		} catch (error) {
			console.log(error);
		}
  }

  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('getAllJoinedChannels')
  async getAllJoinedChannels(client: Socket) {
		try {
			const channels = await this.ChatService.getAllJoinedChannels(
				this.socketToUserID.get(client.id),
			).catch((err) => {
				console.log(err);
			});
			client.emit('allJoinedChannels', JSON.stringify(channels));
		} catch (error) {
			console.log(error);
		}
  }

  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('updateChannelPassword')
  async updateChannelPassword(
    client: Socket,
    payload: UpdateChannelPasswordPayload,
  ) {
    try {
    	const tempJSON = JSON.parse(payload.toString());
			this.utilsService.checkKeys(tempJSON, 'channel_id', 'password');
    	tempJSON.channel_id = parseInt(tempJSON.channel_id);
      if (
        !(await this.utilsService.isRequestorOwner(
          client,
          tempJSON.channel_id,
          this.socketToUserID,
        ))
      )
        return;
      await this.ChatService.updateChannelPassword(
        tempJSON.channel_id,
        tempJSON.password,
      );
    } catch (error) {
      console.log('Error updating channel password:', error);
    }
  }

  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('joinChannel')
  async joinChannel(client: Socket, payload: ModifyArrayPayload) {
		try {
			const tempJSON = JSON.parse(payload.toString());
			this.utilsService.checkKeys(tempJSON, 'channel_id');
			tempJSON.channel_id = parseInt(tempJSON.channel_id);
			const user_id: number = this.socketToUserID.get(client.id);
			const password = 'password' in tempJSON ? tempJSON.password : '';
      // if channel is private, check if user is invited
      if (
        (await this.utilsService.isChannelPublic(tempJSON.channel_id)) === false
      ) {
        if (
          (await this.utilsService.isUserInvited(
            user_id,
            tempJSON.channel_id,
          )) === false
        ) {
          console.log('User is not invited');
          return;
        } else {
          await this.ChatService.upgradeUserToMember(
            user_id,
            tempJSON.channel_id,
          );
					this.utilsService.joinSocketRoom(client, tempJSON.channel_id);
          console.log('User upgraded to member');
          return;
        }
      }
      // if channel is protected, check if password is correct
      if (
        !(await this.utilsService.verifyChannelPassword(
          tempJSON.channel_id,
          password,
        ))
      ) {
        return;
      }
      const temp = await this.participantService.getParticipant(
        user_id,
        parseInt(tempJSON.channel_id),
      );
      // if user is already in channel, check if user is banned
      if (temp) {
        if ((await temp).isBanned === true) console.log('User is banned');
        else console.log('User already in channel');
        return;
      }
      await this.ChatService.addUserToChannel(
        user_id,
        parseInt(tempJSON.channel_id),
        Role.MEMBER,
      );
      this.utilsService.joinSocketRoom(client, tempJSON.channel_id);
    } catch (error) {
      console.log('Error adding user to channel:', error);
    }
  }

  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('leaveChannel')
  async leaveChannel(client: Socket, payload: ModifyArrayPayload) {
		try {
			const tempJSON = JSON.parse(payload.toString());
			this.utilsService.checkKeys(tempJSON, 'channel_id');
			tempJSON.channel_id = parseInt(tempJSON.channel_id);
			const user_id: number = this.socketToUserID.get(client.id);
      if (
        !(await this.utilsService.isUserInChannel(user_id, tempJSON.channel_id))
      ) {
        return;
      }
      if (
        await this.utilsService.isRequestorOwner(
          client,
          tempJSON.channel_id,
          this.socketToUserID,
        )
      ) {
        console.log('Owner cant leave channel');
        return;
      }
      await this.ChatService.removeUserFromChannel(
        user_id,
        tempJSON.channel_id,
      );
    } catch (error) {
      console.log('Error removing user from channel:', error);
    }
  }

  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('addAdmin')
  async addAdmin(client: Socket, payload: ModifyArrayPayload) {
		try {
			const tempJSON = JSON.parse(payload.toString());
			this.utilsService.checkKeys(tempJSON, 'user_id', 'channel_id');
			tempJSON.user_id = parseInt(tempJSON.user_id);
			tempJSON.channel_id = parseInt(tempJSON.channel_id);
      if (
        (await this.utilsService.isRequestorOwner(
          client,
          tempJSON.channel_id,
          this.socketToUserID,
        )) === false
      ) {
        return;
      }
      await this.ChatService.makeUserAdminInChannel(
        parseInt(tempJSON.user_id),
        parseInt(tempJSON.channel_id),
      );
    } catch (error) {
      console.log('Error adding user to channel:', error);
    }
  }

  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('removeAdmin')
  async removeAdmin(client: Socket, payload: ModifyArrayPayload) {
		try {
			const tempJSON = JSON.parse(payload.toString());
			this.utilsService.checkKeys(tempJSON, 'user_id', 'channel_id');
			tempJSON.user_id = parseInt(tempJSON.user_id);
			tempJSON.channel_id = parseInt(tempJSON.channel_id);
      if (
        !(await this.utilsService.isRequestorOwner(
          client,
          tempJSON.channel_id,
          this.socketToUserID,
        ))
      )
        return;
      if (
        (await this.utilsService.isUserInChannel(
          tempJSON.user_id,
          tempJSON.channel_id,
        )) === false
      )
        return; //user is not in channel
      if (
        (
          await this.participantService.getParticipant(
            tempJSON.user_id,
            tempJSON.channel_id,
          )
        ).role !== Role.ADMIN
      ) {
        console.log('User is not admin');
        return;
      }
      await this.ChatService.removeUserAdminInChannel(
        tempJSON.user_id,
        tempJSON.channel_id,
      );
    } catch (error) {
      console.log('Error removing user from admins:', error);
    }
  }

  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('banUser')
  async banUser(client: Socket, payload: ModifyArrayPayload) {
		try {
			const tempJSON = JSON.parse(payload.toString());
			this.utilsService.checkKeys(tempJSON, 'user_id', 'channel_id');
			tempJSON.user_id = parseInt(tempJSON.user_id);
			tempJSON.channel_id = parseInt(tempJSON.channel_id);
      if (
        !(await this.utilsService.isRequestorAuthorized(
          client,
          tempJSON.channel_id,
          this.socketToUserID,
        ))
      ) {
        return;
      }
      if (
        (
          await this.participantService.getParticipant(
            tempJSON.user_id,
            tempJSON.channel_id,
          )
        ).role === Role.OWNER
      ) {
        console.log('Cant ban owner');
        return;
      }

      if (
        (
          await this.participantService.getParticipant(
            tempJSON.user_id,
            tempJSON.channel_id,
          )
        ).isBanned === true
      ) {
        console.log('User is already banned');
        return;
      }

      await this.ChatService.banUserFromChannel(
        tempJSON.user_id,
        tempJSON.channel_id,
      );
      this.utilsService.leaveSocketRoom(client, tempJSON.channel_id);
    } catch (error) {
      console.log('Error adding user to channel:', error);
    }
  }

  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('unbanUser')
  async unbanUser(client: Socket, payload: ModifyArrayPayload) {
		try {
			const tempJSON = JSON.parse(payload.toString());
			this.utilsService.checkKeys(tempJSON, 'user_id', 'channel_id');
			tempJSON.user_id = parseInt(tempJSON.user_id);
			tempJSON.channel_id = parseInt(tempJSON.channel_id);
      if (
        !(await this.utilsService.isRequestorAuthorized(
          client,
          tempJSON.channel_id,
          this.socketToUserID,
        ))
      ) {
        return;
      }
      if (
        !(await this.utilsService.isUserInChannel(
          tempJSON.user_id,
          tempJSON.channel_id,
        ))
      ) {
        return;
      }
      if (
        (
          await this.participantService.getParticipant(
            tempJSON.user_id,
            tempJSON.channel_id,
          )
        ).isBanned === false
      ) {
        console.log('User is not banned');
        return;
      }
      await this.ChatService.unbanUserFromChannel(
        tempJSON.user_id,
        tempJSON.channel_id,
      );
      this.utilsService.joinSocketRoom(client, tempJSON.channel_id);
    } catch (error) {
      console.log('Error removing user from banned:', error);
    }
  }

  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('kickUser')
  async kickUser(client: Socket, payload: ModifyArrayPayload) {
		try {
			const tempJSON = JSON.parse(payload.toString());
			this.utilsService.checkKeys(tempJSON, 'user_id', 'channel_id');
			tempJSON.user_id = parseInt(tempJSON.user_id);
			tempJSON.channel_id = parseInt(tempJSON.channel_id);
      if (
        !(await this.utilsService.isRequestorAuthorized(
          client,
          tempJSON.channel_id,
          this.socketToUserID,
        ))
      ) {
        return;
      }
      if (
        (
          await this.participantService.getParticipant(
            tempJSON.user_id,
            tempJSON.channel_id,
          )
        ).role === Role.OWNER
      ) {
        console.log('Cant kick owner');
        return;
      }
      await this.ChatService.removeUserFromChannel(
        tempJSON.user_id,
        tempJSON.channel_id,
      );
    } catch (error) {
      console.log('Error kicking user from channel:', error);
    }
  }

  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('muteUser')
  async muteUser(client: Socket, payload: ModifyArrayPayload) {
		try {
			const tempJSON = JSON.parse(payload.toString());
			this.utilsService.checkKeys(tempJSON, 'user_id', 'channel_id', 'muteDuration');
			tempJSON.user_id = parseInt(tempJSON.user_id);
			tempJSON.channel_id = parseInt(tempJSON.channel_id);
			tempJSON.muteDuration =
			'muteDuration' in tempJSON ? parseInt(tempJSON.muteDuration) : null;
	
			if (!tempJSON || tempJSON.muteDuration <= 0) {
				console.log('Invalid mute duration: ' + tempJSON.muteDuration);
				return;
			}
			if (
        !(await this.utilsService.isRequestorAuthorized(
          client,
          tempJSON.channel_id,
          this.socketToUserID,
        ))
      ) {
        return;
      }
      if (
        (
          await this.participantService.getParticipant(
            tempJSON.user_id,
            tempJSON.channel_id,
          )
        ).role === Role.OWNER
      ) {
        console.log('Cant mute owner');
        return;
      }
      await this.ChatService.muteUserInChannel(
        tempJSON.user_id,
        tempJSON.channel_id,
        tempJSON.muteDuration,
      );
    } catch (error) {
      console.log('Error muting user in channel:', error);
    }
  }

  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('unmuteUser')
  async unmuteUser(client: Socket, payload: ModifyArrayPayload) {
		try {
			const tempJSON = JSON.parse(payload.toString());
			this.utilsService.checkKeys(tempJSON, 'user_id', 'channel_id');
			tempJSON.user_id = parseInt(tempJSON.user_id);
			tempJSON.channel_id = parseInt(tempJSON.channel_id);
      if (
        !(await this.utilsService.isRequestorAuthorized(
          client,
          tempJSON.channel_id,
          this.socketToUserID,
        ))
      ) {
        return;
      }
      if (
        (
          await this.participantService.getParticipant(
            tempJSON.user_id,
            tempJSON.channel_id,
          )
        ).isMuted === false
      ) {
        console.log('User is not muted');
        return;
      }
      await this.ChatService.unmuteUserInChannel(
        tempJSON.user_id,
        tempJSON.channel_id,
      );
    } catch (error) {
      console.log('Error unmuting user in channel:', error);
    }
  }

  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('inviteUser')
  async inviteUser(client: Socket, payload: ModifyArrayPayload) {
		try {
			const tempJSON = JSON.parse(payload.toString());
			this.utilsService.checkKeys(tempJSON, 'user_id', 'channel_id');
			tempJSON.user_id = parseInt(tempJSON.user_id);
			tempJSON.channel_id = parseInt(tempJSON.channel_id);
      if (
        (await this.utilsService.isChannelPublic(tempJSON.channel_id)) === true
      ) {
        console.log("Channel is public (can't invite)");
        return;
      }
      if (
        !(await this.utilsService.isRequestorAuthorized(
          client,
          tempJSON.channel_id,
          this.socketToUserID,
        ))
      ) {
        return;
      }
      if (
        await this.utilsService.isUserInChannel(
          tempJSON.user_id,
          tempJSON.channel_id,
        )
      ) {
        return;
      }
      await this.ChatService.addUserToChannel(
        tempJSON.user_id,
        tempJSON.channel_id,
        Role.INVITED,
      );
      await this.utilsService.sendInviteNotification(
        this.server,
        client,
        this.socketToUserID,
        tempJSON.user_id,
        tempJSON.channel_id,
      );
    } catch (error) {
      console.log('Error inviting user to channel:', error);
    }
  }

  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('uninviteUser')
  async uninviteUser(client: Socket, payload: ModifyArrayPayload) {
		try {
			const tempJSON = JSON.parse(payload.toString());
			this.utilsService.checkKeys(tempJSON, 'user_id', 'channel_id');
			tempJSON.user_id = parseInt(tempJSON.user_id);
			tempJSON.channel_id = parseInt(tempJSON.channel_id);
      if (
        !(await this.utilsService.isRequestorAuthorized(
          client,
          tempJSON.channel_id,
          this.socketToUserID,
        ))
      ) {
        return;
      }
      if (
        !(await this.utilsService.isUserInChannel(
          tempJSON.user_id,
          tempJSON.channel_id,
        ))
      ) {
        return;
      }
      if (
        (
          await this.participantService.getParticipant(
            tempJSON.user_id,
            tempJSON.channel_id,
          )
        ).role !== Role.INVITED
      ) {
        console.log('User is not invited');
        return;
      }
      await this.ChatService.removeUserFromChannel(
        tempJSON.user_id,
        tempJSON.channel_id,
      );
    } catch (error) {
      console.log('Error removing user from invited:', error);
    }
  }

  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('getMyParticipant') //should this be an endpoint?
  async getParticipant(client: Socket, payload: ModifyArrayPayload) {
		try {
			const tempJSON = JSON.parse(payload.toString());
			this.utilsService.checkKeys(tempJSON, 'channel_id');
			tempJSON.channel_id = parseInt(tempJSON.channel_id);
			const user_id: number = this.socketToUserID.get(client.id);
      const participant = await this.participantService.getParticipant(
        user_id,
        tempJSON.channel_id,
      );
      client.emit('myParticipant', JSON.stringify(participant));
    } catch (error) {
      console.log('Error getting participant:', error);
    }
  }

  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('getParticipantsInChannel') //should this be an endpoint?
  async getParticipantsInChannel(client: Socket, payload: ModifyArrayPayload) {
		try {
			const tempJSON = JSON.parse(payload.toString());
			this.utilsService.checkKeys(tempJSON, 'channel_id');
			tempJSON.channel_id = parseInt(tempJSON.channel_id);
      if (
        (await this.ChatService.getChannelByID(tempJSON.channel_id)) === null
      ) {
        return;
      }
			if (await this.utilsService.isUserInChannel(
				this.socketToUserID.get(client.id),
				tempJSON.channel_id
			) === false){
				return;
			}
			if ((await this.participantService.getParticipant(
				this.socketToUserID.get(client.id),
				tempJSON.channel_id
			)).isBanned === true){
				return;
			}
      const participants =
        await this.participantService.getAllParticipantsInChannel(
          tempJSON.channel_id,
        );
      client.emit('participantsInChannel', JSON.stringify(participants));
    } catch (error) {
      console.log('Error getting participants in channel:', error);
    }
  }

  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('deleteChannel')
  async deleteChannel(client: Socket, payload: DeleteChannelPayload) {
    try {
      const tempJSON = JSON.parse(payload.toString());
			this.utilsService.checkKeys(tempJSON, 'channel_id');
      tempJSON.channel_id = parseInt(tempJSON.channel_id);
      if (!(await this.ChatService.getChannelByID(tempJSON.channel_id))) {
        console.log('No channel with that ID');
        return;
      }
      if (
        !(await this.utilsService.isRequestorOwner(
          client,
          tempJSON.channel_id,
          this.socketToUserID,
        ))
      ) {
        return;
      }
      await this.ChatService.deleteChannel(tempJSON.channel_id);
      await this.utilsService.deleteSocketRoom(
        this.server,
        tempJSON.channel_id,
      );
    } catch (error) {
      console.log('Error deleting channel:', error);
    }
  }

  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('getAllChannelsUserIsInvitedTo')
  async getAllChannelsUserIsInvitedTo(client: Socket) {
    try {
    	const user_id: number = this.socketToUserID.get(client.id);
      const channels = await this.ChatService.getAllChannelsUserIsInvitedTo(
        user_id,
      );
      client.emit('allChannelsUserIsInvitedTo', JSON.stringify(channels));
    } catch (error) {
      console.log('Error getting all channels user is invited to:', error);
    }
  }

  @UseGuards(SocketAuthGuard)
  @SubscribeMessage('getAvailableUsersNotInChannel')
  async getAvailableUsersNotInChannel(
    client: Socket,
    payload: ModifyArrayPayload,
  ) {
		try {
    	const tempJSON = JSON.parse(payload.toString());
			this.utilsService.checkKeys(tempJSON, 'channel_id');
			tempJSON.channel_id = parseInt(tempJSON.channel_id);
			if (
				!(await this.utilsService.isRequestorAuthorized(
					client,
					tempJSON.channel_id,
					this.socketToUserID,
				))
			) {
				return;
			}
      const users = await this.ChatService.getAvailableUsersNotInChannel(
        tempJSON.channel_id,
      );
      client.emit('availableUsersNotInChannel', JSON.stringify(users));
    } catch (error) {
      console.log('Error getting available users not in channel:', error);
    }
  }
}
