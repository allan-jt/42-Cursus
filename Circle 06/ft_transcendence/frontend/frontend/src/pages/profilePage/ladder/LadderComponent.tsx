import { useEffect, useState } from 'react';
import style from '../style.module.css';
import { useNavigate } from 'react-router-dom';

export interface LadderInfo {
    id: number;
    image: string;
    username: string;
    rating: number;
    position?: number;
    updatedAt: Date;
}

const LadderComponent = () => {
    const [ladders, setLadders] = useState<LadderInfo[]>([]);
    const [isLoading, setIsLoading] = useState(true);
    const attributes = 'id+username+rating+image+updatedAt';
    const navigate = useNavigate();
    const [currentUserId, setCurrentUserId] = useState('');

    useEffect(() => {
        async function fetchData() {
          const response = await fetch(
            `${process.env.REACT_APP_BE_URL}/users/get-all-users?attributes=${attributes}`,
            {
              method: "GET",
              credentials: "include",
            }
          );
          if (!response.ok) {
            window.location.href = '/';
          }
          const json = await response.json();
          if (Array.isArray(json)) {
            setLadders(json);
          }

          setIsLoading(false);
          }
        fetchData();
    }, []);

    useEffect(() => {
      async function fetchData() {
        const response = await fetch(
          `${process.env.REACT_APP_BE_URL}/users/get?search=username+id`,
          {
            method: "GET",
            credentials: "include",
          }
        );
        if (!response.ok) {
          window.location.href = '/';
        }
        const data = await response.json();
        setCurrentUserId(data.id);
      }
      fetchData();
    }, []);

    const sortedLadders = [...ladders].sort((a, b) => {
      if (a.rating === b.rating) {
        const updatedAtA = new Date(a.updatedAt);
        const updatedAtB = new Date(b.updatedAt);
        return updatedAtB.getTime() - updatedAtA.getTime();
      } 
      else {
        return b.rating - a.rating;
      }
    });
    sortedLadders.forEach((ladder, index) => {
        ladder.position = index + 1;
    });

    if (isLoading) {
        return <></>;
    }

    return (
      <div className={style["ladderList"]}>
        <div className={style["ladder-header"]}>
          <div className={style["ladder-rank"]}>Rank</div>
          <div className={style["ladder-username"]}>Username</div>
          <div className={style["ladder-rating"]}>Rating</div>
        </div>

        <div className={style["ladder-table"]}>
          {Array.isArray(sortedLadders) && sortedLadders.map((ladder, index) => (
            <div key={ladder.position} className={`${style["ladder-item"]}          
                  ${
                    String(ladder.id) === String(currentUserId) ? style['current-user'] : ''
                  } ${index < 3 ? style['top-three'] : ''} ${
                    index === 0 ? style['first-place'] : ''
                  } ${index === 1 ? style['second-place'] : ''} ${
                    index === 2 ? style['third-place'] : ''
                  }`}>
              <div className={style["ladder-rank"]}>{ladder.position}</div>
              <div className={style["ladder-username"]}
              onClick={() => navigate('/user', { state: { type: ladder.id } })} 
              >
                <div className={`${style["profile-picture-small"]}`}
                  style={{ backgroundImage: `url(${process.env.REACT_APP_BE_URL}/${ladder.image})` }}
                />

                <div className={style["ladder-username-name"]}>                            
                  {ladder.username}
                </div>
              
              </div>
              <div className={style["ladder-rating"]}>{ladder.rating}</div>
            </div>
          ))}
        </div>
      </div>
    );
}

export default LadderComponent;