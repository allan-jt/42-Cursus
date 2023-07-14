import React, { useState, useEffect, useContext } from "react";
import HeaderComponent from "../../components/Header/index";
import style from "./style.module.css";
import { useNavigate } from "react-router-dom";
import { SocketContext, InviteProps } from "../../SocketProvider";
import GamePopUp from "../../components/gameInvitePopup/gamePopUp";
import useGamePopUp from "../../components/gameInvitePopup/useGamePopUp";
import Invite from "../../components/gameInvitePopup/invite";

export interface userInfo {
  id: number;
  image: string;
  username: string;
}

function SearchPage() {
  const [search, setSearch] = useState("");
  const [allUsers, setAllUsers] = useState<userInfo[]>([]);
  const [filteredUsers, setFilteredUsers] = useState<userInfo[]>([]);
  const navigate = useNavigate();
  // const [currentUserId, setCurrentUserId] = useState('');
  const attributes = "id+username+image";
  const socket = useContext(SocketContext);
  const { isGameInviteOpen, handleOpen, handleClose } = useGamePopUp();
  const [inviteData, setInviteData] = useState<InviteProps>();

  const handleSearchChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    setSearch(event.target.value);
  };

    useEffect(() => {
        async function fetchData() {
          const response = await fetch(
            `${process.env.REACT_APP_BE_URL}/users/get-all-other-users?attributes=${attributes}`,
            {
              method: "GET",
              credentials: "include",
            }
          );
          if (!response.ok) {
            window.location.href = '/';
          }
          const json = await response.json();
          
          const sortedJson = json.sort((a: any, b: any) => a.username.localeCompare(b.username));
          setAllUsers(sortedJson);
          setFilteredUsers(sortedJson);

        }
    fetchData();
  }, []);

  useEffect(() => {
    if (search === "") {
      setFilteredUsers(allUsers);
    } else {
      const filteredResults = allUsers.filter((user) =>
        user.username.toLowerCase().includes(search.toLowerCase())
      );
      setFilteredUsers(filteredResults);
    }
  }, [search, allUsers]);

  useEffect(() => {
    if (socket) {
      socket.on("receiveInvite", (data: InviteProps) => {
        setInviteData(data);
        handleOpen();
      });
    }
  }, [socket, inviteData, handleOpen]);

  useEffect(() => {
    if (socket) {
      socket.on("closePopUp", () => {
        handleClose();
      });
    }
  }, [socket, handleClose]);

  return (
    <div className={style["search-page"]}>
      <HeaderComponent />
      <div className={style["search-component"]}>
        <input
          className={style["input"]}
          type="text"
          placeholder="Enter Username"
          onChange={handleSearchChange}
        ></input>
        <div className={style["user_info_container"]}>
          {Array.isArray(filteredUsers) &&
            filteredUsers?.map((user) => {
              return (
                (user.id)?
                <button
                  key={user.id}
                  className={style["user_info"]}
                  onClick={(event) =>
                    navigate("/user", { state: { type: user.id } })
                  }
                >
                  <img src={`${process.env.REACT_APP_BE_URL}/${user.image}`} alt="profile"/>
                  <p>{user.username}</p>
                </button>
                :
                <></>
              );
            })}
        </div>
      </div>
      {/* <FooterComponent /> */}

      <GamePopUp
        isGameInviteOpen={isGameInviteOpen}
        handleOpen={handleOpen}
        handleClose={handleClose}
      >
        {socket && inviteData ? (
          <Invite
            socket={socket}
            inviterName={inviteData.inviterName}
            inviteeName={inviteData.inviteeName}
            close={handleClose}
          />
        ) : (
          <></>
        )}
      </GamePopUp>
    </div>
  );
}

export default SearchPage;
