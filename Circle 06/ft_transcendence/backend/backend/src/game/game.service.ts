import { Injectable } from '@nestjs/common';
import { BallService } from './game.ball.service';
import { SessionsService } from 'src/sessions/sessions.service';
import { RatingService } from './rating/rating.service';
import { AchievementService } from './achievement/achievement.service';
import { GameDTO, GAME_WIDTH } from './dto/game.dto';
import { Game, User } from '@prisma/client';
import { GamePrismaService } from 'src/prisma/game.prisma';

@Injectable()
export class GameService {
  private WINNING_POINT: number;
  private newGame: Game;
  private botAccuracy: number;

  constructor(
    private ballService: BallService,
    private sessionsService: SessionsService,
    private ratingService: RatingService,
    private achievementService: AchievementService,
    private gamePrisma: GamePrismaService,
  ) {
    this.WINNING_POINT = 11;
    this.botAccuracy = 1;
  }

  isSocketABot(socketID: string, gameID: string): boolean {
    return socketID == 'BOT@' + gameID;
  }

  async initGame(
    gameID: string,
    player1Socket: string,
    player1: User,
    player2Socket: string,
    player2: User,
  ): Promise<GameDTO> {
    try {
      if (!this.isSocketABot(player2Socket, gameID)) {
        const p1UserID = await this.sessionsService.getInGameUserID(
          player1Socket,
        );
        const p2UserID = await this.sessionsService.getInGameUserID(
          player2Socket,
        );

        this.newGame = await this.gamePrisma.createGame({
          player1: { connect: { id: p1UserID } },
          player2: { connect: { id: p2UserID } },
        });
      }

      return new GameDTO(
        gameID,
        player1Socket,
        player1.username,
        `${process.env.REACT_APP_BE_URL}/` + player1.image,
        player2Socket,
        player2 == undefined ? 'BOT' : player2.username,
        player2 == undefined
          ? ''
          : `${process.env.REACT_APP_BE_URL}/` + player2.image,
      );
    } catch (error) {
      console.log('ERROR: Game Initialization');
    }
  }

  startNewRound(game: GameDTO): void {
    if (game.ball.position.x < 0 || game.ball.position.x > GAME_WIDTH) {
      this.updateScore(game);
      this.ballService.resetBall(game.ball);
      this.botAccuracy = 1;
    }
  }

  getBotAccuracy() {
    return this.botAccuracy > 0
      ? (this.botAccuracy -= 0.00007)
      : this.botAccuracy;
  }

  updateBotPaddle(game: GameDTO, isAgainstBot: boolean) {
    if (isAgainstBot) {
      const botMidPoint = game.ball.position.y - game.player2.paddle.height / 2;
      game.player2.paddle.position.y = botMidPoint * this.getBotAccuracy();
    }
  }

  async updateGame(game: GameDTO, isAgainstBot: boolean): Promise<void> {
    this.ballService.updateBallPosition(game.ball);
    this.ballService.incrementBallVector(game.ball.direction);
    this.ballService.flipBallDirection(game);
    this.updateBotPaddle(game, isAgainstBot);
    this.startNewRound(game);
  }

  async checkAchivements(game: GameDTO) {
    const player1ID = await this.sessionsService.getInGameUserID(
      game.player1.ID,
    );
    const player2ID = await this.sessionsService.getInGameUserID(
      game.player2.ID,
    );

    await this.achievementService.calculateAchievment(player1ID);
    await this.achievementService.calculateAchievment(player2ID);
  }

  getWinner(game: GameDTO) {
    return game.player2.surrender ||
      (!game.player1.surrender && game.player1.score > game.player2.score)
      ? game.player1.ID
      : game.player2.ID;
  }

  async updateGameData(game: GameDTO, winnerSocketID: string) {
    try {
      await this.gamePrisma.updateGame(
        { id: this.newGame.id },
        {
          score1: game.player1.score,
          score2: game.player2.score,
          winner: {
            connect: {
              id: await this.sessionsService.getInGameUserID(winnerSocketID),
            },
          },
        },
      );
    } catch (error) {
      console.log('ERROR: Game Record');
    }
  }

  isScoreEqualToWinningPoint(game: GameDTO) {
    return (
      game.player1.score == this.WINNING_POINT ||
      game.player2.score == this.WINNING_POINT
    );
  }

  updateScore(game: GameDTO): void {
    if (game.ball.position.x > GAME_WIDTH) {
      game.player1.score++;
      game.ball.direction.x = -1;
    } else if (game.ball.position.x < 0) {
      game.player2.score++;
      game.ball.direction.x = 1;
    }

    if (this.isScoreEqualToWinningPoint(game)) {
      this.endGame(game, null);
    }
  }

  didPlayerSurrender(game: GameDTO, socketID: string) {
    const player = getPlayer(game, socketID);
    if (player) {
      player.surrender = true;
    }
  }

  async endGame(game: GameDTO, socketID: string): Promise<void> {
    this.didPlayerSurrender(game, socketID);
    const winnerSocketID = this.getWinner(game);

    if (!this.isSocketABot(game.player2.ID, game.id)) {
      await this.ratingService.updatePlayerRatings(game, winnerSocketID);
      await this.updateGameData(game, winnerSocketID);
      await this.checkAchivements(game);
    }

    game.status.isGameDone = true;
  }

  isGameDone(game: GameDTO): boolean {
    return game.status.isGameDone;
  }
}

export function getPlayer(game: GameDTO, socketID: string) {
  return game && socketID == game.player1.ID
    ? game.player1
    : game && socketID == game.player2.ID
    ? game.player2
    : undefined;
}
