import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { AuthModule } from './auth/auth.module';
import { UsersModule } from './users/users.module';
import { PrismaModule } from './prisma/prisma.module';
import { GameModule } from './game/game.module';
import { SessionsModule } from './sessions/sessions.module';
import { FriendsModule } from './friends/friends.module';
import { ServeStaticModule } from '@nestjs/serve-static';
import { CookieModule } from './cookie/cookie.module';
import { AchievementModule } from './game/achievement/achievement.module';
import { MatchmakingModule } from './game/matchmaking/matchmaking.module';
import { join } from 'path';
import { ChatModule } from './chat/chat.module';
import { ThrottlerGuard, ThrottlerModule } from '@nestjs/throttler';
import { APP_GUARD } from '@nestjs/core';

@Module({
  imports: [
    AuthModule,
    UsersModule,
    PrismaModule,
    GameModule,
    SessionsModule,
    CookieModule,
    AchievementModule,
    FriendsModule,
    ChatModule,
    ServeStaticModule.forRoot({
      rootPath: join(__dirname, '..', '../images'),
      serveRoot: '/api',
      serveStaticOptions: {
        index: false
      },
    }),
    MatchmakingModule,
    ThrottlerModule.forRoot({
      ttl: 60,
      limit: 20000,
    })
  ],
  controllers: [AppController],
  providers: [AppService, {
    provide: APP_GUARD,
    useClass: ThrottlerGuard,
  }],
})
export class AppModule {}
