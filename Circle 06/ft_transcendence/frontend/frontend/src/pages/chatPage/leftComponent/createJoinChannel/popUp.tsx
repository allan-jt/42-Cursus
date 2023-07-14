
import React, { ReactNode } from 'react';
import style from '../../style.module.css';

interface PopUpType {
  children?: ReactNode;
  isOpen: boolean;
  toggleOn: () => void;
  toggleOff: () => void;
}

export default function PopUp(props: PopUpType) {

  return (
    <>
      {props.isOpen && (
        <div onClick={props.toggleOff} className={style["addJoinOverlay"]} >
          <div onClick={(e) => e.stopPropagation()} className={style["addJoinBox"]}>
            {props.children}
          </div>
        </div>
      )}
    </>
  );
}

