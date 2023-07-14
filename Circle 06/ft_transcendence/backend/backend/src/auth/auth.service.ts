import { Injectable } from '@nestjs/common';
import axios from 'axios';
import { UsersService } from 'src/users/users.service';
import * as speakeasy from 'speakeasy';
import { PayloadDTO } from './dto/JWTPayload.dto';
import { AuthStatusDTO } from './dto/UserStatus.dto';
import { CookieService } from 'src/cookie/cookie.service';
import { Status } from '@prisma/client';

@Injectable()
export class AuthService {
  constructor(
    public userService: UsersService,
    public cookieService: CookieService,
  ) {}

  async login(profile) {
    const user = await this.userService.addUser(profile);
    const userExist: boolean = user?.username != null;
    console.log(userExist);
    const payload: PayloadDTO = {
      login: user?.intraLogin,
      id: user?.id,
      status: AuthStatusDTO.stage_completed,
    };

    // if (user == undefined || (userExist == true && user.available == Status.ONLINE)) {
    //   return {
    //     token: '',
    //   };
    // }

    if (!userExist) {
      payload.status = AuthStatusDTO.stage_setUsername;
    } else if (user.enable2FA === true) {
      payload.status = !user.loggedin
        ? AuthStatusDTO.stage_2faAuthNew
        : AuthStatusDTO.stage_2faAuthOld;
    } else if (!user.loggedin) {
      await this.userService.setData(user.id, {
        loggedin: true,
      })
    }

    return {
      token: this.cookieService.getJWTToken(payload),
    };
  }

  async loginWithUsername(
    payload: PayloadDTO,
    username: string,
    enable2FA: string,
  ) {
    const usernameStatus: boolean = await this.userService.setUsername(
      payload.id,
      username,
    );

    payload.status =
      usernameStatus === false
        ? AuthStatusDTO.stage_setUsername
        : enable2FA === 'true'
          ? AuthStatusDTO.stage_2faAuthNew
          : AuthStatusDTO.stage_completed;

    return {
      redirectURL: '/',
      token: this.cookieService.getJWTToken(payload),
      usernameStatus,
    };
  }

  async generateQrCode(userID: number) {
    const SecretCode = speakeasy.generateSecret().base32;

    await this.userService.setData(userID, {
      enable2FA: true,
      secret2FA: SecretCode,
    });

    const response = await axios.get(process.env.TFA_API_QR_GEN_URL, {
      params: {
        AppName: process.env.REACT_APP_NAME,
        AppInfo: userID,
        SecretCode,
      },
    });

    const regex = /<img.*?src=['"](.*?)['"]/;
    const match = response.data.match(regex);
    return match[1];
  }

  async verifyCode(userID: number, Pin: string) {
    const userData = await this.userService.getData(
      userID,
      'secret2FA loggedin',
    );
    if (userData == undefined) return false;

    const SecretCode = userData.secret2FA;
    const response = await axios.get(process.env.TFA_API_VERIFY_URL, {
      params: {
        Pin,
        SecretCode,
      },
    });

    const isCodeValid: boolean = response.data == 'True' ? true : false;
    if (isCodeValid == true && !userData.loggedin) {
      await this.userService.setData(userID, {
        loggedin: true,
      });
    }

    return isCodeValid;
  }
}
