import { Module } from '@nestjs/common';
import { AuthService } from './auth.service';
import { AuthController } from './auth.controller';
import { UsersModule } from 'src/users/users.module';
import { JwtModule } from '@nestjs/jwt';
import { PassportModule } from '@nestjs/passport';
import { Strategy42 } from './passport/ft.strategy';
import { LoggedStrategyJWT } from './passport/jwt.logged.strategy';
import { NonLoggedStrategyJWT } from './passport/jwt.nonlogged.strategy';
import { LoggedAuthGuard } from './guards/logged.guard';
import { NonLoggedAuthGuard } from './guards/nonlogged.guard';
import { CookieModule } from 'src/cookie/cookie.module';
import { SocketAuthGuard } from './guards/socket.guard';

@Module({
  imports: [PassportModule, UsersModule, CookieModule],
  providers: [
    AuthService,
    Strategy42,
    LoggedStrategyJWT,
    NonLoggedStrategyJWT,
    LoggedAuthGuard,
    NonLoggedAuthGuard,
    SocketAuthGuard
  ],
  controllers: [AuthController],
  exports: [
    AuthService,
    Strategy42,
    LoggedStrategyJWT,
    NonLoggedStrategyJWT,
    LoggedAuthGuard,
    NonLoggedAuthGuard,
    SocketAuthGuard,
    CookieModule
  ],
})
export class AuthModule {}
