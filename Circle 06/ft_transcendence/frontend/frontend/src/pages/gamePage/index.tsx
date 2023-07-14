import React, { useEffect, useState, useContext } from "react";
import { useLocation, useNavigate } from "react-router-dom";
import Pong from "./pong";
import FriendList from "./friendList";
import { SocketContext } from "../../SocketProvider";
import HomePage from "../homePage";

function GamePage() {
  const socket = useContext(SocketContext);
  const location = useLocation();
  const navigate = useNavigate();
  const type = location.state?.type;
  const [gameType, changeGameType] = useState(type ?? "bot");

  useEffect(() => {
    async function setGameType() {
      const response = await fetch(
        `${process.env.REACT_APP_BE_URL}/game/setType`,
        {
          method: "POST",
          credentials: "include",
          headers: {
            "Content-type": "application/json; charset=UTF-8",
          },
          body: JSON.stringify({
            gameType: `${gameType}`,
          }),
        }
      );
      if (!response.ok) {
        navigate("/");
      }
    }
    setGameType();
  }, [gameType, navigate]);

  useEffect(() => {
    if (socket) {
      socket.on("changeGameType", (type: string) => {
        if (type === "invite") {
          changeGameType("invite");
        }
      });
    }
  }, [socket]);

  const selectFriend = () => {
    changeGameType("invite");
    navigate("/pong", { state: { type: "invite" } });
  };

  return (
    <div>
      {(() => {
        switch (gameType) {
          case "friend":
            return <FriendList selectFriend={selectFriend} />;
          case "invite":
            return <Pong gameType="invite" />;
          case "random":
            return <Pong gameType="random" />;
          case "bot":
            return <Pong gameType="solo" />;
          default:
            return <HomePage />;
        }
      })()}
    </div>
  );
}

export default GamePage;
