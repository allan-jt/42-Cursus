
import React, { ReactNode } from 'react';
import style from '../../../style.module.css';

interface PopUpType {
  children?: ReactNode;
  isInviteOpen: boolean;
  handleInviteOpen: () => void;
  handleInviteClose: () => void;
}

export default function PopUp(props: PopUpType) {

  return (
    <>
      {props.isInviteOpen && (
        <div 
          onClick={props.handleInviteClose} 
          className={style["InviteOverlay"]} 
        >
          <div 
            onClick={(e) => e.stopPropagation()} 
            className={style["InviteBox"]}
          >
            {props.children}
          </div>
        </div>
      )}
    </>
  );
} 

