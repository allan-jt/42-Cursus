import React from "react";
import Anchor from "./AnchorComponent";
import style from "./style.module.css";

interface Link {
  id: number;
  page: string;
  type: string;
  label: string;
  onClick?: () => void;
}

interface Props {
  links: Link[];
}

const DropdownComponent: React.FC<Props> = ({ links }) => {
  
  return (
    <div className={style["dropdown-content"]}>
      {links.map((link) => (
        <Anchor key={link.id} page={link.page} type={link.type} label={link.label} onClick={link.onClick}/>
      ))}
    </div>
  );
};

export default DropdownComponent;
