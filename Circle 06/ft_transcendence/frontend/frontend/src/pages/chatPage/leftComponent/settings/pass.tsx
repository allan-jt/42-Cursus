import React, { useState } from "react";
import style from "../../style.module.css";
import { Socket } from "socket.io-client";
import arrow from "../../../../assets/arrow.png";

interface Channel {
  name: string;
  isDirect: boolean;
  isPublic: boolean;
  id: number;
  createdAt: Date;
}

interface myProps {
  socket: Socket;
  currentChannel: Channel | undefined;
	close: () => void;
}

const Pass = (props: myProps) => {
  const [isPassChangeOn, setIsPassChangeOn] = useState(false);
  const [Pass, setPass] = useState("");

  const HandlePassChangeOn = () => {
    setIsPassChangeOn((isPassChangeOn)? false: true);
    const arrow = document.getElementById("pass");

    if (arrow && isPassChangeOn === false){
      arrow.style.transform = 'rotate(0deg)';
    }
    else if (arrow && isPassChangeOn === true)
      arrow.style.transform = 'rotate(-90deg)';
  }

  const handlePassChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    setPass(event.target.value);
  }

  const SavePass = (e: any) => {
		if (props.currentChannel){
				props.socket.emit("updateChannelPassword",
				JSON.stringify(
				{
					channel_id: props.currentChannel.id,
					password: Pass,
				}
			));
		}
		props.close();
  }

  return (
    <div className={style["settingsType"]}>
        <h3 onClick={HandlePassChangeOn}>
          <img id="pass" src={arrow} className={style["arrow"]} alt="arrow"></img>
          Channel Password
        </h3> 
        {(isPassChangeOn)? (
          <div className={style["passChangeContainer"]}>
            <input
              className={style["input"]}
              type="text"
              placeholder="Enter new password"
              onChange={handlePassChange}
            >
            </input>
            <button onClick={SavePass}>Update</button>
          </div>
          ):(
            <></>
          )
        }
      </div>
  );
};

export default Pass;
