import React, { useContext } from "react";
import { useNavigate } from "react-router-dom";
import DropdownContent from "./DropdownComponent";
import style from "./style.module.css";
import GroupLogo from "../../assets/Logo.png";
import { useEffect, useState } from "react";
import searchIcon from "../../assets/search.png";
import { SocketContext } from "../../SocketProvider";

const HeaderComponent: React.FC = () => {
  const socket = useContext(SocketContext);
  const navigate = useNavigate();
  
  const goToHomePage = () => {
    navigate(`/home`);
  };

  const goToProfilePage = () => {
    navigate(`/profile`);
  };
  
  
  const handleLogoutClick = async () => {
    async function logOut(){
      try {
        const response = await fetch(
            `${process.env.REACT_APP_BE_URL}/auth/logout`, 
            {
                method: "GET",
                credentials: "include",
            }
        );
        if (!response.ok)
            navigate(0);
        socket?.disconnect();
        navigate('/login');
      } 
      catch (error) {
          console.error(`Logout error`);
      }
    }

    await logOut();

  };

  const [imageUrl, setImageUrl] = useState<string>('');

  useEffect(() => {
    async function fetchData() {
      const response = await fetch(
        `${process.env.REACT_APP_BE_URL}/users/get?search=image`,
        {
          method: "GET",
          credentials: "include",
        }
      );
      const json = await response.json();
      setImageUrl(`${process.env.REACT_APP_BE_URL}/${json?.image}`);
    }
    fetchData();
  }, []);

  return (
    <div className={style["header"]}>
      <img
        className={style["group-logo"]}
        src={GroupLogo}
        alt="logo"
        onClick={goToHomePage}
      />

      <div className={style["navigation-bar"]}>
        <div className={style["dropdown"]}>
          <button className={style["button"]} onClick={goToHomePage}>Play</button>
          <DropdownContent
            links={[
              { id: 1, page: "/pong", type: "friend", label: "Challenge A Friend" },
              { id: 0, page: "/pong", type: "random", label: "Matchmake" },
              { id: 2, page: "/pong", type: "bot", label: "Practice" },
            ]}
          />
        </div>

        <a className={style["navigate"]} href="/watch">
          Watch
        </a>

        <a className={style["navigate"]} href="/chat">
          Chat
        </a>

        <a className={style["navigate"]} style={{display: "flex", justifyContent: "center", alignItems: "center"}} href="/search">
          <img className={style["search_icon"]} src={searchIcon} alt="search" />
          <p>Search</p>
        </a>

        <div className={style["dropdown"]}>
          <img className={style["header-photo"]} src={imageUrl} alt="user" onClick={goToProfilePage} />
          <DropdownContent
            links={[
              { id: 0, page: "/profile", type:"", label: "Profile" },
              { id: 1, page: "/search", type: "", label: "Search" },
              { id: 2, page: "/", type: "", label: "Log Out", onClick: handleLogoutClick },
            ]}
          />
        </div>
      </div>
    </div>
  );
};

export default HeaderComponent;
