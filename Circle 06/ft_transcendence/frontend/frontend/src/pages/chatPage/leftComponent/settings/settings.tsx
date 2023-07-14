import React, { useState, useEffect } from "react";
import style from "../../style.module.css"
import { Socket } from "socket.io-client";
import Pass from "./pass"
import UseSmallPopUp from './smallPopUp/useSmallPopUp'
import UsePopUp from "./InvitePopUp/usePopUp";
import PopUp from "./InvitePopUp/PopUp";
import SmallPopUp from './smallPopUp/smallPopUp'
import Options from "./options";
import MuteIcon from '../../../../assets/mute.png'
import BanIcon from '../../../../assets/ban.png'
import Invite from "./invite";
import { useNavigate } from 'react-router-dom';

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

interface Channel {
  name: string;
  isDirect: boolean;
  isPublic: boolean;
  id: number;
  createdAt: Date;
}

interface myProps {
  socket: Socket;
  currentChannel: Channel | undefined;
  handleChannelSelect: (channel: any) => void;
  toggleOff: () => void;
}

const Settings = (props: myProps) => {
  const { isSmallOpen, handleOpen, handleClose } = UseSmallPopUp();
  const { isInviteOpen, handleInviteOpen, handleInviteClose } = UsePopUp();
  const [currParticipant, setCurrParticipant] = useState<ParticipantProps>();
  const [allParticipants, setAllParticipants] = useState<ParticipantProps[]>([]);
  const [user, setUser] = useState<ParticipantProps>();
  const channelId = props.currentChannel?.id;
  const navigate = useNavigate();

  useEffect(() => {
    if (user && typeof channelId === 'number'){
      const payload = {
        channel_id: channelId,
        user_id: user.participant.id,
        password: "",
      };
      props.socket.emit("getParticipantsInChannel", JSON.stringify(payload));
      props.socket.on("participantsInChannel", (data: any) => {
        const participants = JSON.parse(data);
        const sortedParticipants = participants.sort((a: any, b: any) => a.participant.username.localeCompare(b.participant.username)); 
        setAllParticipants(sortedParticipants);
      });
    }
  }, [isSmallOpen, allParticipants, channelId, user, props.socket]);

  useEffect(() => {
    if (typeof channelId === 'number') {
      const payload = {
        channel_id: channelId,
        password: "",
      };
      props.socket.emit("getMyParticipant", JSON.stringify(payload));
      props.socket.on("myParticipant", (data: any) => {
        const myParticipants = JSON.parse(data);
        setUser(myParticipants);
      });
    }
  }, [channelId, user?.participant.id, props.socket]);

  const getCurrentMember = (par: ParticipantProps) => {
    setCurrParticipant(par);
    if (par.participant.id === user?.participant.id)
      return;
    if (user?.role === 'MEMBER' || par.role === 'OWNER')
      navigate("/user", { state: { type: par.participant.id } });
    handleOpen();
  }

  const HandleInvitePopUpOpen = () => {
    handleInviteOpen();
  }

  const handlePopupClose = () => {
    handleClose();
  };

  const HandleDelete = () => {
    if (user && typeof channelId === 'number'){
      const payload = {
        channel_id: channelId,
        user_id: user.participant.id,
      };
      props.socket.emit("deleteChannel", JSON.stringify(payload));
      props.handleChannelSelect(undefined);
      props.toggleOff();

    }
  }

  const HandleLeave = () => {
    if (user && typeof channelId === 'number'){
      const payload = {
        channel_id: channelId,
        user_id: user?.participant.id,
      };
      props.socket.emit("leaveChannel", JSON.stringify(payload));
      props.handleChannelSelect(undefined);
      props.toggleOff();
    }
  }

  return (
    <div className={style["settingsBox"]}>
      {/* <h2 className={style["settingsTitle"]}>channel settings</h2> */}
      <div className={style["settingsTypes"]}></div>

      {/*  */}
      <h2 className={style["membersTitle"]}>Participants</h2>
      <div className={style["membersBox"]}>
        {allParticipants.map((part: ParticipantProps) =>{
          return(
            <div 
              key={part.participant.id} 
              className={style["member"]} 
              onClick={() => getCurrentMember(part)}
            >
              <div>
              <h4> {part.participant.username} </h4>
              {(part.isBanned === true)? 
                  <img src={BanIcon} className={style["banIcon"]} alt="banIcon"></img>
                :
                  <></>
                }
                {(part.isMuted === true)? 
                  <img src={MuteIcon} className={style["muteIcon"]} alt="muteIcon"></img>
                :
                  <></>
                }
                </div>
                {(part.role === 'OWNER')? 
                <p>owner</p>: (part.role === 'ADMIN')? 
                <p>Admin</p>: <p>member</p>  }
            </div>
          );
        })}
      </div>

      {(user?.role === 'OWNER')? (
        <Pass 
          socket={props.socket} 
          currentChannel={props.currentChannel}
					close={props.toggleOff}
        />
      ):(
        <></> 
      )}

      {(user?.role === 'OWNER' && props.currentChannel?.isPublic !== true)? (
        <div className={style["ownerButtons"]}>
          <button 
            className={style["DeleteLeave"]} 
            onClick={HandleInvitePopUpOpen}
          >
            Invite
          </button> 
          <button className={style["DeleteLeave"]} onClick={HandleDelete}>
            Delete Channel
          </button>
          </div>
      ):(user?.role === 'OWNER')? (
        <button className={style["DeleteLeave"]} onClick={HandleDelete}>
          Delete Channel
        </button> 
      ):(
        <button className={style["DeleteLeave"]} onClick={HandleLeave}>
          Leave Channel
        </button> 
      )}

      {(user?.role === 'MEMBER' ||  currParticipant?.role === 'OWNER' || user?.participant.id === currParticipant?.participant.id)? (
        <></>
      ):(
        <SmallPopUp 
          isSmallOpen={isSmallOpen} 
          handleOpen={handleOpen} 
          handleClose={handleClose}
        >
          <Options 
            socket={props.socket} 
            currentChannel={props.currentChannel} 
            participant={currParticipant}
            myParticipant={user}
            close={handlePopupClose}
          />
        </SmallPopUp>
      )}

      <PopUp 
        isInviteOpen={isInviteOpen} 
        handleInviteOpen={handleInviteOpen} 
        handleInviteClose={handleInviteClose}
      >
        <Invite 
          socket={props.socket} 
          currentChannel={props.currentChannel}
          close={handleInviteClose}
        />
      </PopUp>

    </div>
  );
}

export default Settings;
