import React from "react";
import style from "../style.module.css";

const InfoAndSurrenderComponent: React.FC<{
  handleSurrender: () => void;
}> = ({ handleSurrender }) => {

  return (
    <div className={style["infoAndSurrender"]}>
      <button className={style["surrender"]} onClick={handleSurrender}>
        SURRENDER
      </button>
    </div>
  );
};

export default InfoAndSurrenderComponent;
