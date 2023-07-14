import React, { ReactNode } from 'react';
import style from '../style.module.css';

interface ModalType {
  children?: ReactNode;
  isOpen: boolean;
  toggle: () => void;
}

export default function Popup(props: ModalType) {

  return (
    <>
      {props.isOpen && (
        <div className={style["addFriendBox-overlay"]} >
          <button onClick={props.toggle}>X</button>
          <div onClick={(e) => e.stopPropagation()} className={style["addFriendBox"]}>
            {props.children}
          </div>
        </div>
      )}
    </>
  );
} 

