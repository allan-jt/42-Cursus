import React, { useState, useEffect, useContext } from "react";
import { useNavigate } from "react-router-dom";
import style from "./style.module.css";
import HeaderComponent from "../../components/Header/index";
import FooterComponent from "../../components/Footer/index";
import character1 from "../../assets/athekkap.png";
import character2 from "../../assets/anasr.png";
import character3 from "../../assets/aalsuwai.png";
import character4 from "../../assets/anifanto.png";
import character5 from "../../assets/gkintana.png";
import { SocketContext, InviteProps } from "../../SocketProvider";
import GamePopUp from "../../components/gameInvitePopup/gamePopUp";
import useGamePopUp from "../../components/gameInvitePopup/useGamePopUp";
import Invite from "../../components/gameInvitePopup/invite";

function HomePage() {
  const socket = useContext(SocketContext);
  const { isGameInviteOpen, handleOpen, handleClose } = useGamePopUp();
  const navigate = useNavigate();
  const [inviteData, setInviteData] = useState<InviteProps>();

  const goToGamePage = () => {
    navigate(`/pong`);
  };

  const goToFriendListPage = () => {
    navigate("/pong", { state: { type: "friend" } });
  };

  const goToRandomPage = () => {
    navigate("/pong", { state: { type: "random" } });
  };

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
        window.location.href = "/login";
      }
    }

    getStatus();
  }, []);

  useEffect(() => {
    if (socket) {
      socket.on("receiveInvite", (data: InviteProps) => {
        setInviteData(data);
        handleOpen();
      });
    }
  }, [socket, inviteData, handleOpen]);

  useEffect(() => {
    if (socket) {
      socket.on("closePopUp", () => {
        handleClose();
      });
    }
  }, [socket, handleClose]);

  return (
    <div className={style["HomePage"]}>
      <HeaderComponent />
      <div className={style["characters"]}>
        <img src={character1} alt="catMermaid"></img>
        <img src={character2} alt="Bubble"></img>
        <img src={character3} alt="Lola"></img>
        <img src={character4} alt="Ana"></img>
        <img src={character5} alt="Sonic"></img>
      </div>
      <div className={style["wrap"]}>
        <button className={style["playFriend"]} onClick={goToFriendListPage}>
          Play with a friend
        </button>
        <button className={style["playRandom"]} onClick={goToRandomPage}>
          Play online match
        </button>
        <button className={style["playAlone"]} onClick={goToGamePage}>
          Play with computer
        </button>
      </div>
      <div className={style["characters_bottom"]}>
        <img src={character1} alt="catMermaid"></img>
        <img src={character2} alt="Bubble"></img>
        <img src={character3} alt="Lola"></img>
        <img src={character4} alt="Ana"></img>
        <img src={character5} alt="Sonic"></img>
      </div>
      <FooterComponent />

      <GamePopUp
        isGameInviteOpen={isGameInviteOpen}
        handleOpen={handleOpen}
        handleClose={handleClose}
      >
        {socket && inviteData ? (
          <Invite
            socket={socket}
            inviterName={inviteData.inviterName}
            inviteeName={inviteData.inviteeName}
            close={handleClose}
          />
        ) : (
          <></>
        )}
      </GamePopUp>
    </div>
  );
}

export default HomePage;
