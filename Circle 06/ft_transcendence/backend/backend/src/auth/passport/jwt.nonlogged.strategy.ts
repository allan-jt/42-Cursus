import { Injectable } from '@nestjs/common';
import { PassportStrategy } from '@nestjs/passport';
import { Strategy } from 'passport-jwt';
import { PayloadDTO } from '../dto/JWTPayload.dto';
import { LoggedStrategyJWT } from './jwt.logged.strategy';

@Injectable()
export class NonLoggedStrategyJWT extends PassportStrategy(
  Strategy,
  'non-logged',
) {
  constructor() {
    super({
      secretOrKey: `${process.env.JWT_SECRET}`,
      jwtFromRequest: LoggedStrategyJWT.extractJWTCookie,
      ignoreExpiration: false,
    });
  }

  async validate(payload: PayloadDTO): Promise<PayloadDTO> {
    return payload;
  }
}
