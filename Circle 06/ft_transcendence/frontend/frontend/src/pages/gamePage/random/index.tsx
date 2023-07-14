import React, { useEffect } from "react";
import style from "../style.module.css";
import HeaderComponent from "../../../components/Header";
import FooterComponent from "../../../components/Footer/index";
import LoadingComponent from "../../../components/Loading";

export function Random() {
  useEffect(() => {
    async function getStatus() {
      const response = await fetch(
        `${process.env.REACT_APP_BE_URL}/auth/getAuthStatus`,
        {
          method: "GET",
          credentials: "include",
        }
      );

      if (!response.ok) {
        window.location.href = "/";
      }
    }

    getStatus();
  }, []);

  return (
    <div className={style["body"]}>
      <HeaderComponent />
      <div className={style["middleBox"]}>
        <LoadingComponent />
      </div>
      <FooterComponent />
    </div>
  );
}

export default Random;
