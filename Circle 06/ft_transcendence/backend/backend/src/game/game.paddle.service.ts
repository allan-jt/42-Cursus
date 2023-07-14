import { Injectable } from '@nestjs/common';
import {
  GameDTO,
  Player,
  Paddle,
  GAME_HEIGHT,
  PADDLE_HEIGHT,
} from './dto/game.dto';
import { getPlayer } from './game.service';

@Injectable()
export class PaddleService {
  async sleepThenClear(ms: number, interval: NodeJS.Timer) {
    await new Promise((resolve) => setTimeout(resolve, ms));
    clearInterval(interval);
  }

  async createInterval(time: number, action: () => void) {
    var interval = setInterval(() => {
      action();
    });
    await this.sleepThenClear(time, interval);
  }

  movePaddleUp(player: Player, index: number) {
    if (player.paddle.position.y > 0 && index < 100) {
      player.paddle.position.y -= 0.775;
      index++;
    }
  }

  movePaddleDown(paddleEnd: number, player: Player, index: number) {
    if (paddleEnd < GAME_HEIGHT && index < 100) {
      player.paddle.position.y += 0.775;
      index++;
    }
  }

  async handleUpKey(game: GameDTO, socketID: string) {
    const player = getPlayer(game, socketID);
    if (!player) {
      return;
    }

    let i = 0;
    this.createInterval(50, () => this.movePaddleUp(player, i));
  }

  async handleDownKey(game: GameDTO, socketID: string) {
    const player = getPlayer(game, socketID);
    if (!player) {
      return;
    }
    const paddleEnd = player.paddle.position.y + player.paddle.height;

    let i = 0;
    this.createInterval(50, () => this.movePaddleDown(paddleEnd, player, i));
  }

  increasePaddleHeight(paddle: Paddle) {
    if (paddle.height < PADDLE_HEIGHT * 2) {
      paddle.position.y -= 0.5;
      paddle.height++;
    }
  }

  decreasePaddleHeight(paddle: Paddle) {
    if (paddle.height > PADDLE_HEIGHT) {
      paddle.position.y += 0.5;
      paddle.height--;
    }
  }

  async increaseSize(game: GameDTO, socketID: string) {
    const player = getPlayer(game, socketID);
    if (!player || !player.powerUp.expandPaddle) {
      return;
    }

    player.powerUp.expandPaddle = false;
    await this.createInterval(3000, () =>
      this.increasePaddleHeight(player.paddle),
    );
    await this.createInterval(10000, () =>
      this.decreasePaddleHeight(player.paddle),
    );
    player.powerUp.expandPaddle = true;
  }
}
