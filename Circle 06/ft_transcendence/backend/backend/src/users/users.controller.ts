import {
  Param,
  Controller,
  Get,
  HttpException,
  Post,
  Query,
  Req,
  Res,
  UseGuards,
  UploadedFile, 
  UseInterceptors,
	Body
} from '@nestjs/common';
import { Request, Response } from 'express';
import { UsersService } from './users.service';
import { LoggedAuthGuard } from 'src/auth/guards/logged.guard';
import { FileInterceptor } from '@nestjs/platform-express';
import { diskStorage } from 'multer';
import { extname } from 'path';
import * as sharp from 'sharp';


@Controller('users')
export class UsersController {
  constructor(private usersService: UsersService) {}

  @Get('get')
  @UseGuards(LoggedAuthGuard)
  async getData(@Req() req: Request, @Query('search') attributes: string) {
    const payload: any = req.user;
    await this.usersService.updateGameInfo(payload.id);

    return this.usersService.getData(payload.id, attributes);
  }

  @Get('get-all')
  @UseGuards(LoggedAuthGuard)
  async getAllUsers(@Req() req: Request, @Query('search') attributes: string) {
    const payload: any = req.user;

    return this.usersService.getAllUsers(payload.id);
  }

  @Get('get-all-users')
  @UseGuards(LoggedAuthGuard)
  async getListAllUsers(@Query('attributes') attributes: string, @Res() res: Response) {
    const listUsers = await this.usersService.getListAllUsers(attributes)
    
    return res.send(listUsers);
  }

  @Get('get-all-other-users')
  @UseGuards(LoggedAuthGuard)
  async getListOtherUsers(@Req() req: Request, @Query('attributes') attributes: string, @Res() res: Response) {
    const listUsers = await this.usersService.getListAllUsers(attributes)
    const payload: any = req.user;

    const modifiedListUsers = (listUsers as any[]).filter((user) => user.id !== payload.id);

    console.log(modifiedListUsers);

    return res.send(modifiedListUsers);
  }

  @Post('set')
  @UseGuards(LoggedAuthGuard)
  async setData(@Req() req: Request, @Query() attributes, @Res() res: Response) {
    const payload: any = req.user;
    try {
      await this.usersService.setData(payload.id, attributes);
    } catch (error) {
      throw new HttpException(error.message, 400, { cause: error });
    }

    return res.send ({
      message: 'ok'
    });
  }

  @Get('other/:id')
  @UseGuards(LoggedAuthGuard)
  async findOne(@Param('id') id: string, @Query('attributes') attributes: string, @Res() res: Response) {
    await this.usersService.updateGameInfo(parseInt(id, 10));
    const userData = await this.usersService.getData(parseInt(id, 10), attributes);

    return res.send(userData);
  }

  @Post('set-avatar')
  @UseGuards(LoggedAuthGuard)
  @UseInterceptors(FileInterceptor('file', {
    storage: diskStorage({
      destination: './images',
      filename: (req, file, cb) => {
        const payload: any = req.user;
        const newDate: Date = new Date();
        const avatarName = `${payload.id}${newDate.getMonth()}`;
        cb(null, `${avatarName}${extname(file.originalname)}`);
      }
    })
  }))
  async setAvatar(@UploadedFile() file, @Req() req: Request, @Res() res: Response) {
    const payload: any = req.user;
    try {
      await this.usersService.setData(payload.id, {'image': file.filename});
    } catch (error) {
      throw new HttpException(error.message, 400, { cause: error });
    }

    return res.send ({
      message: 'File uploaded successfully'
    });
  }

  @Get('get-achievements')
  @UseGuards(LoggedAuthGuard)
  async getAchievements(@Req() req: Request, @Res() res: Response) {
    const payload: any = req.user;
    const achievements = await this.usersService.getData(payload.id, "achievements");
    if (!achievements || !achievements.achievements) {
      return res.send([]);
    }
    
    return res.send(achievements.achievements);
  }

  @Get('get-matches')
  @UseGuards(LoggedAuthGuard)
  async getMatchesHistory(@Req() req: Request, @Res() res: Response) {
    const payload: any = req.user;
    const matchesLog = await this.usersService.MatchesHistory(payload.id);

    return res.send(matchesLog);
  }

	@Post('block-user')
	@UseGuards(LoggedAuthGuard)
	async blockUser(@Req() req: Request, @Body('id') id: string, @Res() res: Response) {
		try {
      const payload: any = req.user;
		  const block = await this.usersService.blockUser(payload.id, parseInt(id));
		  return res.send(block);
    } catch(error) {
      //console.log(error);
    }
	}

	@Post('unblock-user')
	@UseGuards(LoggedAuthGuard)
	async unblockUser(@Req() req: Request, @Body('id') id: string, @Res() res: Response) {
		try {
      const payload: any = req.user;
      const unblock = await this.usersService.unblockUser(payload.id, parseInt(id));
      return res.send(unblock);
    } catch(error) {
    //  console.log(error);
    }
	}

	@Get('get-blocked-users')
	@UseGuards(LoggedAuthGuard)
	async getBlockedUsers(@Req() req: Request, @Res() res: Response) {
		try {
      const payload: any = req.user;
      const blockedUsers = await this.usersService.getBlockedUsers(payload.id);
      return res.send(blockedUsers);
    } catch(error) {
     // console.log(error);
    }
	}

	@Get('am-i-blocked')
	@UseGuards(LoggedAuthGuard)
	async amIBlocked(@Req() req: Request, @Query('id') id: string, @Res() res: Response) {
    try {
      const payload: any = req.user;
      const amIBlocked = await this.usersService.amIBlockedByUser(parseInt(id), payload.id);
      return res.send(amIBlocked);
    } catch(error) {
      //console.log(error);
    }
	}
}
