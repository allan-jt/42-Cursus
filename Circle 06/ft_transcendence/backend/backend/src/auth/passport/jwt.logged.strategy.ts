import { Injectable, UnauthorizedException } from '@nestjs/common';
import { PassportStrategy } from '@nestjs/passport';
import { Strategy } from 'passport-jwt';
import { AuthStatusDTO } from '../dto/UserStatus.dto';
import { PayloadDTO } from '../dto/JWTPayload.dto';
import { CookieService } from 'src/cookie/cookie.service';

@Injectable()
export class LoggedStrategyJWT extends PassportStrategy(Strategy, 'logged') {
  constructor() {
    super({
      secretOrKey: `${process.env.JWT_SECRET}`,
      jwtFromRequest: LoggedStrategyJWT.extractJWTCookie,
      ignoreExpiration: false,
    });
  }

  static extractJWTCookie(req) {
    return CookieService.extractValueFromCookies(req, 'Authorization');
  }

  async validate(payload: PayloadDTO): Promise<PayloadDTO> {
    if (payload.status != AuthStatusDTO.stage_completed) {
      throw new UnauthorizedException();
    }
    return payload;
  }
}
