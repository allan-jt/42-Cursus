import { Injectable } from '@nestjs/common';
import { Achievements, Game, User } from '@prisma/client';
import { UserPrismaService } from 'src/prisma/user.prisma';
import { UserWithGames } from './dto/UserWithGames.dto';

@Injectable()
export class AchievementService {
  private baseRating: number;

  constructor(private userPrisma: UserPrismaService) {
    this.baseRating = 1500;
  }

  async calculateAchievment(userID: number) {
    console.log('calculating achievement for id', userID);
    const user = (await this.userPrisma.getUser(
      { id: userID },
      {
        gamesPlayer1: { orderBy: { startAt: 'desc' } },
        gamesPlayer2: { orderBy: { startAt: 'desc' } },
        gamesWon: { orderBy: { startAt: 'desc' } },
      },
    )) as UserWithGames;

    const lastGame: Game = this.getLastGame(user);
    if (typeof lastGame === 'undefined' || lastGame.winner_id !== user.id) {
      return; // No achievment
    }

    this.calculatePowerpuffPaddle(user);
    await this.calculateChemicalXChampion(user);
    await this.calculateSuperSonicServe(user);
    await this.calculateVillainVanquisher(user, lastGame);

    await this.updateAchievments(user);
  }

  calculatePowerpuffPaddle(user: UserWithGames) {
    const index: number = user.achievements.indexOf(
      Achievements.POWERPUFF_PADDLE,
    );

    if (user.rating >= this.baseRating && index < 0) {
      user.achievements.push(Achievements.POWERPUFF_PADDLE);
    } else if (user.rating < this.baseRating && index >= 0) {
      user.achievements.splice(index, 1);
    }
  }

  async calculateChemicalXChampion(user: UserWithGames) {
    const games1: Game[] = user.gamesPlayer1;
    const games2: Game[] = user.gamesPlayer2;
    const gamesWon: Game[] = user.gamesWon;
    let [games1Index, games2Index, gamesWonInARow] = [0, 0, 0];

    for (let game of gamesWon) {
      if (games1Index < games1.length && game.id === games1[games1Index].id) {
        games1Index++;
      } else if (
        games2Index < games2.length &&
        game.id === games2[games2Index].id
      ) {
        games2Index++;
      } else {
        break;
      }
      gamesWonInARow++;
    }
    console.log(games1Index, games2Index, gamesWonInARow);
    if (gamesWonInARow > 0 && gamesWonInARow % 10 === 0) {
      user.achievements.push(Achievements.CHEMICAL_X_CHAMPION);
    }
  }

  async calculateSuperSonicServe(user: UserWithGames) {
    const gamesWon: Game[] = user.gamesWon;
    const now: Date = new Date();
    const startOfToday: Date = new Date(now.getFullYear(), now.getMonth(), now.getDate(), 0, 0, 0);
    
    let gamesWonToday: number = 0;
    for (let game of gamesWon) {
      if (game.finishAt.getTime() >= startOfToday.getTime()) {
        gamesWonToday++;
      }
    }

    if (gamesWonToday === 3) {
      user.achievements.push(Achievements.SUPER_SONIC_SERVE);
    }
  }

  async calculateVillainVanquisher(user: UserWithGames, lastGame: Game) {
    console.log(lastGame.id);

    const opponentID =
      user.id === lastGame.player1_id
        ? lastGame.player2_id
        : lastGame.player1_id;
    const opponent = await this.userPrisma.getUser({ id: opponentID });

    if (opponent.rating >= this.baseRating && user.rating < this.baseRating) {
      user.achievements.push(Achievements.VILLAIN_VANQUISHER);
    }
  }

  getLastGame(user: UserWithGames): Game {
    if (!user) {
      return;
    }
    const game1: Game = user.gamesPlayer1[0];
    const game2: Game = user.gamesPlayer2[0];

    return typeof game1 === 'undefined'
      ? game2
      : typeof game2 === 'undefined'
      ? game1
      : game1.finishAt.getTime() > game2.finishAt.getTime()
      ? game1
      : game2;
  }

  async updateAchievments(user: UserWithGames) {
    await this.userPrisma.updateUser(
      { id: user.id },
      {
        achievements: user.achievements,
      },
    );
  }
}

// "Powerpuff Paddle": Achieve rating > 1000.
// "Chemical X Champion": Win 10 games in a row.
// "Super Sonic Serve": Win 3 games in an hour
// "Villain Vanquisher": Win a game against the "Powerpubb Paddle" with < 1000.
