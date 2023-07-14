import React, { useState, useEffect, useContext } from "react";
import style from "./style.module.css";
import HeaderComponent from "../../components/Header/index";
import Watch from "../../assets/watch.gif";
import { SocketContext, InviteProps } from "../../SocketProvider";
import GamePopUp from "../../components/gameInvitePopup/gamePopUp";
import useGamePopUp from "../../components/gameInvitePopup/useGamePopUp";
import Invite from "../../components/gameInvitePopup/invite";

function WatchPage() {
  const socket = useContext(SocketContext);
  const { isGameInviteOpen, handleOpen, handleClose } = useGamePopUp();
  const [inviteData, setInviteData] = useState<InviteProps>();

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
    <div className={style["body"]}>
      <HeaderComponent />
      <img src={Watch} className={style["watch"]} alt="eyes gif"></img>

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

export default WatchPage;
