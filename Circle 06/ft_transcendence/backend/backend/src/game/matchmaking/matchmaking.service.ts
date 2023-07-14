import { Injectable } from '@nestjs/common';
import { GameStatus, User } from '@prisma/client';
import { UserPrismaService } from 'src/prisma/user.prisma';
import { PairedUsers } from './dto/PairedUsers.dto';
import { GameGateway } from 'src/game/game.gateway';

@Injectable()
export class MatchmakingService {
  private matchmakerTimer: NodeJS.Timer;
  private now: Date;
  private waitTimes: Map<number, number>; // <userID, Date.getTime()>
  private refreshRate: number; // in ms
  private timeWaitFactor: number; // value between 0 and 1

  private maxDiffAggregate: number;
  private minDiffAggregate: number;
  private maxWaitingTime: number;
  private minWaitingTime: number;

  constructor(private userPrisma: UserPrismaService, 
      private gameGateway: GameGateway) {
    this.waitTimes = new Map<number, number>();
    this.refreshRate = 2000;
    this.timeWaitFactor = 0.25;

    this.minDiffAggregate = 0;
    this.minWaitingTime = 0;
    this.maxWaitingTime = 120000;

    this.matchmakerTimer = setInterval(
      async () => await this.matchCurrentQueue(),
      this.refreshRate,
    );
  }

  /* SET UP BASIC VARIABLES & START MATCHING_____________________________________*/
   async stopMatchmaking(): Promise<void> {
    clearInterval(this.matchmakerTimer);
  }

  async matchCurrentQueue(): Promise<void> {
    const usersInQueue: User[] = await this.userPrisma.getUsers({
      where: { gameStatus: GameStatus.ONQUEUE },
      orderBy: { rating: 'desc' },
    });
    if (usersInQueue.length === 0) {
      return;
    }

    this.now = new Date();
    this.setMaxDiff(usersInQueue);
    this.setWaitStats(usersInQueue);
    if (usersInQueue.length > 1) {
      this.processPairs(this.getOptimalPairings(usersInQueue));
    }
  }

  processPairs(pairedUsers: PairedUsers[]): void {
    for (const pair of pairedUsers) {
      this.waitTimes.delete(pair.user1.id);
      this.waitTimes.delete(pair.user2.id);
      this.gameGateway.receivePairs(pair);
      // console.log(
      //   `{${pair.user1.id}(${pair.user1.rating}) | ${pair.user2.id}(${pair.user2.rating})}`,
      // );
    }
  }

  /* MEAT OF THE HANDSHAKE ALGORITHM_____________________________________________*/
  getOptimalPairings(usersInQueue: User[]): PairedUsers[] {
    let rightPairs: PairedUsers[] = this.pairByHandshake(usersInQueue, -1);
    let leftPairs: PairedUsers[] = this.pairByHandshake(usersInQueue, 1);

    let rightPairScore: number = rightPairs.reduce(
      (total, pair) => total + pair.matchedScore,
      0,
    );
    let leftPairScore: number = leftPairs.reduce(
      (total, pair) => total + pair.matchedScore,
      0,
    );

    return leftPairScore <= rightPairScore ? leftPairs : rightPairs;
  }

  pairByHandshake(usersInQueue: User[], direction: number): PairedUsers[] {
    let pairedUsers: PairedUsers[] = [];
    let queuedUsers: User[] = usersInQueue.slice();
    let startIndex: number = direction == 1 ? 1 : queuedUsers.length - 2;

    while (queuedUsers.length >= 3) {
      const { index, pair } = this.getPairByHandshake(
        queuedUsers,
        startIndex,
        direction,
      );

      startIndex = index;
      if (pair !== undefined) {
        pairedUsers.push(pair);
      }
    }

    if (queuedUsers.length == 2) {
      pairedUsers.push({
        user1: queuedUsers[0],
        user2: queuedUsers[1],
        matchedScore: this.getMatchScore(queuedUsers[0], queuedUsers[1]),
      });
    }

    return pairedUsers;
  }

  getPairByHandshake(
    queuedUsers: User[],
    startIndex: number,
    direction: number,
  ) {
    const leftUser: User = queuedUsers[startIndex - 1];
    const midUser: User = queuedUsers[startIndex];
    const rightUser: User = queuedUsers[startIndex + 1];
    let pair: PairedUsers = undefined;

    const leftScore = this.getMatchScore(leftUser, midUser);
    const rightScore = this.getMatchScore(rightUser, midUser);

    if (
      this.betterPairExists(
        queuedUsers,
        startIndex,
        direction,
        leftScore,
        rightScore,
      ) === true
    ) {
      return {
        index: startIndex + direction,
        pair,
      };
    }

    if (leftScore <= rightScore) {
      queuedUsers.splice(startIndex - 1, 2);
      pair = {
        user1: midUser,
        user2: leftUser,
        matchedScore: leftScore,
      };
    } else {
      queuedUsers.splice(startIndex, 2);
      pair = {
        user1: midUser,
        user2: rightUser,
        matchedScore: rightScore,
      };
    }

    return {
      index: direction == 1 ? 1 : queuedUsers.length - 2,
      pair,
    };
  }

  betterPairExists(
    usersInQueue: User[],
    userIndex: number,
    direction: number,
    leftScore: number,
    rightScore: number,
  ): boolean {
    if (
      (direction === -1 && userIndex === 1) ||
      (direction === 1 && userIndex === usersInQueue.length - 2)
    ) {
      return false;
    }

    const alternateScore = this.getMatchScore(
      usersInQueue[userIndex + direction],
      usersInQueue[userIndex + direction * 2],
    );

    return (
      (direction == -1 &&
        rightScore > leftScore &&
        leftScore > alternateScore) ||
      (direction == 1 && leftScore > rightScore && rightScore > alternateScore)
    );
  }

  /* HELPER FUNCTIONS___________________________________________________________*/
  getMatchScore(user1: User, user2: User): number {
    const ratingDiff = Math.abs(user1.rating - user2.rating);
    const avgWait =
      (this.waitTimes.get(user1.id) + this.waitTimes.get(user2.id)) / 2;

    const normalizedDiff = this.getNormalizedValue(
      ratingDiff,
      this.minDiffAggregate,
      this.maxDiffAggregate,
    );
    const normalizedWait = this.getNormalizedValue(
      this.now.getTime() - avgWait,
      this.minWaitingTime,
      this.maxWaitingTime,
    );

    return (
      (1 - this.timeWaitFactor) * normalizedDiff -
      this.timeWaitFactor * normalizedWait
    );
  }

  setMaxDiff(usersInQueue: User[]) {
    this.maxDiffAggregate = usersInQueue[0].rating - usersInQueue.at(-1).rating;
  }

  setWaitStats(usersInQueue: User[]) {
    let priorUserFound: boolean = false;
    let priorUser = undefined;
    for (const [key, val] of this.waitTimes.entries()) {
      priorUser = [key, val];
    }

    for (const user of usersInQueue) {
      if (priorUser === undefined || user.id !== priorUser[0]) {
        this.waitTimes.set(user.id, this.now.getTime());
        continue;
      }
      priorUserFound = true;
    }

    if (priorUser !== undefined && priorUserFound == false) {
      this.waitTimes.delete(priorUser[0]);
    }
  }

  getNormalizedValue(value: number, min: number, max: number) {
    return max == min ? 0 : (value - min) / (max - min);
  }
}
