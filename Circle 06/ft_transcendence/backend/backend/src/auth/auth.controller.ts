import {
  Body,
  Controller,
  Get,
  HttpException,
  Post,
  Req,
  Res,
  UseGuards,
} from '@nestjs/common';
import { AuthGuard } from '@nestjs/passport';
import { Request, Response } from 'express';
import { AuthService } from './auth.service';
import { NonLoggedAuthGuard } from './guards/nonlogged.guard';
import { LoggedAuthGuard } from './guards/logged.guard';
import { PayloadDTO } from './dto/JWTPayload.dto';
import { AuthStatusDTO } from './dto/UserStatus.dto';

@Controller('auth')
export class AuthController {
  constructor(private authService: AuthService) {}

  @UseGuards(AuthGuard('42'))
  @Get()
  async authenticate() {}

  @UseGuards(AuthGuard('42'))
  @Get('login')
  async login(@Req() req, @Res() res) {
    const data = await this.authService.login(req.user);
    res.cookie('Authorization', data.token, { httpOnly: true });
    res.redirect(`${process.env.FE_URL}/`);
  }

  @Post('login-username')
  @UseGuards(NonLoggedAuthGuard)
  async setUsername(
    @Req() req,
    @Res() res,
    @Body('username') username,
    @Body('enable2FA') enable2FA,
  ) {
    try {
      const payload: PayloadDTO = req.user;
      const status = await this.authService.loginWithUsername(
        payload,
        username,
        enable2FA,
      );
      res.cookie('Authorization', status.token, { httpOnly: true });
      res.send({
        redirectURL: status.redirectURL,
        usernameStatus: status.usernameStatus,
      });
    } catch (error) {
      throw new HttpException(error.message, 400, { cause: error });
    }
  }

  @Get('logout')
  @UseGuards(LoggedAuthGuard)
  loggingOut(@Res() res) {
    res.cookie('Authorization', '', { httpOnly: true });
    res.send();
  }

  @Get('checkLogged')
  @UseGuards(LoggedAuthGuard)
  async checkLoggedIn(@Req() req) {
    const user = await this.authService.userService.userPrisma.getUser({id: req.user.id});
    if (user === undefined || user === null) {
      throw new HttpException("Unauthorized", 401);
    }
  }

  @Get('getAuthStatus')
  @UseGuards(NonLoggedAuthGuard)
  async getAuthStatus(@Req() req, @Res() res) {
    const user = await this.authService.userService.userPrisma.getUser({id: req.user.id});
    if (user === undefined || user === null) {
      res.send({authStatus: 4});
    } else {
      res.send({ authStatus: req.user.status });
    }
    
  }

  @Get('qrcode')
  @UseGuards(NonLoggedAuthGuard)
  async generateQrCode(@Req() req, @Res() res) {
    const payload: PayloadDTO = req.user;
    const QRCodeURL = await this.authService.generateQrCode(payload.id);
    res.send(QRCodeURL);
  }

  @Post('verify')
  @UseGuards(NonLoggedAuthGuard)
  async verifyCode(@Req() req, @Res() res, @Body('code') code) {
    try {
      const payload: PayloadDTO = req.user;
      const verified = await this.authService.verifyCode(payload.id, code);
      if (!verified) {
        res.send({ valid: 'False' });
      } else {
        payload.status = AuthStatusDTO.stage_completed;
        const newJWTToken = this.authService.cookieService.getJWTToken(payload);
        res.cookie('Authorization', newJWTToken, { httpOnly: true });
        res.send({ valid: 'True' });
      }
    } catch(error) {
      res.send({ valid: 'False' });
    }
  }
}
