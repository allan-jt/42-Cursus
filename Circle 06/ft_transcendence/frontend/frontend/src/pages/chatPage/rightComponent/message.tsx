import React from "react";
import style from "./style.module.css";

type MessageProps = {
  message: string;
  time: string | Date;
  isSender: boolean;
  username: string;
  ref?: React.Ref<HTMLDivElement>;
};

const Message = React.forwardRef<HTMLDivElement, MessageProps>(
  (props, ref) => {
    const containerClassName = props.isSender === true ? "sentContainer" : "receivedContainer";
    const messageClassName = props.isSender === true ? "sentMessage" : "receivedMessage";
    const DateTypeTime = (props.time === undefined)? new Date(): new Date(props.time);
    const formattedTime = DateTypeTime.toLocaleTimeString([], { hour: "2-digit", minute: "2-digit" });

    return (
      <div
        className={style[containerClassName]}
        style={{ alignItems: props.isSender ? "flex-end" : "flex-start" }}
        ref={ref}
      >
        <div className={style[messageClassName]}>
          {props.isSender === true ? (
            <></>
          ) : (
            <div className={style["username"]}>{props.username}</div>
           )}
          <p>{props.message}</p>
          <div className={style["time"]}>{formattedTime}</div>
        </div>
      </div>
    );
  }
);

export default Message;
