import React, { useState, useEffect, useContext } from "react";
import HeaderComponent from "../../components/Header/index";
import FooterComponent from "../../components/Footer/index";
import LoadingComponent from "../../components/Loading/index";
import CareerComponent from "./CareerComponent";
import StatsComponent from "./StatsComponent";
import FriendComponent from "./friends/FriendComponent";
import AchievementsComponent from "./achievements/AchievementsComponent";
import HistoryComponent from "./history/HistoryComponent";
import LadderComponent from "./ladder/LadderComponent";
import style from "./style.module.css";
import EditImage from "./image/editImage";
import { SocketContext, InviteProps } from "../../SocketProvider";
import GamePopUp from "../../components/gameInvitePopup/gamePopUp";
import useGamePopUp from "../../components/gameInvitePopup/useGamePopUp";
import Invite from "../../components/gameInvitePopup/invite";
import { useLocation } from "react-router-dom";

function Profile() {
  const location = useLocation();
  const hash = location.hash.replace("#", "");
  const [type, setType] = useState(hash === "" ? "history" : hash);
  const socket = useContext(SocketContext);
  const { isGameInviteOpen, handleOpen, handleClose } = useGamePopUp();
  const [inviteData, setInviteData] = useState<InviteProps | null>(null);

  const HandleTypeChange = (newValue: string) => {
    window.location.hash = `#${newValue}`;

    setType(newValue);
  };

  const [userData, setUserData] = useState<null | {
    username: string;
    intraLogin: string;
    rating: number;
    wins: number;
    loses: number;
    image: string;
  }>(null);

  const [imageUrl, setImageUrl] = useState<string>("");
  const attributes = "username+intraLogin+rating+wins+loses+image";

  useEffect(() => {
    if (socket) {
      socket.on("receiveInvite", (data: any) => {
        setInviteData(data);
        handleOpen();
      });
    }
  }, [socket, handleOpen]);

  useEffect(() => {
    if (socket) {
      socket.on("closePopUp", () => {
        handleClose();
      });
    }
  }, [socket, handleClose]);

  useEffect(() => {
    async function fetchData() {
      const response = await fetch(
        `${process.env.REACT_APP_BE_URL}/users/get?search=${attributes}`,
        {
          method: "GET",
          credentials: "include",
        }
      );
      if (!response.ok) {
        window.location.href = "/";
      }
      const json = await response.json();
      setUserData(json);
      setImageUrl(`${process.env.REACT_APP_BE_URL}/${json?.image}`);
    }
    fetchData();
  }, []);

  if (userData === null) {
    return <LoadingComponent />;
  }

  return (
    <div className={style["profile-page"]}>
      <HeaderComponent />

      <div className={style["profile"]}>
        {userData && (
          <div
            className={style["profile-picture"]}
            style={{ backgroundImage: `url(${imageUrl})` }}
          />
        )}

        <div>
          <EditImage imageUrl={imageUrl} setImageUrl={setImageUrl} />
        </div>

        <h1>{userData.username}</h1>
        <h3>{userData.intraLogin}</h3>
      </div>

      <div className={style["career"]}>
        <CareerComponent h2="Rating" h1={userData.rating} />
        <CareerComponent h2="Wins" h1={userData.wins} />
        <CareerComponent h2="Losses" h1={userData.loses} />
      </div>

      <div className={style["stats"]}>
        <StatsComponent type={type} func={HandleTypeChange} />
        <div className={style["box"]}>
          {(() => {
            switch (type) {
              case "friends":
                return (
                  <FriendComponent
                    username={userData.username}
                    image={userData.image}
                  />
                );
              case "achievements":
                return <AchievementsComponent />;
              case "ladder":
                return <LadderComponent />;
              default:
                return <HistoryComponent />;
            }
          })()}
        </div>
      </div>

      <FooterComponent />

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

export default Profile;
