import React from "react";
import style from "../style.module.css";
import { GameDTO } from "../pong/dto/gameDTO";
import BotPhoto from "../../../assets/bot.png";

const ScoreboardComponent: React.FC<{
  gameData: GameDTO;
  isAgainstBot: boolean;
  player1Score: number;
  player2Score: number;
}> = ({ gameData, isAgainstBot, player1Score, player2Score }) => {
  return (
    <div className={style["playersAndScore"]}>
      <div className={style["player1"]}>
        <img
          className={style["playerImg"]}
          src={gameData.player1.image}
          alt="player1-img"
        ></img>
        <h3>{gameData.player1.username}</h3>
      </div>

      <div className={style["liveScore"]}>
        <h3>{player1Score}</h3>
        <h3>:</h3>
        <h3>{player2Score}</h3>
      </div>

      <div className={style["player2"]}>
        <h3>{gameData.player2.username}</h3>
        <img
          className={style["playerImg"]}
          src={isAgainstBot ? BotPhoto : gameData.player2.image}
          alt="player2-img"
        ></img>
      </div>
    </div>
  );
};

export default ScoreboardComponent;
