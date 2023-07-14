import React, { useState, useEffect, useContext } from "react";
import style from "../style.module.css";
import HeaderComponent from "../../../components/Header";
import FooterComponent from "../../../components/Footer/index";
import Friends from "./friends";
import { SocketContext, InviteProps } from "../../../SocketProvider";
import GamePopUp from "../../../components/gameInvitePopup/gamePopUp";
import useGamePopUp from "../../../components/gameInvitePopup/useGamePopUp";
import Invite from "../../../components/gameInvitePopup/invite";

interface ButtonProps {
  selectFriend: () => void;
}

function FriendList({ selectFriend }: ButtonProps) {
  const socket = useContext(SocketContext);
  const { isGameInviteOpen, handleOpen, handleClose } = useGamePopUp();
  const [inviteData, setInviteData] = useState<InviteProps>();

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

      <div className={style["middleBox"]}>
        <h1 className={style["availableFriends"]}>Available friends:</h1>
        <Friends selectFriend={selectFriend} />
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

export default FriendList;
