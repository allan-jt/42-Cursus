import { Injectable } from '@nestjs/common';
import { GameStatus, Status, User } from '@prisma/client';
import { UserPrismaService } from '../prisma/user.prisma';
import { Invite, InviteStatus } from './dto/invite.dto';
import { SessionsService } from './sessions.service';
import { Socket } from 'socket.io';

@Injectable()
export class InviteService {
  inviteeList = new Map<string, string[]>();
  constructor(
    private userPrisma: UserPrismaService,
    private sessionsService: SessionsService,
  ) {}

  async getSocketID(userID: number) {
    const userSocketID = await this.sessionsService.getOnlineSocketID(userID);
    return userSocketID;
  }

  async getSockets(userID: number) {
    const userSockets: Socket[] = [];
    const socketIDs: string[] = await this.getSocketID(userID);

    for (const socketID of socketIDs) {
      const socket = await this.sessionsService.getOnlineUserSocket(socketID);
      userSockets.push(socket);
    }

    // const userSocket = await this.sessionsService.getOnlineUserSocket(
    //   await this.getSocketID(userID),
    // );
    return userSockets;
  }

  async startTimer(invitee: User): Promise<void> {
    const sockets = await this.getSockets(invitee.id);
    setTimeout(() => {
      if (this.inviteeList.has(invitee.username)) {
        this.inviteeList.delete(invitee.username);
        for (const socket of sockets) {
          socket.emit('closePopUp');
        }
      }
    }, 5000);
  }

  async sendGameInvite(invite: Invite): Promise<Invite> {
    const inviter: User = await this.validateUser(invite.inviterName, invite);
    const invitee: User = await this.validateUser(invite.inviteeName, invite);

    if (this.inviteeList.has(invitee.username)) {
      invite.status = InviteStatus.invitee_no_available;
      return invite;
    }

    this.inviteeList.set(invitee.username, await this.getSocketID(invitee.id));
    await this.startTimer(invitee);
    if (inviter && invitee && invite.status == InviteStatus.invite_sent) {
      this.emitEvent(inviter, invitee, 'receiveInvite', invite);
    }
    return invite;
  }

  async receiveGameInvite(invite: Invite) {
    const inviter: User = await this.validateUser(invite.inviterName, invite);
    const invitee: User = await this.validateUser(invite.inviteeName, invite);

    if (this.inviteeList.has(invitee.username)) {
      this.inviteeList.delete(invitee.username);
    }

    if (inviter.available != 'ONLINE' || inviter.gameStatus != 'WAITING') {
      console.log('INVITER ISSUE');
      invite.status = InviteStatus.inviter_no_available;
      return invite;
    }

    if (
      invite.status != InviteStatus.response_received &&
      invite.accept != true
    ) {
      this.emitEvent(invitee, inviter, 'inviteResponse', invite);
      return invite;
    }

    const inviteeSockets = await this.getSockets(invitee.id);
    for (const inviteeSocket of inviteeSockets) {
      inviteeSocket.emit('closePopUp');
      inviteeSocket.emit('changeGameType', 'invite');
    }

    return invite;
  }

  async emitEvent(userA: User, userB: User, event: string, invite: Invite) {
    const srcSockets = await this.getSockets(userA.id);
    const destSocketIDs = await this.getSocketID(userB.id);

    for (const srcSocket of srcSockets) {
      for (const destSocketID of destSocketIDs) {
        srcSocket.to(destSocketID).emit(event, invite);
      }
    }
  }

  async validateUser(username: string, invite: Invite): Promise<User> {
    const user: User = await this.userPrisma.getUser({
      username: username,
    });

    if (user === undefined || user === null) {
      invite.status =
        username == invite.inviteeName
          ? InviteStatus.invitee_no_exist
          : InviteStatus.inviter_no_exist;
    } else if (
      user.available == Status.OFFLINE ||
      (user.gameStatus != GameStatus.AVAILABLE &&
        user.gameStatus != GameStatus.WAITING)
    ) {
      invite.status =
        username == invite.inviteeName
          ? InviteStatus.invitee_no_available
          : InviteStatus.inviter_no_available;
    }

    return user;
  }
}
