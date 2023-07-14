import React, { useState, useEffect } from "react";
import style from "../../style.module.css";
import { Socket } from "socket.io-client";
import UseSmallPopUp from '../settings/smallPopUp/useSmallPopUp';
import SmallPopUp from '../settings/smallPopUp/smallPopUp';


interface Channel {
  name: string;
  isDirect: boolean;
  isPublic: boolean;
  id: number;
  createdAt: Date;
}

export interface JoinChannelProps {
  channel_id: number;
  user_id: number;
  password?: string;
}

interface myProps {
  socket: Socket;
  toggleOff: () => void;
  handleChannelSelect: (channel: any) => void;
}

const JoinChannel = (props: myProps) => {
  const [search, setSearch] = useState("");
  const [inputPassword, setInputPassword] = useState("");
  const { isSmallOpen, handleOpen, handleClose } = UseSmallPopUp();
  const [userData, setUserData] = useState<null | {id: number; username: string;}>(null);
  const [selectedChannel, setSelectedChannel] = useState<Channel | null>(null);
  const [allChannels, setAllChannels] = useState<Channel[]>([]);
  const [channelsList, setChannelsList] = useState<Channel[]>([]);

  useEffect(() => {
    async function fetchData() {
      const response = await fetch(
        `${process.env.REACT_APP_BE_URL}/users/get?search=username+intraLogin+rating+wins+loses+image`,
        {
          method: "GET",
          credentials: "include",
        }
      );
      const json = await response.json();
      setUserData(json);
    }
    fetchData();
  }, []);

  const handleSearchChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    setSearch(event.target.value);
  };

  const handlePasswordInputChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    setInputPassword(event.target.value);
  };

  const handleJoinChannel = async (event: React.MouseEvent, channel: any) => {
    event.preventDefault();
    if (channel !== undefined && typeof channel.id === 'number'){
      setSelectedChannel(channel);
      props.handleChannelSelect(channel);
  
      if (channel.password === ""){
        const joinChannelProps: JoinChannelProps = {
          channel_id: channel.id,
          user_id: channel.user_id,
        };
        props.socket.emit("joinChannel", JSON.stringify(joinChannelProps));
        props.toggleOff();
      }
      else {
        handleOpen();
      };
    }
  };

  const handleJoinChannelWithPassword = () => {
    if (selectedChannel && typeof selectedChannel.id === 'number' && userData) {
      const joinChannelProps: JoinChannelProps = {
        channel_id: selectedChannel.id,
        user_id: userData.id,
        password: inputPassword,
      };
      props.socket.emit("joinChannel", JSON.stringify(joinChannelProps));

    }
  }

  useEffect(() => {
    async function fetchData() {
      props.socket.emit("getAllPublicChannelsNotJoined");
      props.socket.on("allPublicChannelsNotJoined", (data: any) => {
        const channels = JSON.parse(data);
        setAllChannels(channels);
        setChannelsList(channels);
      });
    }

    fetchData();
  }, [channelsList]); // eslint-disable-line react-hooks/exhaustive-deps

  useEffect(() => {
    setChannelsList([]);

    allChannels.filter((val: any) => {
      if (val.name.toLowerCase().includes(search.toLowerCase())) {
        setChannelsList((channelsList) => [...channelsList, val]);
      }
      return (allChannels);
    });
  }, [search, allChannels]);

  return (
    <div>
      <form className={style["joiningBox"]}>
        <h2>Join a channel</h2>
        <input
          className={style["input"]}
          type="text"
          placeholder="Enter group name"
          onChange={handleSearchChange}
        ></input>
        <div className={style["Channel_info_container"]}>
          {channelsList?.map((channel: Channel) => {
            return (
              <button
                key={channel.id.toString()}
                className={style["Channel_info"]}
                onClick={(event) => handleJoinChannel(event, channel)}
              >
                <p>{channel.name}</p>
              </button>
            );
          })}
        </div>
      </form>
      <SmallPopUp
        isSmallOpen={isSmallOpen} 
        handleOpen={handleOpen} 
        handleClose={handleClose}
      >
        <form onSubmit={handleJoinChannelWithPassword}>

          <input
            className={style["input"]}
            type="password"
            placeholder="Enter password"
            style={{width: "100%"}}
            onChange={handlePasswordInputChange}
          ></input>

        </form>
      </SmallPopUp>
    </div>
  );
};

export default JoinChannel;
