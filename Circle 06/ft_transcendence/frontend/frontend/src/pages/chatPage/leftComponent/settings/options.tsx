import React, { useCallback, useState } from "react";
import style from "../../style.module.css";
import { Socket } from "socket.io-client";
import { useNavigate } from 'react-router-dom';

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
  };
}

interface myProps {
  socket: Socket;
  currentChannel: Channel | undefined;
  participant: ParticipantProps | undefined;
  myParticipant: ParticipantProps | undefined;
  close: () => void;
}

const Options = (props: myProps) => {
  const navigate = useNavigate();
  const [isMuteOn, setIsMuteOn] = useState(false);
  const [muteDuration, setMuteDuration] = useState('');
  const [error, setError] = useState('');

  const addAdmin = () => {
    if  (props.currentChannel){
      const payload = {
        channel_id: props.currentChannel?.id,
        user_id: props.participant?.participant.id,
      };
      props.socket.emit("addAdmin", JSON.stringify(payload));
      props.close();
    }
  };

  const removeAdmin = () => {
    const payload = {
      channel_id: props.currentChannel?.id,
      user_id: props.participant?.participant.id,
    };
    props.socket.emit("removeAdmin", JSON.stringify(payload));
    props.close();
  };

  const handleBanUser = () => {
    if (props.currentChannel && props.participant){
      const payload = {
        channel_id: props.currentChannel.id,
        user_id: props.participant.participant.id,
      };
      props.socket.emit("banUser", JSON.stringify(payload));
      props.close();

    }
  };

  const handleUnbanUser = () => {
    if (props.currentChannel && props.participant){
      const payload = {
        channel_id: props.currentChannel.id,
        user_id: props.participant.participant.id,
      };
      props.socket.emit("unbanUser", JSON.stringify(payload));
      props.close();
    }
  };

  const handleUnmute = () => {
    if (props.currentChannel && props.participant){
      const payload = {
        channel_id: props.currentChannel.id,
        user_id: props.participant.participant.id,
      };
      props.socket.emit("unmuteUser", JSON.stringify(payload));
      props.close();
    }
  }

  const handleMute = (e: any) => {
    setIsMuteOn(!isMuteOn);
  };

  const handleFormSubmit = (event: React.FormEvent<HTMLFormElement>) => {
		event.preventDefault();
		if (error !== '')
			return ;
		if (props.currentChannel && props.participant){
			props.socket.emit('muteUser', JSON.stringify({
				channel_id: props.currentChannel.id,
				user_id: props.participant.participant.id,
				muteDuration: muteDuration
			}))
			props.close();
		}
  };

  const handleMinutesChange = (event: React.ChangeEvent<HTMLInputElement>) => {
		const inputValue = event.target.value;
  
  if (inputValue === '' || /^(?:[1-9]|[1-9][0-9]|[12][0-3][0-9]|240)$/.test(inputValue)) {
    setMuteDuration(inputValue);
    setError('');
  } else {
    setError('Please enter a whole number between 1 and 240.');
  }
  };

  const kickParticipant = () => {
    if (props.currentChannel && props.participant){
      const payload = {
        channel_id: props.currentChannel.id,
        user_id: props.participant.participant.id,
      };
      props.socket.emit("kickUser", JSON.stringify(payload));
      props.close();
    }
  };

	const goToProfile = useCallback(() => {
		if (props.participant === undefined)
			return ;
		else
			navigate("/user", { state: { type: props.participant.participant.id } });
	}, [props.participant, navigate]);

  return (
    <div className={style["options"]}>
      {props.participant?.isBanned === true?
        <></>
        :
        (props.participant?.isMuted === true ? (
        <h2 className={style["option_top"]} onClick={handleUnmute}>
          Unmute
        </h2>
      ) : (
        <div className={style["option_top"]}>
          <h2 onClick={handleMute}>Mute</h2>
          {isMuteOn === true ? (
            <form onSubmit={handleFormSubmit}>
            <input 
              type="text"
              className={style["input"]}
              placeholder="Duration in Minutes"
              onChange={handleMinutesChange}
							maxLength={3}
            />
          </form>
          ) : (
            <></>
          )}
				<h3 className={style['Error']}>{error}</h3>
        </div>
      ))}
      {props.participant?.isBanned === true ? (
        <h2 className={style["option"]} onClick={handleUnbanUser}>
          Unban
        </h2>
      ) : (
        <h2 className={style["option"]} onClick={handleBanUser}>
          Ban
        </h2>
      )}
      {props.participant?.isBanned === true ?
        <></>
        :
        <h2 className={style["option"]} onClick={kickParticipant}>
          Kick
        </h2>
      }
      {props.participant?.isBanned === true?
        <></>
        :
        props.myParticipant?.role === "OWNER" ? (
        props.participant?.role === "ADMIN" ? (
          <h2
            className={style["option"]}
            onClick={removeAdmin}
          >
            Remove admin
          </h2>
        ) : (
          <h2 className={style["option"]} onClick={addAdmin}>
            Make admin
          </h2>
        )
      ) : (
        <></>
      )}

				<h2 className={style["option"]} onClick={goToProfile}>
        	View Profile
      	</h2>
    </div>
  );
};

export default Options;
