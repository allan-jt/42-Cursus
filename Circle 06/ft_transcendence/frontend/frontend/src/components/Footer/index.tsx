import React from "react";
import style from "./style.module.css";
import FortyTwoLogo from "../../assets/42AD.png";

const FooterComponent: React.FC = () => {
  return (
    <div className={style["footer"]}>
      <div className={style["footer_content"]}>
        <p className={style["footer_title"]}></p>
        <p className={style["footer_text"]}>
          © 2023. All rights reserved. Made with ❤️ by{" Alia, Allan, Ameer, Gerard, and Anastasia "}
        </p>
        <img className={style["ft-logo"]} src={FortyTwoLogo} alt="42" />
      </div>
    </div>
  );
};

export default FooterComponent;
