import React from "react";
import style from "../style.module.css";
import { GameDTO } from "../pong/dto/gameDTO";

const PowerUpComponent: React.FC<{ gameData: GameDTO }> = ({ gameData }) => {
  const getImageSource = (powerUp: string) => {
    return powerUp === "Q"
      ? `${process.env.REACT_APP_POWER_UP_1}`
      : powerUp === "W"
      ? `${process.env.REACT_APP_POWER_UP_2}`
      : `${process.env.REACT_APP_POWER_UP_3}`;
  };

  const renderPowerUp = (isAvailable: boolean, powerUp: string) => {
    const status = isAvailable ? "available" : "used";
    return (
      <div
        className={`${style[powerUp]} ${style[status]}`}
        data-powerup={powerUp}
      >
        <img src={getImageSource(powerUp)} alt="power-up"></img>
        <p>{powerUp}</p>
      </div>
    );
  };

  return (
    <div className={style["powerUps"]}>
      {renderPowerUp(gameData.player1.powerUp.expandPaddle, "Q")}
      {renderPowerUp(gameData.player1.powerUp.slowDownBall, "W")}
      {renderPowerUp(gameData.player1.powerUp.smash, "E")}
      {renderPowerUp(gameData.player2.powerUp.smash, "E")}
      {renderPowerUp(gameData.player2.powerUp.slowDownBall, "W")}
      {renderPowerUp(gameData.player2.powerUp.expandPaddle, "Q")}
    </div>
  );
};

export default PowerUpComponent;
