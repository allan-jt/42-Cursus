import React, { useState } from "react";
import style from "../../style.module.css"
import { Socket } from "socket.io-client";

interface myProps {
  socket: Socket;
  toggleOff: () => void;
} 

const CreateChannel = (props: myProps) => {
  const [name, setName] = useState("");
  const [error, setError] = useState("");
  const [nameError, setNameError] = useState("");
  const [password, setPassword] = useState("");
  const [isDirect] = useState(false);
  const [isPrivate, setIsPrivate] = useState(false);
  const [isPublic, setIsPublic] = useState(true);
  const [isPassword, setIsPassword] = useState(false);
  
  const handleChannelChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    setName(event.target.value);
  }

  const handleIsPrivate = async (
    event: React.ChangeEvent<HTMLInputElement>
  ) => {
    if (isPublic === true){
      setIsPublic(false);
      setIsPassword(false);
      setPassword("");
    }
    setIsPrivate(event.target.checked);
    if (event.target.checked === false && isPublic === false)
      setIsPublic(true);

  };

  const handleIsPublic = async (
    event: React.ChangeEvent<HTMLInputElement>
  ) => {
    if (isPrivate === true)
      setIsPrivate(false);

    setIsPublic(event.target.checked);
    if (isPublic === false){
      setIsPassword(false);
      setPassword("");
    }
    if (event.target.checked === false && isPrivate === false)
    setIsPrivate(true);
  };

  const handleIsPassword = async (
    event: React.ChangeEvent<HTMLInputElement>
  ) => {
    setIsPassword(event.target.checked);
    if (isPassword === false){
      setPassword("");
      setError("");
    }
  };

  const handlePasswordChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    setPassword(event.target.value);
  }

  const handleSubmit = (e: any) => {
    e.preventDefault();
    if (name === ""){
      setNameError("please provide a name");
    }
    else if (isPassword === true && password === ""){
      setError("Please provide a password")
    }
    else {
      const payload = {
        name,
        isDirect,
        isPublic,
        password,
      };
      props.socket.emit("createChannel", JSON.stringify(payload));
      props.toggleOff();
    }

  };

  return (
    <div>
      <form className={style["joiningBox"]}>
      <h2>Join a channel or chat with friends </h2>
      <input 
        className={style["input"]} 
        type="text" 
        maxLength={15}
        placeholder="Enter group name" 
        onChange={handleChannelChange}>
      </input>
      <p className={style["Error"]}>{nameError}</p>
      
      <div className={style["channelType"]}>
        <label className={style["privateType"]}>
          <input
            type="checkbox"
            checked={isPrivate}
            onChange={handleIsPrivate}
          />
          <span className={style["check-box"]}></span>
          <div>Private</div>
        </label>
        <label className={style["publicType"]}>
          <input
            type="checkbox"
            checked={isPublic}
            onChange={handleIsPublic}
          />
          <span className={style["check-box"]}></span>
          <div>Public</div>
          </label>
        </div>

        {(isPublic === true)? (
          <div>
            <label className={style["PasswordType"]}>
              <input
                type="checkbox"
                checked={isPassword}
                onChange={handleIsPassword}
              />
              <span className={style["check-box"]}></span>
              <div>Password</div>
            </label>
          </div>
      ):(
        <></>
      )}

      {(isPassword === true && isPublic === true)? (
        <input 
          className={style["input"]} 
          type="text" 
          placeholder="Password" 
          onChange={handlePasswordChange}
        >
        </input>
      ):(
        <></>
      )}

      {(isPassword === true && isPublic === true)? (
        <p className={style["Error"]}>{error}</p>
      ):(
        <></>
      )}

      <button 
        className={style["createButton"]}
        onClick={handleSubmit}
      >
        Create</button>

          
      </form>
    </div>
  );
}

export default CreateChannel;
