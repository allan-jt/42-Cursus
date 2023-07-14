import { Module } from '@nestjs/common';
import { RatingService } from './rating.service';

@Module({
  providers: [RatingService],
})
export class RatingModule {}
