import React, { useEffect, useState } from "react";
import style from "../style.module.css";
import { Socket } from "socket.io-client";
import setting from "../../../assets/settings.png";
import Settings from "./settings/settings";
import UsePopUp from "./createJoinChannel/usePopUp";
import PopUp from "./createJoinChannel/popUp";

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
	handleChannelSelect: (channel: any) => void;
}

function Channels(props: myProps) {
  const [channelsList, setChannelsList] = useState<Channel[]>([]);
  const [invitedChannelsList, setInvitedChannelsList] = useState<any[]>([]);
  const [currentChannel, setCurrentChannel] = useState<Channel>();
  const { isOpen, toggleOn, toggleOff } = UsePopUp();
  const [user, setUser] = useState<ParticipantProps>();

  useEffect(() => {
    if (!user && currentChannel && typeof currentChannel.id === "number") {
      const payload = {
        channel_id: currentChannel.id,
        password: "",
      };
      props.socket.emit("getMyParticipant", JSON.stringify(payload));
      props.socket.on("myParticipant", (data: any) => {
        const myParticipants = JSON.parse(data);
        setUser(myParticipants);
      });
    }
  }, [currentChannel, user]); // eslint-disable-line react-hooks/exhaustive-deps

  useEffect(() => {
    props.socket.emit("getAllJoinedChannels", () => {
    });
    props.socket.on("allJoinedChannels", (data: any) => {
      const channels = JSON.parse(data);
      const sortedChannels = channels.sort((a: any, b: any) => a.name - b.name);
      setChannelsList(sortedChannels);
    });
  }, [channelsList]); // eslint-disable-line react-hooks/exhaustive-deps

  useEffect(() => {
	props.socket.emit("getAllChannelsUserIsInvitedTo");
	props.socket.on("allChannelsUserIsInvitedTo", (data: any) => {
	const channels = JSON.parse(data);
	setInvitedChannelsList(channels);
	});
  }, [invitedChannelsList]); // eslint-disable-line react-hooks/exhaustive-deps

  const HandleChannelChange = (id: string) => {
    const btn = document.getElementById(id);
    const backgroundColor = btn?.style.backgroundColor;

    
    //save selected channel
    const selectedChannel = channelsList.filter(
      (channel: Channel) => channel.id.toString() === id
    );
    if (selectedChannel.length === 0) {
      return;
    }
    if ((currentChannel && selectedChannel[0].id !== currentChannel.id) || !currentChannel) {
      setCurrentChannel(selectedChannel[0]);
      props.handleChannelSelect(selectedChannel[0]);

      if (
        btn &&
        (backgroundColor === "rgba(245, 245, 245, 0.25)" ||
          backgroundColor === "")
      ) {
        btn.style.backgroundColor = "rgba(255,255,255 )";
        btn.style.color = "#333456";

        channelsList.map((channel: Channel) => {
          if (channel.id.toString() !== id) {
            const bt = document.getElementById(channel.id.toString());

            if (bt) {
              bt.style.backgroundColor = "rgba(245, 245, 245, 0.25)";
              bt.style.color = "rgba(255,255,255, 0.5)";
            }
          }
          return channelsList;
        }); 
      } else if (btn) {
        btn.style.backgroundColor = "rgba(245, 245, 245, 0.25)";
        btn.style.color = "rgba(255,255,255, 0.5)";
      }
    }
    else if (currentChannel && selectedChannel[0].id === currentChannel.id) {
      props.handleChannelSelect(selectedChannel[0]);
    }
  };


  const getName = (channelName: string, isDirect: boolean) => {
    if (!user || !user.participant)
      return channelName;

    if (isDirect === false)
      return channelName;

    const namesArray = channelName.split("+");

    if (namesArray.length !== 2)
      return channelName;

    return (namesArray[0] !== user?.participant.username)? namesArray[0]: namesArray[1];
  }

  const handleInviteJoin = (channelId: number | undefined) => {
	  if (typeof channelId === 'number'){
      const joinChannelProps = {
        channel_id: channelId,
        user_id: user?.participant.id,
      };
      props.socket.emit("joinChannel", JSON.stringify(joinChannelProps), () => {
      });
    }
  }

  const handleInviteDismiss = (channelId: number) => {
    if (typeof channelId === 'number'){
      const payload = {
        channel_id: channelId,
        user_id: user?.participant.id,
      };
      props.socket.emit("leaveChannel", JSON.stringify(payload));
    }
  }

  return (
    <div className={style["JoinedChannles"]}>
      <div className={style["channles"]}>
        {channelsList.map((channel: Channel, index: number) => {
          const isSelected = currentChannel?.id === channel.id;

            return (
              <button
                key={channel.id}
                id={channel.id.toString()}
                className={`${style["channelInfo"]} ${isSelected ? style["selectedChannel"] : ""}`}
                onClick={() => HandleChannelChange(channel.id.toString())}
              >
                <p>{getName(channel.name, channel.isDirect)}</p>
  
                {
                  (channel.isDirect !== true) ? (
                    <img
                      className={style["setting"]}
                      src={setting}
                      onClick={toggleOn}
                      alt="setting"
                    />
                  ) : (
                    <div key={index * 1000}></div>
                )
              }
              </button>
            );
          }

        )}
      </div>

      <div className={style["invitedChannelsList"]}>
        {invitedChannelsList && invitedChannelsList.length > 0 ? (
          invitedChannelsList.map((channel: any) => (
            (channel.channel)?(
            <div 
              key={channel.channel.id * 500} 
              className={style["invitedChannel"]}
            >
              <p className={style["text"]}>
                you are invited to join  
                <span className={style["name"]}>
                  {channel?.channel?.name}
                </span>
              </p>
              <div>
                <button onClick={() => handleInviteJoin(channel.channel?.id)}>join</button>
                <button onClick={() => handleInviteDismiss(channel.channel?.id)}>dismiss</button>
              </div>
            </div>
            ):(
              <></>
            )
          ))
        ) : (
          <></>
        )}
      </div>

      <PopUp isOpen={isOpen} toggleOn={toggleOn} toggleOff={toggleOff}>
        <Settings 
          socket={props.socket} 
          currentChannel={currentChannel}
          toggleOff={toggleOff}
          handleChannelSelect={props.handleChannelSelect}
          />
      </PopUp>
    </div>
  );
}

export default Channels;
