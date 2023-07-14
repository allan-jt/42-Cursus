import React, { useState, useEffect, useContext } from "react";
import style from "./style.module.css";
import HeaderComponent from "../../components/Header/index";
import LeftComponent from "./leftComponent";
import RightComponent from "./rightComponent/index";
import { io, Socket } from "socket.io-client";
import { useLocation } from "react-router-dom";
import { SocketContext, InviteProps } from "../../SocketProvider";
import GamePopUp from "../../components/gameInvitePopup/gamePopUp";
import useGamePopUp from "../../components/gameInvitePopup/useGamePopUp";
import Invite from "../../components/gameInvitePopup/invite";

function ChatPage() {
  const mainSocket = useContext(SocketContext);
  const { isGameInviteOpen, handleOpen, handleClose } = useGamePopUp();
  const [socket, setSocket] = useState<Socket>();
  const [selectedChannel, setSelectedChannel] = useState({});
  const location = useLocation();
  const id = location.state ? location.state.type : null;
  const [friendId] = useState<number | null>(id ?? null);
  const [inviteData, setInviteData] = useState<InviteProps | null>(null);

  useEffect(() => {
    if (mainSocket) {
      mainSocket.on("receiveInvite", (data: any) => {
        setInviteData(data);
        handleOpen();
      });
    }
  }, [mainSocket, handleOpen]);

  useEffect(() => {
    if (mainSocket) {
      mainSocket.on("closePopUp", () => {
        handleClose();
      });
    }
  }, [mainSocket, handleClose]);

  useEffect(() => {
    if (mainSocket) {
      mainSocket.on("closePopUp", () => {
        handleClose();
      });
    }
  }, [mainSocket, handleClose]);

  const handleChannelSelect = (channel: any) => {
    setSelectedChannel(channel);
  };

  useEffect(() => {
    const newSocket = io(`${process.env.REACT_APP_HOST_URL}/chat`, {
      withCredentials: true,
      transports: ["websocket"],
    });
    setSocket(newSocket);

    return () => {
      newSocket.disconnect();
    };
  }, []);

  if (friendId !== null || friendId !== undefined) {
    // console.log("I am here");
    if (socket) {
      socket.emit("chatWithUser", JSON.stringify({ other_user_id: friendId }));
      socket.on("chatWithUserRes", (data: any) => {
        return JSON.parse(data).channel_id;
      });
    }
  }

  useEffect(() => {
    // console.log("and here");
    if (friendId !== null || friendId !== undefined) {
      // console.log("in condition one");
      if (socket) {
        // console.log("in condition two");
        socket.emit(
          "chatWithUser",
          JSON.stringify({ other_user_id: friendId })
          );
          socket.on("chatWithUserRes", (data: any) => {
          });
          // console.log("two");

      }
    }
  }, [friendId, socket]);

  useEffect(() => {
    if (socket) {
      socket.on("disconnect", (data: any) => {
        // navigate("/");
      });
    }
  }, [socket]);

  return (
    <div className={style["ChatPage"]}>
      <HeaderComponent />
      <div className={style["chatroom_msg"]}>
        {socket && (
          <div className={style["chatRooms"]}>
            <LeftComponent
              socket={socket}
              handleChannelSelect={handleChannelSelect}
            />
          </div>
        )}
        {socket && (
          <div className={style["msgs"]}>
            <RightComponent socket={socket} selectedChannel={selectedChannel} />
          </div>
        )}
      </div>
      <GamePopUp
        isGameInviteOpen={isGameInviteOpen}
        handleOpen={handleOpen}
        handleClose={handleClose}
      >
        {mainSocket && inviteData ? (
          <Invite
            socket={mainSocket}
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

export default ChatPage;
