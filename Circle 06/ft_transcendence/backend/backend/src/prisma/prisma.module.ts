import { Global, Module } from '@nestjs/common';
import { PrismaService } from './prisma.service';
import { UserPrismaService } from './user.prisma';
import { GamePrismaService } from './game.prisma';
import { FriendPrismaService } from './friend.prisma';

@Global()
@Module({
  providers: [PrismaService, UserPrismaService, GamePrismaService, FriendPrismaService],
  exports: [PrismaService, UserPrismaService, GamePrismaService, FriendPrismaService],
})
export class PrismaModule {}
