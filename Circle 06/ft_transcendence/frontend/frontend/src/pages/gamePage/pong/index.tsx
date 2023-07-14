import React, { useEffect, useRef, useState } from "react";
import style from "../style.module.css";
import HeaderComponent from "../../../components/Header/index";
import FooterComponent from "../../../components/Footer/index";
import Random from "../random/index";
import PowerUpComponent from "../powerUps";
import ScoreboardComponent from "../scoreboard";
import InfoAndSurrenderComponent from "../infoAndSurrender";
import ResultComponent from "../results";
import UserPhoto from "../../../assets/cat.png";
import BotPhoto from "../../../assets/bot.png";
import buttercup from "../../../assets/buttercup.png";
import { GameDTO, emptyGameDTO } from "./dto/gameDTO";
import type { Socket } from "socket.io-client";
import { io } from "socket.io-client";
import { useNavigate } from "react-router";

export interface UserProps {
  username: string;
  img: string;
  score: number;
  surrender: boolean;
}

interface props {
  gameType: string; // solo or multi
}

interface rectProps {
  x: number;
  y: number;
  width: number;
  height: number;
  color: string;
}

interface circleProps {
  x: number;
  y: number;
  radius: number;
  color: string;
}

function Pong(gameProp: props) {
  const navigate = useNavigate();
  const [isGameOn, setIsGameOn] = useState(true);
  const [socket, setSocket] = useState<Socket>();
  const [gameData, setGameData] = useState<GameDTO>(emptyGameDTO());
  const [isGameReady, setGameReady] = useState(false);

  useEffect(() => {
    const newSocket = io(`${process.env.REACT_APP_HOST_URL}/game`, {
      transports: ["websocket"],
      withCredentials: true,
    });
    setSocket(newSocket);

    return () => {
      newSocket.disconnect();
    };
  }, [gameProp.gameType]);

  useEffect(() => {
    const timer = setTimeout(() => {
      if (gameProp.gameType === "invite" && !isGameReady) {
        navigate("/");
      }
    }, 5000);

    return () => {
      clearTimeout(timer);
    };
  }, [gameProp.gameType, isGameReady, navigate]);

  useEffect(() => {
    if (socket) {
      socket.on("updateGameDTO", (data: GameDTO) => {
        setGameData(data);
        setGameReady(true);
      });
    }
  }, [socket]);

  useEffect(() => {
    if (socket) {
      socket.on("disconnect", (data: any) => {
        navigate("/");
      });
    }
  }, [socket, navigate]);

  const [player1, setPlayer1] = useState({
    username: "P1",
    userImage: UserPhoto,
  });
  const [player2, setPlayer2] = useState({
    username: gameProp.gameType === "solo" ? "BOT" : "P2",
    userImage: gameProp.gameType === "solo" ? BotPhoto : buttercup,
  });
  const [player1Score, setPlayer1Score] = useState(0);
  const [player2Score, setPlayer2Score] = useState(0);
  const canvasRef = useRef<HTMLCanvasElement>(null);

  useEffect(() => {
    if (player1.username === "P1" && gameData.player1.username) {
      setPlayer1({
        username: gameData.player1.username,
        userImage: gameData.player1.image,
      });
    }
    if (player2.username === "P2" && gameData.player2.username) {
      setPlayer2({
        username: gameData.player2.username,
        userImage: gameData.player2.image,
      });
    }
    setPlayer1Score(gameData.player1.score);
    setPlayer2Score(gameData.player2.score);

    if (gameData.status.isGameDone) {
      setIsGameOn(false);
    }

    const windowX = 1100;
    const windowY = 500;
    let scale = window.devicePixelRatio;
    const middleLine = {
      x: windowX / 2 - 1.5,
      y: 0,
      width: 3,
      height: windowY,
      color: "white",
    };

    const canvas = canvasRef.current;
    if (!canvas) {
      return;
    }

    var context = canvas.getContext("2d");
    if (!context) {
      return;
    }

    const movePaddle = (event: KeyboardEvent) => {
      event.preventDefault();
      if (socket && gameData){
        if (event.code === "ArrowUp") {
          socket?.emit("moveUp", gameData.id, socket.id);
        } else if (event.code === "ArrowDown") {
          socket?.emit("moveDown", gameData.id, socket.id);
        } else if (event.key === "q") {
          socket?.emit("increasePaddle", gameData.id, socket.id);
        } else if (event.key === "w") {
          socket?.emit("decreaseBallSpeed", gameData.id, socket.id);
        } else if (event.key === "e") {
          socket?.emit("smash", gameData.id, socket.id);
        }
      }
    };
    window.addEventListener("keydown", movePaddle);

    function drawRect(context: CanvasRenderingContext2D, props: rectProps) {
      context.fillStyle = props.color;
      context.fillRect(props.x, props.y, props.width, props.height);
    }

    function drawBall(context: CanvasRenderingContext2D, props: circleProps) {
      context.fillStyle = props.color;
      context.arc(props.x, props.y, props.radius, 0, 2 * Math.PI);
      context.fill();
    }

    function draw() {
      if (!context) {
        return;
      }

      if (gameData){
        drawRect(context, {
          x: gameData.player1.paddle.position.x,
          y: gameData.player1.paddle.position.y,
          width: gameData.player1.paddle.width,
          height: gameData.player1.paddle.height,
          color: gameData.player1.paddle.color,
        });
        drawRect(context, {
          x: gameData.player2.paddle.position.x,
          y: gameData.player2.paddle.position.y,
          width: gameData.player2.paddle.width,
          height: gameData.player2.paddle.height,
          color: gameData.player2.paddle.color,
        });
        drawRect(context, {
          x: middleLine.x,
          y: middleLine.y,
          width: middleLine.width,
          height: middleLine.height,
          color: middleLine.color,
        });
        drawBall(context, {
          x: gameData.ball.position.x,
          y: gameData.ball.position.y,
          radius: gameData.ball.radius,
          color: gameData.ball.color,
        });
      }
    }

    function scaling() {
      scale = window.devicePixelRatio;

      if (canvas) {
        canvas.width = windowX;
        canvas.height = windowY;
        canvas.width = Math.floor(canvas.width * scale);
        canvas.height = Math.floor(canvas.height * scale);
      }

      if (context) {
        context.scale(scale, scale); // Normalize coordinate system to use css pixels.
      }
    }

    function render() {
      setTimeout(() => {
        scaling();
        draw();
      });
    }

    render();

    return () => {
      window.removeEventListener("keydown", movePaddle);
    };
  }, [player1, player2, socket, gameData]);

  const handleSurrender = () => {
    if (gameData && socket){
      setIsGameOn(false);
      socket?.emit("surrender", gameData.id, socket.id);
    }
  };

  // For results page
  const playerStats = {
    p1: {
      username: gameData.player1.username,
      img: gameData.player1.image,
      score: gameData.player1.score,
      surrender: gameData.player1.surrender,
    },
    p2: {
      username: gameData.player2.username,
      img: gameProp.gameType === "solo" ? BotPhoto : gameData.player2.image,
      score: gameData.player2.score,
      surrender: gameData.player2.surrender,
    },
  };

  return !isGameReady ? (
    <Random />
  ) : isGameOn === true ? (
    <div className={style["GamePage"]}>
      <HeaderComponent />
      <div className={style["wrap"]}>
        <ScoreboardComponent
          gameData={gameData}
          isAgainstBot={gameProp.gameType === "solo"}
          player1Score={player1Score}
          player2Score={player2Score}
        />
        <PowerUpComponent gameData={gameData} />
        <canvas ref={canvasRef} className={style["gameWindow"]} />
        <InfoAndSurrenderComponent handleSurrender={handleSurrender} />
      </div>
      <FooterComponent />
    </div>
  ) : (
    <ResultComponent players={playerStats} />
  );
}

export default Pong;
