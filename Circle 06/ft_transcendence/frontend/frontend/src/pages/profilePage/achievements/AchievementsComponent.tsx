import { useEffect, useState } from 'react';
import { AchievementInfo, achievs } from './AchievementInfo';
import style from '../style.module.css';
import Trophey from '../../../assets/Trophy.png'


const AchievementsComponent = () => {

    const [achievements, setAchievements] = useState<AchievementInfo[]>([]);
    const [isLoading, setIsLoading] = useState(true);

    useEffect(() => {
      const fetchData = async () => {
        const response = await fetch(`${process.env.REACT_APP_BE_URL}/users/get-achievements`, {
          method: 'GET',
          credentials: 'include',
        });

        if (!response.ok) {
          window.location.href = '/';
        }

        const json: string[] = await response.json();
        if (Array.isArray(json)) {
          const achievementObjects = json.map((achievement, index) => {
            const foundAchievement = achievs.find((a) => a.achiev === achievement);
            return {
              id: index,
              achiev: achievement,
              title: foundAchievement ? foundAchievement.title : '',
              description: foundAchievement ? foundAchievement.description : '',
            };
          });
          setAchievements(achievementObjects);
        }
        
        setIsLoading(false);
      };
    fetchData();
    }, []);

    if (isLoading) {
      return <></>;
    }

    return (
        <div className={style["friendsList"]}>
          {achievements.length === 0 ? (
            <h2 className={style["noFriends"]} >You have no achievements yet</h2>) 
            : (
            <ul>
              {Array.isArray(achievements) && achievements.map((achievement) => (
                <div key={achievement.id} className={style["achievement"]}>
                  <img src={Trophey} alt='trophy'/>
                  <div className={style["achievement-info"]}>
                    <h2>{achievement.title}</h2>
                    <br />
                    <h2 className={style["description"]}>{achievement.description}</h2>
                  </div>
                </div>
              ))}
            </ul>
          )}
        </div>
    );
};

export default AchievementsComponent;