import React from "react";
import Circle from "../../components/Circle/index";
import style from "./style.module.css";
import Error404 from "../../assets/404.png";
import Confused from "../../assets/buttercup_confused.png";
import FortyTwoLogo from "../../assets/42AD.png";

type ErrorPageProps = {
  default?: boolean;
};

function ErrorPage(props: ErrorPageProps) {
  return (
    <div className={style["ErrorPage"]}>
      <Circle type="upper" />

      <div className={style["Error404"]}>
        <img className={style["status-code"]} src={Error404} alt="Error 1" />
        <h1>Page Not Found</h1>
        <img className={style["buttercup"]} src={Confused} alt="Error 2" />
      </div>

      <Circle type="lower" />
      <div>
        <img className={style["ft-logo"]} src={FortyTwoLogo} alt="42" />
      </div>
    </div>
  );
}

export default ErrorPage;
