import React, { useState, useEffect, useContext } from "react";
import style from "../style.module.css";
import { Socket } from "socket.io-client";
import { InviteStatus, SocketContext } from "../../../SocketProvider";
import { useNavigate } from "react-router";

interface Channel {
  name: string;
  isDirect: boolean;
  isPublic: boolean;
  id: number;
  createdAt: Date;
}

interface ParticipantProps {
  channel_id: number;
  id: number;
  isBanned: boolean;
  isMuted: boolean;
  role: string;
  participant: {
    id: number;
    username: string;
    available: string,
    gameStatus: string,
  };
}

interface myProps {
  socket: Socket;
  currentChannel: Channel | undefined;
}

const InciteToPlay = (props: myProps) => {
  const socket = useContext(SocketContext);
  const navigate = useNavigate();
  const [myParticipant, setMyParticipant] = useState<ParticipantProps>();
  const [membersList, setMembersList] = useState([]);

  useEffect(() => {
    if (props.currentChannel && typeof props.currentChannel.id === 'number'){
      const payload = {
        channel_id: props.currentChannel.id,
        password: "",
      };
      props.socket.emit("getParticipantsInChannel", JSON.stringify(payload));
      props.socket.on("participantsInChannel", (data: any) => {
        const participants = JSON.parse(data);
        const filteredList = participants.filter((participant: ParticipantProps) => (participant.participant.available === 'ONLINE'));
        const sortedList = filteredList.sort((a: any, b: any) => a.participant.username.localeCompare(b.participant.username)); 
        setMembersList(sortedList);
      });
    }
  }, [props.currentChannel, membersList, props.socket]);

  useEffect(() => {
    if (props.currentChannel && typeof props.currentChannel.id === 'number'){
      const payload = {
        channel_id: props.currentChannel.id,
        password: "",
      };
      props.socket.emit("getMyParticipant", JSON.stringify(payload));
      props.socket.on("myParticipant", (data: any) => {
        const Participant = JSON.parse(data);
        setMyParticipant(Participant);
      }); 
    }
  }, [props.currentChannel, props.socket]);

  const handleInviteToGame = (event: any, memberUsername: string) => {
    event.preventDefault();
    const data = {
      inviteeName: memberUsername,
      inviterName: myParticipant?.participant.username,
      status: InviteStatus.invite_sent,
      accept: false,
    };
    socket?.emit("sendInvite", { invite: data });
    navigate("/pong", { state: { type: "invite" } });
  }

  return (
    <div>
      <h2>Available Participants</h2>
      {membersList?.map((member: ParticipantProps) => {
            return (
              (myParticipant?.participant.id !== member.participant.id && member.participant.gameStatus === "AVAILABLE")? 
                <button
                  key={member.id}
                  className={style["Channel_info"]}
                  onClick={(event) => handleInviteToGame(event, member.participant.username)}
                >
                  <p>{member.participant.username}</p>
                </button>
              :
                <></>
              
            );
          })}
      {(membersList.length === 1)?
        <p className={style["error"]}>no available participants</p>
      :
        <></>

      }
    </div>
  );
};

export default InciteToPlay;
