
import React, { useEffect, ReactNode } from 'react';
import style from '../style.module.css';

interface PopUpType {
  children?: ReactNode;
  isOpen: boolean;
  toggle: () => void;
  errorMessage?: string;
  resetErrorMessage: () => void;
}

export default function PopUp(props: PopUpType) {
  
  useEffect(() => {
    if (!props.isOpen) {
      props.resetErrorMessage();
    }
  }, [props, props.isOpen, props.resetErrorMessage]);

  return (
    <>
      {props.isOpen && (
        <div onClick={props.toggle} className={style["editBoxOverlay"]} >
          <div onClick={(e) => e.stopPropagation()} className={style["ChangePhotoBox"]}>
            {props.children}
          </div>
        </div>
      )}
    </>
  );
} 

