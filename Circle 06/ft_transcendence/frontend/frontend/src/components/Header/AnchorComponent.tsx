// import { type } from "os";
import React from "react";
import { useNavigate } from "react-router-dom";

interface Props {
  page: string;
  type: string;
  label: string;
  onClick?: () => void;
}

const AnchorComponent= (myProp: Props) => {
  const navigate = useNavigate();

  const goToPageWithNoType = () => {
    navigate(myProp.page);
  }

  const goToPageWithType = () => {
    navigate(myProp.page, { state: { type: myProp.type } });
  }

  const handleOnClick = () => {
    if (myProp.onClick) {
      myProp.onClick();
    } 
    else if (myProp.type === "") {
      goToPageWithNoType();
      navigate(0);
    } 
    else {
      goToPageWithType();
      navigate(0);
    }
  };

  return <button onClick={handleOnClick}> {myProp.label} </ button>;
};

export default AnchorComponent;
