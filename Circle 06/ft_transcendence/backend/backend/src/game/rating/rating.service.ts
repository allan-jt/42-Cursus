import { Injectable } from '@nestjs/common';
import { User } from '@prisma/client';
import { SessionsService } from 'src/sessions/sessions.service';
import { UserPrismaService } from 'src/prisma/user.prisma';
import { GameDTO } from 'src/game/dto/game.dto';

@Injectable()
export class RatingService {
  constructor(
    private sessionsService: SessionsService,
    private userPrisma: UserPrismaService,
  ) {}

  getExpectedScore(ratingA: number, ratingB: number) {
    return 1 / (1 + Math.pow(10, (ratingB - ratingA) / 400));
  }

  async getCurrentRating(username: string) {
    try {
      const user: User = await this.userPrisma.getUser({
        username: username,
      });
      return user.rating;
    } catch (error) {
      console.log('ERROR: Unable to Obtain Current Rating');
    }
  }

  /**
   * @param ratingA        current rating of player whose rating is about to be updated
   * @param ratingB        current rating of opposing player
   * @param gameOutcome    a number which could be 1 or 0. 1 if a player won the game
   *                       or 0 if they lost.
   *
   * Formula was taken from:
   * 	• https://en.wikipedia.org/wiki/Elo_rating_system
   * 	• https://en.wikipedia.org/wiki/Chess_rating_system
   * 	• https://www.youtube.com/watch?v=AsYfbmp0To0
   */
  getNewRating(ratingA: number, ratingB: number, gameOutcome: number): number {
    const kFactor = 32;
    const expectedScore = this.getExpectedScore(ratingA, ratingB);
    const score = gameOutcome;

    const newRating = ratingA + kFactor * (score - expectedScore);
    return Math.round(newRating);
  }
  /**
   * @brief    Sample Scenario
   *
   * aalsuwai registered to the game      aalsuwai.Rating = 1000
   * anasr registered to the game         anasr.Rating = 1000
   * anifanto registered to the game      anifanto.Rating = 1000
   * athekkep registered to the game      athekkep.Rating = 1000
   * gkintana registered to the game      gkintana.Rating = 1000
   *
   * aalsuwai vs anasr       aalsuwai wins    aalsuwai.Rating = 1032 | anasr.Rating = 968
   * aalsuwai vs anifanto    aalsuwai wins    aalsuwai.Rating = 1047 | anifanto.Rating = 985
   * anasr vs anifanto       anifanto wins    anasr.Rating = 953 | anifanto.Rating = 1000
   * aalsuwai vs anifanto    anifanto wins    aalsuwai.Rating = 1029 | anifanto.Rating = 1018
   */

  async setNewRating(playerID: string, newRating: number) {
    const userID = await this.sessionsService.getInGameUserID(playerID);
    try {
      await this.userPrisma.updateUser({ id: userID }, { rating: newRating });
    } catch (error) {
      console.log('ERROR: Rating Not Updated');
    }
  }

  async updatePlayerRatings(game: GameDTO, winnerSocketID: string) {
    const gameWinner = winnerSocketID == game.player1.ID ? 1 : 2;
    const player1Rating = Number(
      await this.getCurrentRating(game.player1.username),
    );
    const player2Rating = Number(
      await this.getCurrentRating(game.player2.username),
    );

    const newPlayer1Rating = this.getNewRating(
      player1Rating,
      player2Rating,
      gameWinner == 1 ? 1 : 0,
    );
    const newPlayer2Rating = this.getNewRating(
      player2Rating,
      player1Rating,
      gameWinner == 2 ? 1 : 0,
    );

    this.setNewRating(game.player1.ID, newPlayer1Rating);
    this.setNewRating(game.player2.ID, newPlayer2Rating);
  }
}
