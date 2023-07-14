import { Module } from '@nestjs/common';
import { AchievementService } from './achievement.service';

@Module({
  providers: [AchievementService],
  exports: [AchievementService]
})
export class AchievementModule {}
