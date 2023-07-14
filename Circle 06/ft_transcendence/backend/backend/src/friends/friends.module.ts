import { Module } from '@nestjs/common';
import { FriendsService } from './friends.service';
import { FriendsController } from './friends.controller';
import { UsersService } from 'src/users/users.service';

@Module({
  providers: [FriendsService, UsersService],
  controllers: [FriendsController],
  exports: [FriendsService]
})
export class FriendsModule {}
