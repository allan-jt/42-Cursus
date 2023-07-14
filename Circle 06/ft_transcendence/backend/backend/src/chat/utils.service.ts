import { Injectable } from '@nestjs/common';
import { Server, Socket } from 'socket.io';
import { ParticipantService } from './participant.service';
import { ChatService } from './chat.service';
import { UsersService } from 'src/users/users.service';
import { WsException } from '@nestjs/websockets';
import { Channel, Message, Role } from '@prisma/client';
import { SendMessage } from './chat.interface';
import { comparePassword } from 'src/prisma/bcrypt';

@Injectable()
export class UtilsService {
  constructor(
    private readonly participantService: ParticipantService,
    private readonly usersService: UsersService,
    private readonly chatService: ChatService,
  ) {}

  createSocketRoom(
    client: Socket,
    channel: Channel,
    ownerID: number,
    otherUserID: number,
  ): string {
    const roomName = otherUserID
      ? channel.name
      : channel.id.toString();
    client.join(roomName);
    return roomName;
  }

  joinSocketRoom(client: Socket, channel_id: number): string {
    const roomName = channel_id.toString();
    client.join(roomName);
    return roomName;
  }

  leaveSocketRoom(client: Socket, channel_id: number) {
    const roomName = channel_id.toString();
    client.leave(roomName);
  }

  async deleteSocketRoom(server: Server, channel_id: number) {
    server.socketsLeave(channel_id.toString());
  }

  async isUserAllowedToSend(
    user_id: number,
    channel_id: number,
  ): Promise<boolean> {
    const participant = await this.participantService.getParticipant(
      user_id,
      channel_id,
    );
    if (!participant) {
      console.log('User is not in channel');
      return false;
    }
    if (participant.isBanned) {
      console.log('User is banned.');
      return false;
    }
    if (participant.role === Role.INVITED) {
      console.log('User is invited.');
      return false;
    }

    if (participant.isMuted && new Date() > participant.muteFinishAt)
      this.chatService.unmuteUserInChannel(user_id, channel_id);
    else if (participant.isMuted) return false;

    return true;
  }

  async sendMessageInSocketRoom(
    client: Socket,
    server: Server,
    message: Message,
		roomName: string,
  ) {
    const userInfo = await this.usersService.getData(
      message.sender_id,
      'username',
    );
    const payload: SendMessage = {
			id: message.id,
      sender_id: message.sender_id,
      sender_username: userInfo.username.toString(),
      channel_id: message.channel_id,
      messageBody: message.messageBody,
      sentAt: message.createdAt,
    };

    server.to(roomName).emit('messageSent', payload);
  }

  async isRequestorAuthorized(
    client: Socket,
    channel_id: number,
    socketToUserID: Map<string, number>,
  ) {
    const requestor = await this.participantService.getParticipant(
      socketToUserID.get(client.id),
      channel_id,
    );

    if (!requestor) {
      console.log('User is not in channel');
      return false;
    }

    if (
      (await requestor).role !== Role.ADMIN &&
      (await requestor).role !== Role.OWNER
    ) {
      console.log('User is not an admin or owner');
      return false;
    }
    console.log('User has access');
    return true;
  }

  async isRequestorOwner(
    client: Socket,
    channel_id: number,
    socketToUserID: Map<string, number>,
  ): Promise<boolean> {
    const requestor = await this.participantService.getParticipant(
      socketToUserID.get(client.id),
      channel_id,
    );
    if (!requestor) {
      console.log('User is not in channel');
      return false;
    }
    if (requestor.role !== Role.OWNER) {
      console.log(`User ${socketToUserID.get(client.id)} is not an owner`);
      return false;
    }
    return true;
  }

  async isUserInChannel(user_id: number, channel_id: number) {
    const temp = await this.participantService.getParticipant(
      user_id,
      channel_id,
    );
    if (temp) {
      return true;
    }
    return false;
  }

  async isChannelPublic(channel_id: number) {
    const channel = await this.chatService.getChannelByID(channel_id);
    console.log(channel);
    if (channel.isPublic) {
      console.log('Channel is public');
      return true;
    }
    console.log('Channel is private');
    return false;
  }

  async isUserInvited(user_id: number, channel_id: number) {
    const participant = await this.participantService.getParticipant(
      user_id,
      channel_id,
    );
    if (participant) {
      console.log('User is already in channel');
      return true;
    }
    console.log('User is not in channel');
    return false;
  }

  async getChannelPassword(channel_id: number) {
    return (await this.chatService.getChannelByID(channel_id)).password;
  }

  async sendInviteNotification(
    server: Server,
    client: Socket,
    socketToUserID: Map<string, number>,
    user_id: number,
    channel_id: number,
  ) {
    //client is the one who sent the invite
    //user_id is the one who received the invite
    const payload = {
      channel_id: channel_id,
      sender_id: socketToUserID.get(client.id),
      sender_username: await this.usersService.getData(
        socketToUserID.get(client.id),
        'username',
      ),
    };
    server.emit('inviteNotification', payload);
  }

  async handleReconnectingSocketRooms(
    server: Server,
    client: Socket,
    socketToUserID: Map<string, number>,
  ) {
    const user_id = socketToUserID.get(client.id);
    const channels = await this.chatService.getAllJoinedChannels(user_id);
    for (const channel of channels) {
			const roomName = channel.isDirect ? channel.name : channel.id.toString();
			client.join(roomName);
    }
  }

  async verifyChannelPassword(channel_id: number, password: string) {
    const channel = await this.chatService.getChannelByID(channel_id);
    if (!channel) {
      console.log("Channel doesn't exist");
      return false;
    }
    if (!channel.password || channel.password === '') return true;
    if (await comparePassword(password, channel.password)) {
      return true;
    }
    console.log('Wrong password');
    return false;
  }

	checkKeys(json: any, ...keys: string[]) {
		for (let i = 0; i < keys.length; i++) {
			if (keys[i] in json === false) {
				throw new Error(`Invalid payload - Key '${keys[i]}' is missing in the JSON.`);
			}
		}
	}
}
