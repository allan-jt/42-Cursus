import React, { useContext } from "react";
import { useState, useEffect } from "react";
import style from "../style.module.css";
import { InviteStatus, SocketContext } from "../../../SocketProvider";

export interface friendInfo {
  id: number;
  username: string;
  image: string;
  rating: number;
  available: string;
  gameStatus: string;
}

interface ButtonProps {
  selectFriend: () => void;
}

function Friends({ selectFriend }: ButtonProps) {
  const socket = useContext(SocketContext);
  const [friends, setFriends] = useState<friendInfo[]>();
  const [isLoading, setIsLoading] = useState(true);

  useEffect(() => {

    function getMyFriends(){
      socket?.emit("getFriendsStatus");
      socket?.on("allFriends", (data) =>{
        if (Array.isArray(data)){
          const onlineFriends = data?.filter(
            (friend: friendInfo) =>
              friend.available === "ONLINE" && friend.gameStatus === "AVAILABLE"
          );
          setFriends(onlineFriends);
          setIsLoading(false);
        }
      });
    }

    const interval = setInterval(getMyFriends, 1000);
    return () => {
      clearInterval(interval);
    };
  }, [friends, isLoading, socket]); 

  if (isLoading) {
    return <h2 className={style["noFriendsAvailable"]}>Loading...</h2>;
  }

  async function fetchMyUserID() {
    const response = await fetch(
      `${process.env.REACT_APP_BE_URL}/users/get?search=username`,
      {
        method: "GET",
        credentials: "include",
      }
    );
    const ID = await response.json();
    return ID;
  }

  const inviteUser = async (friendUsername: string) => {
    const myUsername = await fetchMyUserID();
    const data = {
      inviteeName: friendUsername,
      inviterName: myUsername.username,
      status: InviteStatus.invite_sent,
      accept: false,
    };
    socket?.emit("sendInvite", { invite: data });
  };

  return (
    <div className={style["fiend_list"]}>
      {friends === undefined || friends.length === 0 ? (
        <h2 className={style["noFriendsAvailable"]}>
          No friends available to play right now
        </h2>
      ) : (
        friends.map((friend) => (
          <span key={friend.id} onClick={selectFriend}>
            <div
              className={style["friend_info"]}
              onClick={() => inviteUser(friend.username)}
            >
              <img
                className={style["friedImg"]}
                src={`${process.env.REACT_APP_BE_URL}/${friend.image}`}
                alt="friend profile pic"
              />
              <h3>{friend.username}</h3>
            </div>
          </span>
        ))
      )}
    </div>
  );
};

export default Friends;
