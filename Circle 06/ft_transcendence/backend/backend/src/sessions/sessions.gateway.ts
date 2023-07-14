import { Injectable, Req, UseGuards } from '@nestjs/common';
import {
  WebSocketGateway,
  OnGatewayConnection,
  OnGatewayDisconnect,
  SubscribeMessage,
  MessageBody,
} from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import { SessionsService } from './sessions.service';
import { Status } from '@prisma/client';
import { LoggedAuthGuard } from 'src/auth/guards/logged.guard';
import { InviteService } from './sessions.invite.service';
import { Invite } from './dto/invite.dto';
import { SocketAuthGuard } from 'src/auth/guards/socket.guard';
import { FriendsService } from 'src/friends/friends.service';

@Injectable()
@WebSocketGateway({
  cors: {
    origin: process.env.FE_URL,
    credentials: true,
  },
  path: '/api/socket.io',
  namespace: 'sessions',
})
export class SessionsGateway
  implements OnGatewayConnection, OnGatewayDisconnect
{
  public constructor(
    private sessionsService: SessionsService,
    private inviteService: InviteService,
    private friendService: FriendsService,
  ) {}

  async handleConnection(socket: Socket) {
    this.sessionsService.setStatus(Status.ONLINE, socket);
  }

  async handleDisconnect(socket: Socket) {
    this.sessionsService.setStatus(Status.OFFLINE, socket);
  }

  @SubscribeMessage('sendInvite')
  @UseGuards(LoggedAuthGuard)
  async sendInvite(@MessageBody('invite') invite: Invite) {
    try {
      this.checkKeys(invite, 'inviterName', 'inviteeName', 'status', 'accept');
      const newInvite = await this.inviteService.sendGameInvite(invite);
      return { invite: newInvite };
    } catch (error) {
      console.log(error);
    }
  }

  @SubscribeMessage('receiveInvite')
  @UseGuards(LoggedAuthGuard)
  async receiveInvite(@MessageBody('invite') invite: Invite) {
    try {
      this.checkKeys(invite, 'inviterName', 'inviteeName', 'status', 'accept');
      const newInvite = await this.inviteService.receiveGameInvite(invite);
      return { invite: newInvite };
    } catch (error) {
      console.log(error);
    }
  }

  @SubscribeMessage('getFriendsStatus')
  @UseGuards(SocketAuthGuard)
  async getFriendsStatus(client: Socket) {
    //console.log(client);
    try {
      const userID = await this.sessionsService.getOnlineUserID(client.id);
      const friends = await this.friendService.getAllFriends(userID);
      client.emit('allFriends', friends);
    } catch (error) {
      console.log('error: ', error);
      client.disconnect();
    }
  }

  @SubscribeMessage('getAllUsers')
  @UseGuards(SocketAuthGuard)
  async getAllUsers(client: Socket) {
    try {
      const userID = await this.sessionsService.getOnlineUserID(client.id); 
      const friends: any = await this.friendService.getAllFriends(userID);
			const friendsIds = friends.map(friend => friend.id);

			const users = await this.sessionsService.usersService.userPrisma.getUsers({
        where: { id: { not: userID, notIn: friendsIds } },
      });
      client.emit('allUsers', users);
    } catch (error) {
      console.log('error: ', error);
      client.disconnect();
    }
  }

  checkKeys(json: any, ...keys: string[]) {
    for (let i = 0; i < keys.length; i++) {
      if (keys[i] in json === false) {
        throw new Error(
          `Invalid payload - Key '${keys[i]}' is missing in the JSON.`,
        );
      }
    }
  }
}
