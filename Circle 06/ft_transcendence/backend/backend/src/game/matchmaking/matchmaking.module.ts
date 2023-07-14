import { Module } from '@nestjs/common';
import { MatchmakingService } from './matchmaking.service';
import { GameModule } from 'src/game/game.module';

@Module({
  imports: [GameModule],
  providers: [MatchmakingService],
})
export class MatchmakingModule {}
