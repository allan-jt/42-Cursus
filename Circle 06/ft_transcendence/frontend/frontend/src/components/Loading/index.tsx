import React from "react";
import style from "./style.module.css";

const LoadingComponent: React.FC = () => {
  return (
    <div className={style["loading"]}>
      <div className={style["ball"]}>
        <div className={style["one"]}></div>
        <div className={style["two"]}></div>
        <div className={style["three"]}></div>
        <div className={style["four"]}></div>
      </div>
    </div>
  );
};

export default LoadingComponent;
