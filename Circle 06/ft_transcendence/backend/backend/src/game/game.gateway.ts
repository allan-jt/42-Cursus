import {
  WebSocketGateway,
  OnGatewayConnection,
  OnGatewayDisconnect,
  SubscribeMessage,
  MessageBody,
  WebSocketServer,
} from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import { GameController } from './game.controller';
import { GameService } from './game.service';
import { GameDTO } from './dto/game.dto';
import { Injectable, Logger, UseGuards } from '@nestjs/common';
import { SessionsService } from 'src/sessions/sessions.service';
import { BallService } from './game.ball.service';
import { PaddleService } from './game.paddle.service';
import { GameStatus, User } from '@prisma/client';
import { PairedUsers } from './matchmaking/dto/PairedUsers.dto';
import { UserPrismaService } from 'src/prisma/user.prisma';
import { Invite } from 'src/sessions/dto/invite.dto';
import { SocketAuthGuard } from 'src/auth/guards/socket.guard';
import { LoggedStrategyJWT } from 'src/auth/passport/jwt.logged.strategy';
import { PayloadDTO } from 'src/auth/dto/JWTPayload.dto';
import { AuthService } from 'src/auth/auth.service';

@WebSocketGateway({
  cors: {
    origin: process.env.FE_URL,
    credentials: true,
  },
  path: '/api/socket.io',
  namespace: 'game',
})
@Injectable()
export class GameGateway implements OnGatewayConnection, OnGatewayDisconnect {
  @WebSocketServer()
  server: Server;

  // declaring variable to store current GameDTO about ongoing games
  gameMap: Map<string, GameDTO> = new Map();
  clientSocket = new Map<string, Socket>();
  inviteSocket = new Map<string, Socket>();

  public constructor(
    private gameController: GameController,
    private gameService: GameService,
    private ballService: BallService,
    private paddleService: PaddleService,
    private sessionsService: SessionsService,
    private authService: AuthService,
    private userPrisma: UserPrismaService,
  ) {}

  async updateGameStatus(socket: Socket, status: GameStatus) {
    await this.sessionsService.setGameStatus(
      socket.request,
      socket.id,
      status,
      socket,
    );
  }

  async getUser(socket: Socket) {
    try {
      const token = LoggedStrategyJWT.extractJWTCookie(socket.request);
      const payload: PayloadDTO =
        await this.authService.cookieService.verifyJWTToken(token);
      const user: User = await this.userPrisma.getUser({
        id: payload.id,
      });
      return user;
    } catch (error) {
      console.log('ERROR: User Not Found');
    }
  }

  //Event handler for when a client connects to the server
  async handleConnection(socket: Socket) {
    Logger.log('/******** NEW CONNECTION: ' + socket.id + ' ***********/');
    const user = await this.getUser(socket);
    if (user && user.gameStatus == GameStatus.AVAILABLE) {
      this.clientSocket.set(socket.id, socket);
      this.handleJoinGame(socket);
    }
  }

  async startPracticeGame(socket: Socket) {
    try {
      await this.updateGameStatus(socket, GameStatus.ONGAME);

      const gameId = this.generateGameId();
      const player1Socket = socket;
      const player1: User = await this.getUser(player1Socket);
      const player2ID = 'BOT@' + gameId;

      player1Socket.join(gameId);
      this.gameLoop(
        gameId,
        player1Socket.id,
        player1,
        player2ID,
        undefined,
        true,
      );
    } catch (error) {
      console.log('ERROR: Practice Game Terminated');
    }
  }

  async receivePairs(pair: PairedUsers) {
    const p1 = await this.sessionsService.getInQueueSocketID(pair.user1.id);
    const p2 = await this.sessionsService.getInQueueSocketID(pair.user2.id);
    if (p1 && p2) {
      await this.startMultiplayerGame(p1, p2);
    }
  }

  async startMultiplayerGame(p1: string, p2: string) {
    const gameID = this.generateGameId();
    try {
      const player1Socket = this.clientSocket.get(p1);
      const player1: User = await this.getUser(player1Socket);
      const player2Socket = this.clientSocket.get(p2);
      const player2: User = await this.getUser(player2Socket);

      if (p1 && p2) {
        await this.updateGameStatus(player1Socket, GameStatus.ONGAME);
        await this.updateGameStatus(player2Socket, GameStatus.ONGAME);
      }

      await player1Socket.join(gameID);
      await player2Socket.join(gameID);
      await this.gameLoop(
        gameID,
        player1Socket.id,
        player1,
        player2Socket.id,
        player2,
        false,
      );
    } catch (error) {
      console.log('ERROR: Multiplayer Game Terminated');
    }
  }

