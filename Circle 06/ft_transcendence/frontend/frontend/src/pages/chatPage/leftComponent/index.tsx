import React from "react";
import style from "../style.module.css";
import Channels from "./channels";
import CreateJoin from "./createJoinChannel/createJoin";
import { Socket } from "socket.io-client";

interface myProps {
  socket: Socket;
  handleChannelSelect: (channel: any) => void;
}

function LeftComponent(props: myProps) {
  return (
    <div className={style["leftSide"]}>
      <Channels
        socket={props.socket}
        handleChannelSelect={props.handleChannelSelect}
      />
      <div>
        <CreateJoin socket={props.socket} handleChannelSelect={props.handleChannelSelect}/>
      </div>
    </div>
  );
}

export default LeftComponent;
