import React from "react";
import Trophey from '../../assets/Trophy.png';
import style from "./style.module.css";
import { AchievementInfo } from "../profilePage/achievements/AchievementInfo";

interface AchievementProps {
    achievement: AchievementInfo;
}
  
const Achievement: React.FC<AchievementProps> = ({ achievement }) => {
    return (
      <div className={style.achievement}>
        <img src={Trophey} alt="trophy" />
        <div className={style["achievement-info"]}>
          <h2>{achievement.title}</h2>
          <br />
          <h2 className={style.description}>{achievement.description}</h2>
        </div>
      </div>
    );
};
  
interface AchievementsProps {
    achievements: AchievementInfo[];
}
  
const Achievements: React.FC<AchievementsProps> = ({ achievements }) => {
    if (achievements.length === 0) {
        return <h2 className={style.noItem}>You have no achievements yet</h2>;
    }
  
    return (
        <ul>
            {achievements.map((achievement) => (
                <Achievement key={achievement.id} achievement={achievement} />
            ))}
        </ul>
    );
};
  
export default Achievements;