import {
  Body,
  Controller,
  Delete,
  Get,
  HttpException,
  Post,
  Req,
  Res,
  UseGuards,
  Param
} from '@nestjs/common';
import { Request, Response } from 'express';
import { FriendsService } from './friends.service';
import { LoggedAuthGuard } from 'src/auth/guards/logged.guard';


@Controller('friends')
export class FriendsController {
    constructor(private friendService: FriendsService,
    ) {}

    @Get('get')
    @UseGuards(LoggedAuthGuard)
    async getAllFriends(@Req() req: Request, @Res() res: Response) {
      const payload: any = req.user;
      const allFriends = await this.friendService.getAllFriends(payload.id);

      return res.send(allFriends);
    }
  
    @Get('get-online')
    @UseGuards(LoggedAuthGuard)
    async getOnlineFriends(@Req() req: Request, @Res() res: Response) {
      const payload: any = req.user;
      const onlineFriends = await this.friendService.getOnlineFriends(payload.id);

      return res.send(onlineFriends);
    }

    @Get('check-friendship/:id')
    @UseGuards(LoggedAuthGuard)
    async checkFriendship(@Req() req: Request, @Param('id') friendId: string, @Res() res: Response) {
      try {
        const payload: any = req.user;
        const isFriend = await this.friendService.checkFriendship(payload.id, parseInt(friendId, 10));
        return res.send({ isFriend });
      } catch(error) {
        console.log(error);
      }
    }
  
    @Post('add')
    @UseGuards(LoggedAuthGuard)
    async addFriend(@Req() req: Request, @Body('username') username: string, @Res() res: Response) {
      console.log("in add friends");
      const payload: any = req.user;
      try {
        const status = await this.friendService.addFriend(payload.id, username)
        res.send({valid: "True"});
      } 
      catch (error) {
        console.log(error);
        throw new HttpException(error.message, 400, { cause: error });
      }
    }

    @Delete('delete')
    @UseGuards(LoggedAuthGuard)
    async deleteFriend(@Req() req: Request, @Body('id') friendId, @Res() res: Response) {
      try {
        const payload: any = req.user;
        const rmFriend = await this.friendService.deleteFriend(payload.id, parseInt(friendId, 10));
        return res.send(rmFriend);
      } catch (error) {
        console.log(error);
      }
    }
}
