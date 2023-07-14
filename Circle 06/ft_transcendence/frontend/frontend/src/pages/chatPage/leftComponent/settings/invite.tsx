import React, { useEffect, useState } from "react";
import style from "../../style.module.css";
import { Socket } from "socket.io-client";

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
  close: () => void;
}

interface ParticipantProps {
  id: number;
  username: string;
}

const Invite = (props: myProps) => {
  const [search, setSearch] = useState("");
  const [users, setUsers] = useState<ParticipantProps[]>([]);
  const [allUsers, setAllUsers] = useState<ParticipantProps[]>([])

  const handleSearchChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    setSearch(event.target.value);
  };

  useEffect(() => {
    if (props.currentChannel){
      const payload = {
        channel_id: props.currentChannel.id,
        user_id: 0,
        password: "",
      };
      props.socket.emit("getAvailableUsersNotInChannel", JSON.stringify(payload));
      props.socket.on("availableUsersNotInChannel", (data: any) => {
        const usersNotInChannel = JSON.parse(data);
        setUsers(usersNotInChannel);
        setAllUsers(usersNotInChannel);
      });
    }
  }, [props.currentChannel, props.socket]);

  useEffect(() => {
    setUsers([]);

    allUsers.filter(val => {
      if (val.username.toLowerCase().includes(search.toLowerCase())) {
        setUsers(users => [...users, val]);
      }
      return allUsers;
    })

  }, [search, allUsers])

  const handleInviteUsers = (user_id: number) => {
    if (props.currentChannel){
      const payload = {
        channel_id: props.currentChannel?.id,
        user_id: user_id,
      };
      props.socket.emit("inviteUser", JSON.stringify(payload));
      props.close();
  }
  }

  return (
    <div>
      <input 
        className={style["input"]} 
        type="text" 
        placeholder="Enter Username"
        onChange={handleSearchChange}
      />
      <div className={style["usersLists"]}>
        {(users?.map((user) => (
          <button 
            key={user.id} 
            className={style["userToInviteInfo"]} 
            onClick={() => handleInviteUsers(user.id) } 
          >
            <p>{user.username}</p>
          </button>
        )))
        }
      </div>
    </div>
  );
};

export default Invite;


