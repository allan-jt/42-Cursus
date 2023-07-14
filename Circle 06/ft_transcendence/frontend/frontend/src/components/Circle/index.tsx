import React from "react";
import style from "./style.module.css";

interface Props {
  type: string;
}

const CircleComponent: React.FC<Props> = ({ type }) => {
  return type.includes("side") ? (
    <div className={style["side-circle"]}>
      <div className={style["left"]}></div>
      <div className={style["right"]}></div>
    </div>
  ) : (
    <div className={style[type + "-section"]}>
      <div className={style[type + "-circle"]}>
        <div className={style["green"]}></div>
        <div className={style["blue"]}></div>
        <div className={style["pink"]}></div>
      </div>
    </div>
  );
};

export default CircleComponent;
