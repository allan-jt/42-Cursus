import { HttpException, Injectable } from '@nestjs/common';
import { JwtService } from '@nestjs/jwt';
import { PayloadDTO } from 'src/auth/dto/JWTPayload.dto';

@Injectable()
export class CookieService {
  constructor(private jwtService: JwtService) {}

  static extractCookies(request: any): string | undefined {
    const rawCookies: string | undefined =
      request.handshake?.headers.upgrade?.toLowerCase() === 'websocket'
        ? request.handshake.headers.cookie
        : request.headers.cookie;

    return rawCookies;
  }

  static extractValueFromCookies(
    request: any,
    key: string,
  ): string | undefined {
    const cookies = CookieService.extractCookies(request);
    if (typeof cookies == 'undefined' || cookies.length === 0) {
      return undefined;
    }

    const splitCookies = cookies.split('; ');
    const keyValueCookies = {};
    splitCookies.forEach((strValue) => {
      const [key, value] = strValue.split('=');
      keyValueCookies[key] = value;
    });

    return keyValueCookies[key];
  }

  getJWTToken(payload: PayloadDTO): string {
    const { login, id, status } = payload;
    return this.jwtService.sign({ login, id, status }, {
      secret: process.env.JWT_SECRET,
    });
  }

  async verifyJWTToken(token: string) {
    try {
      const payload = await this.jwtService.verify(token.trim(), {
        secret: process.env.JWT_SECRET,
      });
      return payload;
    } catch (error){
      throw new HttpException(error.message, 401, { cause: error });
    }
  }

  async decodeJWTToken(token: string) {
    const payload = await this.jwtService.decode(token.trim());
    return payload;
  }
}