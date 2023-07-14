import { useEffect, useState } from 'react';
import style from '../style.module.css';
import { PlayerInfoLeft, PlayerInfoRight } from './PlayersInfo';
import { MatchesInfo } from './IMatchesInfo';

const HistoryComponent = () => {
    const [matches, setMatches] = useState<MatchesInfo[]>([]);
    const [isLoading, setIsLoading] = useState(true);

    useEffect(() => {
      const fetchData = async () => {
        const response = await fetch(`${process.env.REACT_APP_BE_URL}/users/get-matches`, {
          method: 'GET',
          credentials: 'include',
        });

        if (!response.ok) {
          window.location.href = '/';
        }
        
        const json = await response.json();

        if (Array.isArray(json)) {
          const matchesObjects: MatchesInfo[] = json.map((match: MatchesInfo) => ({
            player1_name: match.player1_name,
            player2_name: match.player2_name,
            player1_image: match.player1_image,
            player2_image: match.player2_image,
            date: match.date,
            duration: match.duration,
            score: match.score,
          }));
          setMatches(matchesObjects);
        }
        
        
        setIsLoading(false);
      };
    fetchData();
    }, []);

    if (isLoading) {
      return <h2> </h2>;
    }

    return (
        <div className={style["friendsList"]}>
          {matches.length === 0 ? (
            <h2 className={style["noFriends"]} >You have no matches yet</h2>) 
          : (
          <ul>
            {Array.isArray(matches) && matches.map((match, index) => (
              <div key={index} className={style["matchesHistory"]} data-date={match.date} data-duration={match.duration}>
                <PlayerInfoLeft name={match.player1_name} image={match.player1_image} />
                <div className={style["scoreHistory"]}>{match.score}</div>
                <PlayerInfoRight name={match.player2_name} image={match.player2_image} />
              </div>
            ))}
          </ul>
          )}
        </div>
    );
} 

export default HistoryComponent;