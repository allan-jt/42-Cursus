
import React, { ReactNode } from 'react';
import style from '../../../style.module.css';

interface PopUpType {
  children?: ReactNode;
  isSmallOpen: boolean;
  handleOpen: () => void;
  handleClose: () => void;
}

export default function SmallPopUp(props: PopUpType) {

  return (
    <>
      {props.isSmallOpen && (
        <div onClick={props.handleClose} className={style["settingPopUpOverlay"]} >
          <div onClick={(e) => e.stopPropagation()} className={style["settingPopUpBox"]}>
            {props.children}
          </div>
        </div>
      )}
    </>
  );
} 

