import React, { useState, useEffect, useContext } from "react";
import style from "../style.module.css"
import { useNavigate } from "react-router-dom";
import { SocketContext } from "../../../SocketProvider";

interface dataProps {
  username: string;
  image: string;
}

const AddFriend = (user: dataProps) => {
  const socket = useContext(SocketContext);
  const [search, setSearch] = useState("");
  const [friendList, setFriendList] = useState<dataProps[]>([]);
  const [allUsers, setAllUsers] = useState<dataProps[]>([])
  const navigate = useNavigate();

  const handleSearchChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    setSearch(event.target.value);
  };

  const handleAddingFriends = async (event: React.MouseEvent, name: string) => {
     event.preventDefault();
    const response = await fetch(
      `${process.env.REACT_APP_BE_URL}/friends/add`,
      {
        credentials: "include",
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ username: `${name}` }),
      }
    );
    if (!response.ok) {
      window.location.href = '/';
    }
    const data = await response.json();
    if (response.ok && data.valid === "True") {
      navigate(0);
    }

  }

  useEffect(() => {
    socket?.emit("getAllUsers");
    socket?.on("allUsers", (data) =>{
      setAllUsers(data);
      setFriendList(data);
      });

  }, [allUsers]); // eslint-disable-line react-hooks/exhaustive-deps

	useEffect(() => {
		setFriendList(prevFriendList => {
			const updatedFriendList: any[] = [];
	
			allUsers.filter(val => {
				if (val.username.toLowerCase().includes(search.toLowerCase())) {
					updatedFriendList.push(val);
				}
				return prevFriendList;
			});
	
			return updatedFriendList;
		});
	}, [search, allUsers]);

  return (
    <div>
      <form className={style["addingBox"]}>
        <input className={style["input"]} type="text" placeholder="Enter Friend Username" onChange={handleSearchChange}></input>
        <div className={style["friend_info_container"]}>
          {friendList?.map(friend => {
            return (
              (friend.username)?
              <button key={friend.username} className={style["friend_info"]} onClick={(event) => handleAddingFriends(event, friend.username) } >
                <div className={`${style["friend_info_img"]}`}
                style={{ backgroundImage: `url(${process.env.REACT_APP_BE_URL}/${friend.image})`}}/>
                <p>{friend.username}</p>
              </button>
              :
              <></>
            )
          })}
        </div>
      </form>
    </div>
  );
}

export default AddFriend;
