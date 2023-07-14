import React, { useState } from "react";
import style from "./style.module.css";

interface StatsProps {
  className: string;
  href: string;
  label: string;
  state: boolean;
  clickFunction: () => void;
}


function Stats({ className, href, label, state, clickFunction }: StatsProps) {
  const name = `${className}${state ? "-clicked" : ""}`;

  return (
    <a className={style[name]} href={href} onClick={clickFunction}>
      {label}
      <div className={style["underline"]}></div>
    </a>
  );
}

interface typeProp {
  type: string;
  func: (newValue: string) => void;
}

function StatsComponent(myProp: typeProp) {
  type stats = {
    history: boolean;
    friends: boolean;
    achievements: boolean;
    ladder: boolean;
  };

  const [statsState, setStatsState] = useState<stats>({
    history: (myProp.type === "history" || myProp.type === "")? true: false,
    friends: (myProp.type === "friends")? true: false,
    achievements: (myProp.type === "achievements")? true: false,
    ladder: (myProp.type === "ladder")? true: false,
  });

  const handleClick = (statIndex: keyof stats) => {
    const updatedStats = {
      history: false,
      friends: false,
      achievements: false,
      ladder: false,
    };
  
    updatedStats[statIndex] = true;
    myProp.func(statIndex);
    setStatsState(updatedStats);
  };

  return (
    <div className={style["stat-anchors"]}>
      <Stats
        className="history"
        href="#history"
        label="Match History"
        state={statsState.history}
        clickFunction={() => handleClick("history")}
      />
      <Stats
        className="friends"
        href="#friends"
        label="Friends"
        state={statsState.friends}
        clickFunction={() => handleClick("friends")}
      />
      <Stats
        className="achievements"
        href="#achievements"
        label="Achievements"
        state={statsState.achievements}
        clickFunction={() => handleClick("achievements")}
      />
      <Stats
        className="ladder"
        href="#ladder"
        label="Ladder"
        state={statsState.ladder}
        clickFunction={() => handleClick("ladder")}
      />
    </div>
  );
}

export default StatsComponent;
