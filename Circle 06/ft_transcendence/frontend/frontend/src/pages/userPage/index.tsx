import React, { useState, useEffect, useContext } from "react";
import style from "./style.module.css";
import HeaderComponent from "../../components/Header/index";
import FooterComponent from "../../components/Footer/index";
import ErrorPage from "../errorPage";
import LoadingComponent from "../../components/Loading";
import CareerComponent from "../profilePage/CareerComponent";
import { achievs } from "../profilePage/achievements/AchievementInfo";
import Achievements from "./AchievementsUsers";
import { useLocation, useNavigate } from "react-router-dom";
import { SocketContext, InviteProps } from "../../SocketProvider";
import GamePopUp from "../../components/gameInvitePopup/gamePopUp";
import useGamePopUp from "../../components/gameInvitePopup/useGamePopUp";
import Invite from "../../components/gameInvitePopup/invite";

function OtherUser() {
  const socket = useContext(SocketContext);
  const { isGameInviteOpen, handleOpen, handleClose } = useGamePopUp();
  const [inviteData, setInviteData] = useState<InviteProps>();

  const [userData, setUserData] = useState<null | {
    username: string;
    intraLogin: string;
    rating: number;
    wins: number;
    loses: number;
    image: string;
    available: string;
    gameStatus: string;
    achievements: string[];
  }>(null);

  const [isFriend, setIsFriend] = useState(false);
  const [isBlocked, setIsBlocked] = useState<boolean>(false);
  const location = useLocation();
  const type = location.state?.type;
  const [userId] = useState(type ?? null);
  const navigate = useNavigate();
  const [currentUserId, setCurrentUserId] = useState("");
  const attributes =
    "username+intraLogin+rating+wins+loses+image+achievements+available";
  const [amIBlocked, setAmIBlocked] = useState<boolean>(false);
  const [refreshCount, setRefreshCount] = useState(0);
  const [achievementObjects, setAchievementObjects] = useState<any>();

  useEffect(() => {
    if (userData && userData.achievements) {
      const updatedAchievementObjects = userData.achievements.map(
        (achievement, index) => {
          const foundAchievement = achievs.find(
            (a) => a.achiev === achievement
          );
          return {
            id: index,
            achiev: achievement,
            title: foundAchievement ? foundAchievement.title : "",
            description: foundAchievement ? foundAchievement.description : "",
          };
        }
      );

      setAchievementObjects(updatedAchievementObjects);
    }
  }, [userData]);

  useEffect(() => {
    const interval = setInterval(() => {
      setRefreshCount((prevCount) => prevCount + 1);
    }, 5000);
    return () => clearInterval(interval);
  }, []);

  useEffect(() => {
    async function fetchUserData() {
      const response = await fetch(
        `${process.env.REACT_APP_BE_URL}/users/get?search=username+id`,
        {
          method: "GET",
          credentials: "include",
        }
      );
      if (!response.ok) {
        window.location.href = "/";
      }
      const data = await response.json();
      setCurrentUserId(data.id);
    }
    fetchUserData();
  }, [currentUserId]);

  useEffect(() => {
    if (currentUserId === userId) {
      navigate("/profile");
    }
  }, [currentUserId, userId, navigate]);

  useEffect(() => {
    async function getIsBlocked() {
      const responseBlock = await fetch(
        `${process.env.REACT_APP_BE_URL}/users/get-blocked-users`,
        {
          method: "GET",
          credentials: "include",
          headers: {
            "Content-Type": "application/json",
          },
        }
      );
      const blockedUsers = await responseBlock.json();

      for (let i = 0; i < blockedUsers.length; i++) {
        if (
          userId &&
          parseInt(blockedUsers[i].blockedUser.id) === parseInt(userId)
        ) {
          setIsBlocked(true);
          break;
        } else setIsBlocked(false);
      }
    }
    getIsBlocked();
  }, [isBlocked, userId]);

  useEffect(() => {
    async function getAmIBlocked() {
      const response = fetch(
        `${process.env.REACT_APP_BE_URL}/users/am-i-blocked?id=${userId}`,
        {
          method: "GET",
          credentials: "include",
          headers: {
            "Content-Type": "application/json",
          },
        }
      );
      const responseParsed = (await response).json();
      setAmIBlocked(await responseParsed);
    }
    getAmIBlocked();
  }, [refreshCount, amIBlocked, userId]);

  useEffect(() => {
    async function fetchData() {
      const response = await fetch(
        `${process.env.REACT_APP_BE_URL}/users/other/${userId}?attributes=${attributes}`,
        {
          method: "GET",
          credentials: "include",
        }
      );
      const json = await response.json();
      setUserData(json);
    }
    if (userId !== null) fetchData();
  }, [userId]);

  useEffect(() => {
    async function fetchData() {
      const response = await fetch(
        `${process.env.REACT_APP_BE_URL}/friends/check-friendship/${userId}`,
        {
          method: "GET",
          credentials: "include",
        }
      );

      if (response.ok) {
        const json = await response.json();
        setIsFriend(json.isFriend);
      }
    }
    fetchData();
  }, [refreshCount, userId]);

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

  const toggleFriendship = async () => {
    if (!userData) {
      return;
    }

    if (isFriend) {
      const response = await fetch(
        `${process.env.REACT_APP_BE_URL}/friends/delete`,
        {
          method: "DELETE",
          credentials: "include",
          headers: {
            "Content-Type": "application/json",
          },
          body: JSON.stringify({ id: userId }),
        }
      );
      if (response.ok) {
        setIsFriend(false);
      }
    } else {
      const response = await fetch(
        `${process.env.REACT_APP_BE_URL}/friends/add`,
        {
          method: "POST",
          credentials: "include",
          headers: {
            "Content-Type": "application/json",
          },
          body: JSON.stringify({ username: userData.username }),
        }
      );
      if (response.ok) {
        setIsFriend(true);
      }
    }
  };

  const toggleBlocking = async () => {
    if (isBlocked === false) {
      const response = await fetch(
        `${process.env.REACT_APP_BE_URL}/users/block-user`,
        {
          method: "POST",
          credentials: "include",
          headers: {
            "Content-Type": "application/json",
          },
          body: JSON.stringify({ id: userId }),
        }
      );

      if (response.ok) {
        setIsBlocked(true);
      }
    } else {
      const response = await fetch(
        `${process.env.REACT_APP_BE_URL}/users/unblock-user`,
        {
          method: "POST",
          credentials: "include",
          headers: {
            "Content-Type": "application/json",
          },
          body: JSON.stringify({ id: userId }),
        }
      );

      if (response.ok) {
        setIsBlocked(false);
      }
    }
  };

  if (userData === null && userId === null) {
    return <ErrorPage />;
  } else if (userData === null) return <LoadingComponent />;

  return userId === null ? (
    <ErrorPage />
  ) : (
    <div className={style["users-page"]}>
      <HeaderComponent />
      <div className={style["profile"]}>
        <div className={style["profile-picture-container"]}>
          <div
            className={style["profile-picture"]}
            style={{
              backgroundImage: `url(${process.env.REACT_APP_BE_URL}/${userData.image})`,
            }}
          />
          {userData.available === "OFFLINE" ? (
            <div
              className={style["offline"]}
              data-status={userData.available}
            ></div>
          ) : userData.available === "ONLINE" ? (
            <div
              className={style["online"]}
              data-status={userData.available}
            ></div>
          ) : (
            <div
              className={style["inGame"]}
              data-status={userData.available}
            ></div>
          )}
        </div>

        <h1>{userData.username}</h1>

        <div className={style["button-group"]}>
          {!amIBlocked && !isBlocked ? (
            <button
              className={style["friend-button"]}
              onClick={toggleFriendship}
            >
              {isFriend ? "Remove from Friends" : "Add to Friends"}
            </button>
          ) : (
            <></>
          )}
          {!isFriend ? (
            <button className={style["block-button"]} onClick={toggleBlocking}>
              {isBlocked ? "Unblock User" : "Block User"}
            </button>
          ) : (
            <></>
          )}
        </div>
        <h3>{userData.intraLogin}</h3>
      </div>

      <div className={style["career"]}>
        <CareerComponent h2="Rank" h1={userData.rating} />
        <CareerComponent h2="Wins" h1={userData.wins} />
        <CareerComponent h2="Losses" h1={userData.loses} />
      </div>

      <div className={style["stats"]}>
        <h4>Achievements</h4>
        <div className={style["box"]}>
          <div className={style["itemList"]}>
            {achievementObjects ? (
              <Achievements achievements={achievementObjects} />
            ) : (
              <></>
            )}
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
    </div>
  );
}

export default OtherUser;
