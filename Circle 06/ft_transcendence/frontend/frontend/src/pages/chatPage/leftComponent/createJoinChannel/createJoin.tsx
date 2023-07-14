import React, { useState } from "react";
import style from "../../style.module.css";
import UsePopUp from "./usePopUp";
import PopUp from "./popUp";
import Join from "./join";
import Create from "./create";
import JoinIcon from "../../../../assets/search.png";
import { Socket } from "socket.io-client";

interface myProps {
  socket: Socket;
  handleChannelSelect: (channel: any) => void;
}

const CreateJoin = (prop: myProps) => {
  const { isOpen, toggleOn, toggleOff } = UsePopUp();
  const [buttonType, setButtonType] = useState("");

  const handleClick = (event: any, value: string) => {
    setButtonType(value);
  };

  return (
    <div className={style["AddJoinButtons"]}>
      <div>
        <button
          onClick={toggleOn}
          onClickCapture={(event) => handleClick(event, "join")}
        >
          <img src={JoinIcon} alt="join icon" />
        </button>
        <p className={style["buttonsDescription"]}>Search for a channel</p>
      </div>

      <div>
        <button
          onClick={toggleOn}
          onClickCapture={(event) => handleClick(event, "create")}
        >
          +
        </button>
        <p className={style["buttonsDescription"]}>Create a channel</p>
      </div>

      <PopUp isOpen={isOpen} toggleOn={toggleOn} toggleOff={toggleOff}>
        {buttonType === "create" ? (
          <Create socket={prop.socket} toggleOff={toggleOff}/>
        ) : (
          <Join socket={prop.socket}  toggleOff={toggleOff}  handleChannelSelect={prop.handleChannelSelect}/>
        )}
      </PopUp>
    </div>
  );
};

export default CreateJoin;
