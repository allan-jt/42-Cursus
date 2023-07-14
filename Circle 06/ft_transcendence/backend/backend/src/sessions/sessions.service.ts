import { Injectable } from '@nestjs/common';
import { WsException } from '@nestjs/websockets';
import { GameStatus, Status } from '@prisma/client';
import { AuthService } from 'src/auth/auth.service';
import { UsersService } from 'src/users/users.service';
import { PayloadDTO } from 'src/auth/dto/JWTPayload.dto';
import { LoggedStrategyJWT } from 'src/auth/passport/jwt.logged.strategy';
import { Socket } from 'socket.io';

@Injectable()
export class SessionsService {
  private onlineUsers: Map<string, Socket>;

  private onlineUserIDs: Map<string, number>;
  private onlineSocketIDs: Map<number, string[]>;

  private waitingUserIDs: Map<string, number>;
  private waitingSocketIDs: Map<number, string>;

  private inQueueUserIDs: Map<string, number>;
  private inQueueSocketIDs: Map<number, string>;

  private inGameUserIDs: Map<string, number>;
  private inGameSocketIDs: Map<number, string>;

  constructor(
    private authService: AuthService,
    public usersService: UsersService,
  ) {
    this.onlineUsers = new Map<string, Socket>();

    this.onlineUserIDs = new Map<string, number>();
    this.onlineSocketIDs = new Map<number, string[]>();

    this.waitingUserIDs = new Map<string, number>();
    this.waitingSocketIDs = new Map<number, string>();

    this.inQueueUserIDs = new Map<string, number>();
    this.inQueueSocketIDs = new Map<number, string>();

    this.inGameUserIDs = new Map<string, number>();
    this.inGameSocketIDs = new Map<number, string>();
  }

  async setStatus(status: Status, socket: Socket = undefined) {
    console.log('in sessions status');

    const userID = await this.setStatusGetUserID(
      socket.request,
      status,
      false,
      socket,
    );
    if (userID === undefined) {
      return;
    }

    status === Status.ONLINE
      ? this.setAsOnline(socket.id, userID, socket)
      : this.removeFromOnlineMaps(socket.id, userID);

    console.log('sessions set');
    console.log('SOCKET - ONLINE', this.onlineSocketIDs);
    console.log('USER - ONLINE', this.onlineUserIDs);
  }

  async setGameStatus(
    request: any,
    socketID: string,
    status: GameStatus,
    client: Socket = undefined,
  ) {
    console.log('in game status');

    const userID = await this.setStatusGetUserID(request, status, true, client);
    if (status === GameStatus.AVAILABLE) {
      this.removeFromWaitingMaps(socketID, userID);
      this.removeFromInQueueMaps(socketID, userID);
      this.removeFromInGameMaps(socketID, userID);
    } else if (status === GameStatus.ONGAME) {
      this.setAsInGame(socketID, userID);
    } else if (status === GameStatus.WAITING) {
      this.setAsWaiting(socketID, userID);
    } else {
      this.setAsInQueue(socketID, userID);
    }

    console.log('SOCKET - IN WAITING', this.waitingSocketIDs);
    console.log('USER - IN WAITING', this.waitingUserIDs);
    console.log('SOCKET - IN QUEUE', this.inQueueSocketIDs);
    console.log('USER - IN QUEUE', this.inQueueUserIDs);
    console.log('SOCKET - IN GAME', this.inGameSocketIDs);
    console.log('USER - IN GAME', this.inGameUserIDs);
  }

  async setStatusGetUserID(
    request: any,
    status: Status | GameStatus,
    isGame: boolean,
    client: Socket = undefined,
  ) {
    try {
      const token = LoggedStrategyJWT.extractJWTCookie(request);
      const payload: PayloadDTO =
        await this.authService.cookieService.verifyJWTToken(token);

      const statusUpdate =
        isGame == true
          ? { gameStatus: status }
          : {
              available: await this.getActiveSessionsStatus(
                payload.id,
                status,
                client,
              ),
            };

      if (isGame == true || statusUpdate.available != undefined) {
        await this.authService.userService.setData(payload.id, statusUpdate);
      }

      return payload.id;
    } catch (err) {
      client?.disconnect();
      return undefined;
    }
  }

