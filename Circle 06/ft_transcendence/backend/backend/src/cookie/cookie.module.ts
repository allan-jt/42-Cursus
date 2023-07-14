import { Module } from '@nestjs/common';
import { CookieService } from './cookie.service';
import { JwtModule } from '@nestjs/jwt';

@Module({
  imports: [
    JwtModule.register({
      secret: `${process.env.JWT_SECRET}`,
      signOptions: { expiresIn: `${process.env.JWT_EXPIRE}` },
    }),
  ],
  providers: [CookieService],
  exports: [CookieService],
})
export class CookieModule {}
