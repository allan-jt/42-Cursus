
// import React, { useEffect, useState, ReactNode } from 'react';
import React, { ReactNode } from 'react';
import style from './style.module.css';

interface PopUpType {
  children?: ReactNode;
  isGameInviteOpen: boolean;
  handleOpen: () => void;
  handleClose: () => void;
}

export default function GamePopUp(props: PopUpType) {
  return (
    <>
      {props.isGameInviteOpen && (
        <div className={style["PopUpOverlay"]} >
          <div className={style["border"]}>
            <div onClick={(e) => e.stopPropagation()} className={style["PopUpBox"]}>
              {props.children}
            </div>
          </div>
        </div>
      )}
    </>
  );
} 

