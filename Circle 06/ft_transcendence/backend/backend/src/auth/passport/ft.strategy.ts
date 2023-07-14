import { Injectable } from '@nestjs/common';
import { PassportStrategy } from '@nestjs/passport';
import { Strategy } from 'passport-42';

@Injectable()
export class Strategy42 extends PassportStrategy(Strategy, '42') {
  constructor() {
    super({
      clientID: `${process.env.CLIENT_ID}`,
      clientSecret: `${process.env.CLIENT_SECRET}`,
      callbackURL: `${process.env.CALLBACK_URL}`,
      profileFields: {
        // https://api.intra.42.fr/apidoc/2.0/users/show.html
        id: 'id',
        login: 'login',
      },
    });
  }

  async validate(
    accessToken: string,
    refreshToken: string,
    profile: any,
    done: any,
  ) {
    delete profile._raw;
    delete profile._json;
    done(null, profile);
  }
}
