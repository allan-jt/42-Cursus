import { Module } from '@nestjs/common';
import { ChatGateway } from './chat.gateway';
import { ChatPrismaService } from './prisma.service';
import { ChatService } from './chat.service';
import { UsersService } from 'src/users/users.service';
import { JwtService } from '@nestjs/jwt';
import { MessageService } from './message.service';
import { ParticipantService } from './participant.service';
import { UtilsService } from './utils.service';
import { AuthService } from './../auth/auth.service';
import { CookieService } from 'src/cookie/cookie.service';
import { Mutex } from 'async-mutex';

@Module({
  imports: [],
  providers: [
    ChatGateway, 
    ChatService,
		AuthService,
		ChatPrismaService,
    UsersService,
		CookieService,
    JwtService,
    MessageService,
    ParticipantService,
    UtilsService,
		Mutex
  ],
})
export class ChatModule {}
