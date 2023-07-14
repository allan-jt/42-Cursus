import { Game, User } from '@prisma/client';

export interface UserWithGames extends User {
  gamesPlayer1: Game[];
  gamesPlayer2: Game[];
  gamesWon: Game[];
}
