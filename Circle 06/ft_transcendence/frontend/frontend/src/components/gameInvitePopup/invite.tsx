import React, { useState, useContext } from "react";
import { useNavigate } from "react-router";
import style from "./style.module.css";
import { Socket } from "socket.io-client";
import { InviteStatus, SocketContext } from "../../SocketProvider";

interface myProps {
  socket: Socket;
  inviterName: string;
  inviteeName: string;
  close: () => void;
}

const Invite = (props: myProps) => {
  const socket = useContext(SocketContext);
  const navigate = useNavigate();
  const [name] = useState(props.inviterName);

  const HandleJoin = () => {
    if (socket) {
      const inviteDTO = {
        inviterName: props.inviterName,
        inviteeName: props.inviteeName,
        status: InviteStatus.response_received,
        accept: true,
      };
      fetch(`${process.env.REACT_APP_BE_URL}/game/inviteDTO`, {
        method: "POST",
        credentials: "include",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ invite: inviteDTO }),
      });
      socket.emit("receiveInvite", { invite: inviteDTO }, (response: any) => {
        if (response.invite.status === InviteStatus.response_received) {
          navigate("/pong", { state: { type: "invite" } });
        }
      });
      props.close();
    }
  };

  const HandleDismiss = () => {
    if (socket) {
      const inviteDTO = {
        inviterName: props.inviterName,
        inviteeName: props.inviteeName,
        status: InviteStatus.invitee_no_available,
        accept: false,
      };
      socket.emit("receiveInvite", { invite: inviteDTO });
      props.close();
    }
  };

  return (
    <div className={style["wrap"]}>
      <div className={style["text"]}>
        <h1>{name}</h1>
        <p>invites you to a game</p>
      </div>
      <div className={style["buttons"]}>
        <button onClick={HandleJoin}>Join</button>
        <button onClick={HandleDismiss}>Dismiss</button>
      </div>
    </div>
  );
};

export default Invite;
