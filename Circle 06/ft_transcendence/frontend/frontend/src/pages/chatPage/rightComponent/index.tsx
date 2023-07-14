import React, { useState, useRef, useEffect } from "react";
import Message from "./message";
import style from "./style.module.css";
import sendIcon from "../../../assets/send.png";
import playIcon from "../../../assets/gameIcon.png";
import { Socket } from "socket.io-client";
import PopUp from "../leftComponent/createJoinChannel/popUp";
import UsePopUp from "../leftComponent/createJoinChannel/usePopUp";
import InciteToPlay from "./InviteToPlay";
import Logo from "../../../assets/logo+ch.png"

type MessageProps = {
  id: number;
  sender_id: number;
  sender_username: string;
  channel_id: number;
  messageBody: string;
  createdAt: Date;
  sender: {id: number, username: string};
};

interface ParticipantProps {
  channel_id: number;
  id: number;
  isBanned: boolean;
  isMuted: boolean;
  role: string;
  participant: {
    id: number;
    username: string;
  };
}

interface myProps {
  socket: Socket;
  selectedChannel: any;
}

function RightComponent(props: myProps) {
  const { isOpen, toggleOn, toggleOff } = UsePopUp();
  const [input, setInput] = useState("");
  const messagesEndRef = useRef<HTMLDivElement>(null);
  const [msgs, setMsgs] = useState<MessageProps[]>([]);
  const [myParticipant, setMyParticipant] = useState<ParticipantProps>();
  const [blockedUsers, setBlockedUsers] = useState<any>([]);
  // const [amIBlocked, setAmIBlocked] = useState<boolean>(false);

  useEffect(() => {
    async function getIsBlocked() {
      const responseBlock = await fetch(
        `${process.env.REACT_APP_BE_URL}/users/get-blocked-users`,
        {
          method: "GET",
          credentials: "include",
          headers: {
            "Content-Type": "application/json",
          },
        }
      );
      const blockedUsers = await responseBlock.json();
      setBlockedUsers(blockedUsers);
    }
    getIsBlocked();
  }, [blockedUsers.length]);

  useEffect(() => {
    if (props.selectedChannel && typeof props.selectedChannel.id === 'number'){
      
      props.socket.emit(
        "getMyParticipant",
        JSON.stringify({ channel_id: props.selectedChannel.id })
      );
      props.socket.on("myParticipant", (data: any) => {
        const participant = JSON.parse(data);
        setMyParticipant(participant);
      });
    }
  }, [props.selectedChannel, myParticipant]); // eslint-disable-line react-hooks/exhaustive-deps

  useEffect(() => {
    if (props.selectedChannel){
      props.socket.off("messageSent");
      props.socket.on("messageSent", (data: any) => {
        const message = data;
        if (message.channel_id === props.selectedChannel.id) {
          setMsgs((msgs: any) => [...msgs, message]);
        }
      });
    }
  }, [msgs, props.selectedChannel]); // eslint-disable-line react-hooks/exhaustive-deps

  useEffect(() => {
    if (props.selectedChannel && typeof props.selectedChannel.id === 'number') {
      props.socket.emit(
        "getMessagesInChannel",
        JSON.stringify({ channel_id: props.selectedChannel.id })
      );
      props.socket.on("messagesInChannel", (data: any) => {
        const messages = JSON.parse(data);
        setMsgs(messages);
      });
    }
  }, [props.selectedChannel, msgs]); // eslint-disable-line react-hooks/exhaustive-deps

  const handleMsgChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    setInput(event.target.value);
  };

  const HandleSendMsg = (event: any) => {
    event.preventDefault();
    const trimmedMessage = input.trim();
    if (trimmedMessage.length === 0) {
      return ;
    }
    if (input !== "" && typeof props.selectedChannel.id === 'number') {
      props.socket.emit(
        "createMessage",
        JSON.stringify({
          channel_id: props.selectedChannel.id,
          messageBody: input,
        })
      );
      setInput("");
    }
  };

  useEffect(() => {
    if (messagesEndRef.current) {
      messagesEndRef.current.scrollIntoView();
    }
  }, [msgs, props.selectedChannel]);

  const handleKeyDown = (event: React.KeyboardEvent<HTMLInputElement>) => {
    if (event.key === "Enter") {
      HandleSendMsg(event);
    }
  };

  const HandleGameInviteMsg = () => {
    toggleOn();
  };

  const isSenderBlocked = (sender_id: number) => {
    for (let i = 0; i < blockedUsers.length; i++) {
      if (
        blockedUsers[i].blockedUser &&
        sender_id === blockedUsers[i].blockedUser.id
      ) {
        return true;
      }
    }
    return false;
  };

  return (
    (myParticipant && myParticipant.isBanned !== true && props.selectedChannel && props.selectedChannel.name)?
      <div className={style["rightSide"]}>
        <div className={style["msgs"]}>
          {msgs.map((msg: any, index: number) => {
            return !isSenderBlocked(msg.sender_id) && props.selectedChannel && msg.sender ? (
              <Message
                key={msg.id}
                message={msg.messageBody}
                time={msg.createdAt}
                isSender={
                  msg.sender_id === myParticipant?.participant.id ? true : false
                }
                username={msg.sender.username}
                ref={msgs.length - 1 === index ? messagesEndRef : undefined}
              />
            ) : (
              <div key={index * 1000}></div>
            );
          })}
          <div ref={messagesEndRef} />
        </div>

        <div className={style["sendingBox"]}>
          <div>
            <input
              className={style["input"]}
              value={input}
              type="text"
              maxLength={1042}
              placeholder="Enter a message"
              onChange={handleMsgChange}
              onKeyDown={handleKeyDown}
            ></input>
            <button className={style["send"]} onClick={HandleSendMsg}>
              <img src={sendIcon} alt="sendIcon" />
            </button>
          </div>
          <button className={style["GameInvite"]} onClick={HandleGameInviteMsg}>
            <img src={playIcon} alt="playIcon" />
          </button>
        </div>

        <PopUp isOpen={isOpen} toggleOn={toggleOn} toggleOff={toggleOff}>
          <InciteToPlay
            socket={props.socket}
            currentChannel={props.selectedChannel}
          />
        </PopUp>
      </div>
      :
      <div className={style["logo_side"]}>
        <img src={Logo} className={style["logo"]} alt="logo"/>
      </div>
      
  );
}

export default RightComponent;
