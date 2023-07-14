import React, { useEffect, useState, useContext } from 'react';
import style from '../style.module.css';
import MiddleBox from './middleBox';
import UseMiddleBox from './useMiddleBox'
import AddFriend from './addFriend';
import ChatIcon from '../../../assets/chat.png'
import { useNavigate } from 'react-router-dom';
import { SocketContext } from "../../../SocketProvider";

export interface friendInfo {
  id: number,
  username: string,
  image: string,
  rating: number,
  available: string,
  gameStatus: string,
}

interface userData {
  username: string;
  image: string;
}

const FriendComponent = (user: userData) => {
  const socket = useContext(SocketContext);
  const navigate = useNavigate();
  const [friends, setFriends] = useState<friendInfo[]>();
  const [isLoading, setIsLoading] = useState(true);

  useEffect(() => {
    socket?.emit("getFriendsStatus");
    socket?.on("allFriends", (data) =>{
      setFriends(data);
      setIsLoading(false);
      });
    }, [friends]); // eslint-disable-line react-hooks/exhaustive-deps

    const { isOpen, toggle } = UseMiddleBox();

    if (isLoading) {
      return <></>;
  }


  return (
    <div className={style["friendsList"]}>
      {(!friends || !friends[0])? (
        <h2 className={style["noFriends"]} >You have no friends</h2>)
      : (
        friends.map((friend) => (
          <div
            key={friend.id}
            className={style["friend"]}
          >
            <div  onClick={() => navigate('/user', { state: { type: friend.id } })}>
            <img className={style["friend_img"]} src={`${process.env.REACT_APP_BE_URL}/${friend.image}`} alt='friendImage' /> 

            {(friend.gameStatus === 'ONGAME')? (<div className={style["inGame"]} data-status={friend.gameStatus}></div>): 
            (friend.available === 'ONLINE')?(<div className={style["online"]} data-status={friend.available}></div>):
            (<div className={style["offline"]} data-status={friend.available}></div>)}

            <h3>{friend.username}</h3>
          </div>
          <button key={friend.id} className={style["chatButton"]}  onClick={() => navigate(`/chat`, {state: { type: friend.id }})} >
            <img src={ChatIcon} alt='chatIcon' />

          </button>
        </div>
      )))}

      <button onClick={toggle}> add friend </button>

      <MiddleBox isOpen={isOpen} toggle={toggle}>
        <AddFriend username={user.username} image={user.image}/>
      </MiddleBox>

    </div>
  );
};
  
export default FriendComponent;
