interface TwoDimension {
  x: number;
  y: number;
}

interface Paddle {
  position: TwoDimension;
  width: number;
  height: number;
  color: string;
}

export interface PowerUp {
  expandPaddle: boolean;
  slowDownBall: boolean;
  smash: boolean;
}

interface Player {
  username: string;
  image: string;
  score: number;
  paddle: Paddle;
  surrender: boolean;
  powerUp: PowerUp;
}

interface Ball {
  position: TwoDimension;
  radius: number;
  color: string;
}

interface GameStatus {
  isRoundDone: boolean;
  isGameDone: boolean;
}

export interface GameDTO {
  id: string;
  ball: Ball;
  player1: Player;
  player2: Player;
  status: GameStatus;
}

export const emptyGameDTO = (): GameDTO => {
  const windowX = 1100;
  const windowY = 500;

  const initialPlayerConfig = {
    username: "",
    image: "",
    score: 0,
    surrender: false,
  };

  const initialPaddleDimensions = {
    width: 12,
    height: 80,
  };

  const initialPowerUpSettings = {
    expandPaddle: true,
    slowDownBall: true,
    smash: true,
  };

  return {
    id: "",
    ball: {
      position: { x: windowX / 2, y: windowY / 2 },
      radius: 12,
      color: "#ffffff",
    },
    player1: {
      ...initialPlayerConfig,
      paddle: {
        position: { x: 0, y: windowY / 2 - 40 },
        color: "#98eb9b",
        ...initialPaddleDimensions,
      },
      powerUp: {
        ...initialPowerUpSettings,
      },
    },
    player2: {
      ...initialPlayerConfig,
      paddle: {
        position: { x: windowX - 12, y: windowY / 2 - 40 },
        color: "#92def6",
        ...initialPaddleDimensions,
      },
      powerUp: {
        ...initialPowerUpSettings,
      },
    },
    status: {
      isRoundDone: false,
      isGameDone: false,
    },
  };
};
