import { Injectable } from '@nestjs/common';
import {
  Ball,
  Paddle,
  GameDTO,
  TwoDimension,
  GAME_WIDTH,
  GAME_HEIGHT,
} from './dto/game.dto';
import { getPlayer } from './game.service';

@Injectable()
export class BallService {
  private GAME_SIZE: TwoDimension;
  private SPEED_FACTOR: number;
  private MAX_BALL_SPEED: number;
  private ballSpeedCooldown: number;
  private smashCooldown: number;
  private smashed: boolean;

  constructor() {
    this.GAME_SIZE = { x: GAME_WIDTH, y: GAME_HEIGHT };
    this.SPEED_FACTOR = 1.001;
    this.MAX_BALL_SPEED = 5;
    this.ballSpeedCooldown = 15;
    this.smashCooldown = 30;
    this.smashed = false;
  }

  incrementBallVector(ballDirection: TwoDimension): void {
    if (Math.abs(ballDirection.x) < this.MAX_BALL_SPEED) {
      ballDirection.x *= this.SPEED_FACTOR;
      ballDirection.y *= this.SPEED_FACTOR;
    }
  }

  didBallPassTheCenterLine(ball: Ball) {
    const centerLine = GAME_WIDTH / 2;
    return (
      (ball.collisionX < centerLine && ball.position.x >= centerLine) ||
      (ball.collisionX > centerLine && ball.position.x <= centerLine)
    );
  }

  updateBallPosition(ball: Ball): void {
    ball.position.x += ball.direction.x;
    ball.position.y += ball.direction.y;

    if (ball.collisionX && this.didBallPassTheCenterLine(ball)) {
      ball.collisionX = 0;
    }
  }

  atWall(ball: Ball, isTopWall: boolean): boolean {
    return isTopWall
      ? ball.position.y - ball.radius <= 0
      : ball.position.y + ball.radius >= this.GAME_SIZE.y;
  }

  isBallWithinPaddleHeight(ballPosition: TwoDimension, paddle: Paddle) {
    return (
      ballPosition.y >= paddle.position.y &&
      ballPosition.y <= paddle.position.y + paddle.height
    );
  }

  atPaddle(
    ballPosition: TwoDimension,
    paddle: Paddle,
    isPlayer1Paddle: boolean,
  ): boolean {
    const ballPositionX = isPlayer1Paddle
      ? ballPosition.x <= paddle.position.x + paddle.width * 2
      : ballPosition.x >= GAME_WIDTH - paddle.width * 2;

    return ballPositionX && this.isBallWithinPaddleHeight(ballPosition, paddle);
  }

  checkBallSpeed(game: GameDTO) {
    if (game.ball.direction.x > this.MAX_BALL_SPEED) {
      game.ball.direction.x = this.MAX_BALL_SPEED;
    }
  }

  isSmash(game: GameDTO) {
    const ballOnLeftSide = game.ball.position.x < GAME_WIDTH / 2;
    const ballOnRightSide = game.ball.position.x >= GAME_WIDTH / 2;

    if (ballOnLeftSide && !game.player1.powerUp.smash && this.smashed) {
      this.smashed = false;
      return true;
    }
    if (ballOnRightSide && !game.player2.powerUp.smash && this.smashed) {
      this.smashed = false;
      return true;
    }
    return false;
  }

  flipBallDirection(game: GameDTO): void {
    if (
      !game.ball.collisionX &&
      (this.atPaddle(game.ball.position, game.player2.paddle, false) ||
        this.atPaddle(game.ball.position, game.player1.paddle, true))
    ) {
      this.checkBallSpeed(game);
      game.ball.direction.x *= this.isSmash(game) ? -3 : -1;
      game.ball.collisionX = game.ball.position.x;
    }

    if (this.atWall(game.ball, true) || this.atWall(game.ball, false)) {
      game.ball.direction.y *= -1;
    }
  }

  resetBall(ball: Ball): void {
    ball.position = { x: GAME_WIDTH / 2, y: GAME_HEIGHT / 2 };
    ball.direction = {
      x: getRandomHorizontalDirection(),
      y: getRandomVerticalDirection(),
    };
  }

  async startTimer(time: number) {
    await new Promise((resolve) => setTimeout(resolve, time * 1000));
  }

  async getBallInterval(ball: Ball, speed: number) {
    let i = 0;
    var interval = setInterval(() => {
      if (i < 5) {
        ball.direction.x *= speed;
        ball.direction.y *= speed;
        i++;
      }
    });
    await this.startTimer(1.5);
    clearInterval(interval);
  }

  async decreaseSpeed(game: GameDTO, socketID: string) {
    const player = getPlayer(game, socketID);
    if (!player || !player.powerUp.slowDownBall) {
      return;
    }

    player.powerUp.slowDownBall = false;
    if (Math.abs(game.ball.direction.x) > 1) {
      await this.getBallInterval(game.ball, 1 / 1.5);
      await this.getBallInterval(game.ball, 1.25);
    }
    await this.startTimer(this.ballSpeedCooldown);
    player.powerUp.slowDownBall = true;
  }

  async smash(game: GameDTO, socketID: string) {
    const player = getPlayer(game, socketID);
    if (!player || !player.powerUp.smash) {
      return;
    }

    player.powerUp.smash = false;
    this.smashed = true;
    await this.startTimer(this.smashCooldown);
    player.powerUp.smash = true;
    this.smashed = false;
  }
}

export function getRandomHorizontalDirection() {
  return Math.random() < 0.5 ? -1 : 1;
}

export function getRandomVerticalDirection() {
  const isPositive = Math.random() < 0.5;
  const direction = Math.random() * 0.7 + 0.3;
  return isPositive ? direction : -direction;
}
