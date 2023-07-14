import React, { useEffect } from "react";
import HeaderComponent from "../../../components/Header";
import FooterComponent from "../../../components/Footer/index";
import style from "../style.module.css";
import { UserProps } from "../pong/index";

interface playerProps {
  p1: UserProps;
  p2: UserProps;
}

const ResultComponent: React.FC<{
  players: playerProps;
}> = ({ players }) => {
  function didPlayer1Win(players: playerProps) {
    return (
      players.p2.surrender ||
      (!players.p1.surrender && players.p1.score > players.p2.score)
    );
  }

  useEffect(() => {
    async function getStatus() {
      const response = await fetch(
        `${process.env.REACT_APP_BE_URL}/auth/getAuthStatus`,
        {
          method: "GET",
          credentials: "include",
        }
      );

      if (!response.ok) {
        window.location.href = "/";
      }
    }

    getStatus();
  }, []);

  function ResultSection(styleName: string, player: UserProps) {
    const headerContent =
      styleName === "winner"
        ? "Winner"
        : player.surrender
        ? "Surrender"
        : "Loser";

    return (
      <div className={style[styleName]}>
        <h2>{headerContent}</h2>
        <img src={player.img} alt={player.username + "'s Image"} />
        <p>{player.username}</p>
      </div>
    );
  }

  function ScoreSection(player: playerProps) {
    return (
      <div className={style["scoreResult"]}>
        <div className={style["score"]}>{player.p1.score}</div>
        <div className={style["twoDots"]}> : </div>
        <div className={style["score"]}>{player.p2.score}</div>
      </div>
    );
  }

  const isP1Winner = didPlayer1Win(players);
  const p1Result = ResultSection(isP1Winner ? "winner" : "loser", players.p1);
  const p2Result = ResultSection(isP1Winner ? "loser" : "winner", players.p2);

  return (
    <div className={style["body"]}>
      <HeaderComponent />
      <div className={style["middleBoxResult"]}>
        <div style={{ padding: "0 5%" }}>
          <h1>Game Results</h1>
          <div className={style["playerResultInfo"]}>
            {p1Result}
            {ScoreSection(players)}
            {p2Result}
          </div>
        </div>
      </div>
      <FooterComponent />
    </div>
  );
};

export default ResultComponent;
