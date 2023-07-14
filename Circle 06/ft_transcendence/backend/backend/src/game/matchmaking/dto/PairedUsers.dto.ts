import { User } from '@prisma/client';

export class PairedUsers {
  user1: User;
  user2: User;
  matchedScore?: number;
}