  async getActiveSessionsStatus(
    userID: number,
    status: Status | GameStatus,
    client: Socket,
  ) {
    if (status == Status.ONLINE) {
      return status;
    }

    const activeSockets = await this.getOnlineSocketID(userID);
    if (activeSockets == undefined || activeSockets.length == 0) {
      return status;
    }

    for (const socket of activeSockets) {
      if (socket != client.id) {
        return undefined;
      }
    }
    return status;
  }

  setAsOnline(socketID: string, userID: number, socket: Socket) {
    this.onlineUserIDs.set(socketID, userID);
    this.addSocketToOnlineMap(socketID, userID);
    this.onlineUsers.set(socketID, socket);
  }

  addSocketToOnlineMap(socketID: string, userID: number) {
    let sockets = this.onlineSocketIDs.get(userID);

    if (sockets !== undefined) {
      sockets.push(socketID);
    } else {
      this.onlineSocketIDs.set(userID, [socketID]);
    }
  }

  setAsWaiting(socketID: string, userID: number) {
    this.waitingUserIDs.set(socketID, userID);
    this.waitingSocketIDs.set(userID, socketID);
  }

  setAsInQueue(socketID: string, userID: number) {
    this.removeFromInGameMaps(socketID, userID);
    this.inQueueUserIDs.set(socketID, userID);
    this.inQueueSocketIDs.set(userID, socketID);
  }

  setAsInGame(socketID: string, userID: number) {
    this.removeFromInQueueMaps(socketID, userID);
    this.inGameUserIDs.set(socketID, userID);
    this.inGameSocketIDs.set(userID, socketID);
  }

  removeFromAllMaps(socketID: string, userID: number) {
    this.removeFromOnlineMaps(socketID, userID);
    this.removeFromWaitingMaps(socketID, userID);
    this.removeFromInQueueMaps(socketID, userID);
    this.removeFromInGameMaps(socketID, userID);
  }

  removeFromOnlineMaps(socketID: string, userID: number) {
    this.onlineUserIDs.delete(socketID);
    this.onlineUsers.delete(socketID);
    this.removeSocketFromOnlineMap(socketID, userID);
  }

  removeSocketFromOnlineMap(socketID: string, userID: number) {
    const sockets = this.onlineSocketIDs.get(userID);
    if (sockets == undefined || sockets.length == 0) {
      return this.onlineSocketIDs.delete(userID);
    }
    const filteredSockets = sockets.filter((sock) => sock !== socketID);
    filteredSockets.length == 0
      ? this.onlineSocketIDs.delete(userID)
      : this.onlineSocketIDs.set(userID, filteredSockets);
  }

  removeFromWaitingMaps(socketID: string, userID: number) {
    this.waitingUserIDs.delete(socketID);
    this.waitingSocketIDs.delete(userID);
  }

  removeFromInQueueMaps(socketID: string, userID: number) {
    this.inQueueUserIDs.delete(socketID);
    this.inQueueSocketIDs.delete(userID);
  }

  removeFromInGameMaps(socketID: string, userID: number) {
    this.inGameUserIDs.delete(socketID);
    this.inGameSocketIDs.delete(userID);
  }

  async getOnlineUserSocket(socketID: string) {
    return this.onlineUsers.get(socketID);
  }

  async getOnlineUserID(socketID: string) {
    return this.onlineUserIDs.get(socketID);
  }

  async getInQueueUserID(socketID: string) {
    return this.inQueueUserIDs.get(socketID);
  }

  async getInGameUserID(socketID: string): Promise<number> {
    return this.inGameUserIDs.get(socketID);
  }

  async getOnlineSocketID(userID: number) {
    return this.onlineSocketIDs.get(userID);
  }

  async getWaitingSocketID(userID: number) {
    return this.waitingSocketIDs.get(userID);
  }

  async getInQueueSocketID(userID: number) {
    return this.inQueueSocketIDs.get(userID);
  }

  async getInGameSocketID(userID: number) {
    return this.inGameSocketIDs.get(userID);
  }
}
