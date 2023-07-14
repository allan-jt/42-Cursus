import {
  getRandomHorizontalDirection,
  getRandomVerticalDirection,
} from '../game.ball.service';
export const GAME_HEIGHT = 500;
export const GAME_WIDTH = 1100;
export const PADDLE_SPEED = 20;
export const PADDLE_HEIGHT = 80;
const PADDLE_WIDTH = 12;
const BALL_RADIUS = 12;

export class TwoDimension {
  x: number;
  y: number;
}

export class Paddle {
  position: TwoDimension;
  width: number;
  height: number;
  color: string;

  constructor() {
    this.width = PADDLE_WIDTH;
    this.height = PADDLE_HEIGHT;
    this.position = { x: 0, y: GAME_HEIGHT / 2 - PADDLE_HEIGHT / 2 };
  }
}

class PowerUp {
  expandPaddle: boolean;
  slowDownBall: boolean;
  smash: boolean;

  constructor() {
    this.expandPaddle = true;
    this.slowDownBall = true;
    this.smash = true;
  }
}

export class Player {
  ID: string;
  username: string;
  image: string;
  score: number;
  paddle: Paddle;
  surrender: boolean;
  powerUp: PowerUp;

  constructor(id: string, username: string, image: string) {
    this.ID = id;
    this.username = username;
    this.image = image;
    this.score = 0;
    this.paddle = new Paddle();
    this.surrender = false;
    this.powerUp = new PowerUp();
  }
}

export class Ball {
  position: TwoDimension;
  direction: TwoDimension;
  radius: number;
  color: string;
  collisionX: number;

  constructor() {
    this.position = { x: GAME_WIDTH / 2, y: GAME_HEIGHT / 2 };
    this.direction = {
      x: getRandomHorizontalDirection(),
      y: getRandomVerticalDirection(),
    };
    this.radius = BALL_RADIUS;
    this.color = 'yellow';
    this.collisionX = 0;
  }
}

export class GameStatus {
  isRoundDone: boolean;
  isGameDone: boolean;

  constructor() {
    this.isRoundDone = false;
    this.isGameDone = false;
  }
}

export class GameDTO {
  id: string;
  ball: Ball;
  player1: Player;
  player2: Player;
  status: GameStatus;

  constructor(
    gameId: string,
    p1SocketID: string,
    p1Username: string,
    p1Image: string,
    p2SocketID: string,
    p2Username: string,
    p2Image: string,
  ) {
    this.id = gameId;
    this.ball = new Ball();

    this.player1 = new Player(p1SocketID, p1Username, p1Image);
    this.player1.paddle.color = '#98eb9b';

    this.player2 = new Player(p2SocketID, p2Username, p2Image);
    this.player2.paddle.position.x = GAME_WIDTH - PADDLE_WIDTH;
    this.player2.paddle.color = '#92def6';

    this.status = new GameStatus();
  }
}
