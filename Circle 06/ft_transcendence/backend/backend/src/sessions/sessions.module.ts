import { Module } from '@nestjs/common';
import { SessionsGateway } from './sessions.gateway';
import { SessionsService } from './sessions.service';
import { UsersService } from 'src/users/users.service';
import { AuthModule } from 'src/auth/auth.module';
import { InviteService } from './sessions.invite.service';
import { FriendsModule } from 'src/friends/friends.module';
import { FriendsService } from 'src/friends/friends.service';

@Module({
  imports: [AuthModule, FriendsModule],
  providers: [SessionsGateway, SessionsService, UsersService, InviteService, FriendsService],
})
export class SessionsModule {}
