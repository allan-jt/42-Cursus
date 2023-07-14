import React from "react";
import style from '../style.module.css';

interface Props {
    name: string;
    image: string;
}
  
export function PlayerInfoLeft(props: Props) {
  return (
    <div className={style["player-info-left"]}>
    <div
      className={`${style["profile-picture-small"]}`}
      style={{ backgroundImage: `url(${process.env.REACT_APP_BE_URL}/${props.image})` }}
    />
    <div>{props.name}</div>
  </div>
  );
}
  
export function PlayerInfoRight(props: Props) {
    return (
      <div className={style["player-info-right"]}>
        <div>{props.name}</div>
          <div
          className={`${style["profile-picture-small"]}`}
          style={{ backgroundImage: `url(${process.env.REACT_APP_BE_URL}/${props.image})` }}
        />
      </div>
    );
}