  async handleInvite(socket: Socket) {
    if (!this.inviteSocket.has(socket.id)) {
      this.inviteSocket.set(socket.id, socket);
      await this.updateGameStatus(socket, GameStatus.WAITING);
    }

    if (this.inviteSocket.size >= 2) {
      const data: Invite = await this.gameController.getInviteDTO();
      if (data) {
        try {
          const inviter: User = await this.userPrisma.getUser({
            username: data['invite'].inviterName,
          });
          const invitee: User = await this.userPrisma.getUser({
            username: data['invite'].inviteeName,
          });

          this.gameController.clearInviteData();
          const p1 = await this.sessionsService.getWaitingSocketID(inviter.id);
          const p2 = await this.sessionsService.getWaitingSocketID(invitee.id);
          if (p1 && p2) {
            this.startMultiplayerGame(p1, p2);
          }
        } catch (error) {
          console.log('ERROR: Invite DTO Contents');
        }
      }
    }
  }

  async handleJoinGame(socket: Socket) {
    const response = await this.gameController.getGameType();
    if (response) {
      response['gameType'] == 'invite'
        ? await this.handleInvite(socket)
        : response['gameType'] == 'random'
        ? await this.updateGameStatus(socket, GameStatus.ONQUEUE)
        : this.startPracticeGame(socket);
    }
  }

  generateGameId(): string {
    return 'room-' + Date.now().toString();
  }

  async gameLoop(
    gameID: string,
    player1Socket: string,
    player1: User,
    player2Socket: string,
    player2: User,
    againstBot: boolean,
  ) {
    let game = await this.gameService.initGame(
      gameID,
      player1Socket,
      player1,
      player2Socket,
      player2,
    );

    var gameInterval = setInterval(() => {
      this.gameService.updateGame(game, againstBot);
      this.gameMap.set(gameID, game);

      this.server.to(gameID).emit('updateGameDTO', this.gameMap.get(gameID));
      if (this.gameService.isGameDone(this.gameMap.get(gameID))) {
        this.cleanUpAfterGame(gameID);
        clearInterval(gameInterval);
      }
    }, 8);
  }

  cleanUpAfterGame(gameId: string) {
    if (this.gameMap.has(gameId)) {
      this.gameMap.delete(gameId);
      this.server.to(gameId).socketsLeave(gameId);
    }
  }

  findGameDTO(client: Socket): GameDTO {
    let gameId = null;

    for (const i of this.gameMap) {
      if (client.id == i[1].player1.ID || client.id == i[1].player2.ID) {
        gameId = i[1].id;
      }
    }
    return this.gameMap.get(gameId);
  }

  // Event handler for when a client disconnects from the server
  async handleDisconnect(socket: Socket) {
    Logger.log('handleDisconnect(): ' + socket.id);

    const sessionDTO = this.findGameDTO(socket);
    if (sessionDTO) {
      await this.gameService.endGame(sessionDTO, socket.id);
    }

    if (this.clientSocket.has(socket.id)) {
      this.clientSocket.delete(socket.id);
      await this.updateGameStatus(socket, GameStatus.AVAILABLE);
    }
    if (this.inviteSocket.has(socket.id)) {
      this.inviteSocket.delete(socket.id);
    }
  }

  @SubscribeMessage('moveUp')
  @UseGuards(SocketAuthGuard)
  movePaddleUpwards(@MessageBody() data: string[]) {
    try {
      if (data && data.length == 2) {
        this.paddleService.handleUpKey(
          this.gameMap.get(data.at(0)),
          data.at(1),
        );
      }
    } catch (error) {
      console.log('ERROR: Invalid Event');
    }
  }

  @SubscribeMessage('moveDown')
  @UseGuards(SocketAuthGuard)
  movePaddleDownwards(@MessageBody() data: string[]) {
    try {
      if (data && data.length == 2) {
        this.paddleService.handleDownKey(
          this.gameMap.get(data.at(0)),
          data.at(1),
        );
      }
    } catch (error) {
      console.log('ERROR: Invalid Event');
    }
  }

  @SubscribeMessage('increasePaddle')
  @UseGuards(SocketAuthGuard)
  increasePaddleSize(@MessageBody() data: string[]) {
    try {
      if (data && data.length == 2) {
        this.paddleService.increaseSize(
          this.gameMap.get(data.at(0)),
          data.at(1),
        );
      }
    } catch (error) {
      console.log('ERROR: Invalid Event');
    }
  }

  @SubscribeMessage('decreaseBallSpeed')
  @UseGuards(SocketAuthGuard)
  decreaseBallSpeed(@MessageBody() data: string[]) {
    try {
      if (data && data.length == 2) {
        this.ballService.decreaseSpeed(
          this.gameMap.get(data.at(0)),
          data.at(1),
        );
      }
    } catch (error) {
      console.log('ERROR: Invalid Event');
    }
  }

  @SubscribeMessage('smash')
  @UseGuards(SocketAuthGuard)
  smash(@MessageBody() data: string[]) {
    try {
      if (data && data.length == 2) {
        this.ballService.smash(this.gameMap.get(data.at(0)), data.at(1));
      }
    } catch (error) {
      console.log('ERROR: Invalid Event');
    }
  }

  @SubscribeMessage('surrender')
  @UseGuards(SocketAuthGuard)
  endGame(@MessageBody() data: string[]) {
    try {
      if (data && data.length == 2) {
        this.gameService.endGame(this.gameMap.get(data.at(0)), data.at(1));
      }
    } catch (error) {
      console.log('ERROR: Invalid Event');
    }
  }
}
