import React from "react";
import Circle from "../../../components/Circle/index";
import style from "../style.module.css";
import GroupLogo from "../../../assets/logo+ch.png";
import FortyTwoLogo from "../../../assets/42AD.png";

function LoginAnchor() {
  const loginUrl = process.env.REACT_APP_BE_URL;
  return (
    <div className={style["login-page"]}>
      <Circle type="upper" />

      <div className={style["middle-section"]}>
        <img className={style["group-logo"]} src={GroupLogo} alt="logo" />
        <Circle type="side" />

        <div>
          <div className={style["anchor-border"]}>
            <a className={style["anchor"]} href={`${loginUrl}/auth`}>
              Login
            </a>
          </div>
        </div>
      </div>

      <div>
        <img className={style["ft-logo"]} src={FortyTwoLogo} alt="42" />
      </div>
      <Circle type="lower" />
    </div>
  );
}

export default LoginAnchor;
