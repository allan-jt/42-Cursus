import React from "react";
import style from "./style.module.css";

interface Props {
  h2: string;
  h1: number;
}

const CareerComponent: React.FC<Props> = ({ h2, h1 }) => {
  return (
    <div className={style["info"]}>
      <h2>{h2}</h2>
      <h1>{h1}</h1>
    </div>
  );
};

export default CareerComponent;
