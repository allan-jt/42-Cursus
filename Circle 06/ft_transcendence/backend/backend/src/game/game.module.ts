import { Module } from '@nestjs/common';
import { GameGateway } from './game.gateway';
import { GameController } from './game.controller';
import { GameService } from './game.service';
import { BallService } from './game.ball.service';
import { PaddleService } from './game.paddle.service';
import { AuthModule } from 'src/auth/auth.module';
import { SessionsService } from 'src/sessions/sessions.service';
import { UsersService } from 'src/users/users.service';
import { RatingService } from './rating/rating.service';
import { AchievementService } from './achievement/achievement.service';

@Module({
  imports: [AuthModule],
  providers: [
    GameGateway,
    GameController,
    GameService,
    RatingService,
    AchievementService,
    BallService,
    PaddleService,
    SessionsService,
    UsersService,
  ],
  controllers: [GameController],
  exports: [GameGateway],
})
export class GameModule {}
