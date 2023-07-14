import { Controller, Post, Body, UseGuards } from '@nestjs/common';
import { LoggedAuthGuard } from 'src/auth/guards/logged.guard';
import { Invite } from 'src/sessions/dto/invite.dto';

@Controller('game')
export class GameController {
  public static gameType: string;
  public static gameInviteData: Invite;

  @Post('setType')
  @UseGuards(LoggedAuthGuard)
  setGameType(@Body() gameType: string): void {
    const type = gameType['gameType'];
    if (type && (type == 'invite' || type == 'random' || type == 'bot')) {
      GameController.gameType = gameType;
    }
  }

  @Post('inviteDTO')
  @UseGuards(LoggedAuthGuard)
  checkDTO(@Body() inviteDTO: any): void {
    try {
      this.checkKeys(
        inviteDTO.invite,
        'inviterName',
        'inviteeName',
        'status',
        'accept',
      );
      GameController.gameInviteData = inviteDTO;
    } catch (error) {
      console.log(error);
    }
  }

  async getGameType(): Promise<string> {
    return GameController.gameType;
  }

  async getInviteDTO(): Promise<Invite> {
    return GameController.gameInviteData;
  }

  clearInviteData(): void {
    GameController.gameInviteData = undefined;
  }

  checkKeys(json: any, ...keys: string[]) {
    for (let i = 0; i < keys.length; i++) {
      if (keys[i] in json === false) {
        throw new Error(
          `Invalid payload - Key '${keys[i]}' is missing in the JSON.`,
        );
      }
    }
  }
}
