import React, { useState } from "react";
import { useNavigate } from "react-router-dom";
import Circle from "../../../components/Circle/index";
import style from "../style.module.css";
import GroupLogo from "../../../assets/logo+ch.png";
import FortyTwoLogo from "../../../assets/42AD.png";

function LoginForm() {
  const [username, setUsername] = useState("");
  const [isChecked, setIsChecked] = useState(false);
  const [display, setDisplay] = useState("");
  const navigate = useNavigate();

  const handleUsernameChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    setUsername(event.target.value);
    setDisplay("");
  };

  const handleIsChecked = async (
    event: React.ChangeEvent<HTMLInputElement>
  ) => {
    setIsChecked(event.target.checked);
  };

  const handleFormSubmit = async (event: React.FormEvent<HTMLFormElement>) => {
    event.preventDefault();

    const response = await fetch(
      `${process.env.REACT_APP_BE_URL}/auth/login-username`,
      {
        credentials: "include",
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({
          username: `${username}`,
          enable2FA: `${isChecked}`,
        }),
      }
    );

    if (!response.ok) {
      setDisplay("Name already taken");
    } else {
      const body = await response.json();
      if (body.usernameStatus !== true) {
        setDisplay("Invalid username!");
        return;
      }
      navigate("/");
      navigate(0);
    }
  };

  return (
    <div className={style["login-page"]}>
      <Circle type="upper" />

      <div className={style["middle-section"]}>
        <img className={style["group-logo"]} src={GroupLogo} alt="logo" />
        <Circle type="side" />
        <form onSubmit={handleFormSubmit}>
          <h1 className={style["header"]}>Enter Display Name</h1>
          <div className={style["form-border"]}>
            <input
              className={style["input"]}
              type="text"
              name="username"
              placeholder="Username"
              onChange={handleUsernameChange}
            />
          </div>
          <p className={style["input-error"]} style={{ display: display ? "block" : "none" }}>
            { display }
          </p>
        </form>
        <label className={style["two-factor-auth"]}>
          <input
            type="checkbox"
            checked={isChecked}
            onChange={handleIsChecked}
          />
          <span className={style["check-box"]}></span>
          <div>Enable Two Factor Authentication</div>
        </label>
      </div>

      <div>
        <img className={style["ft-logo"]} src={FortyTwoLogo} alt="42" />
      </div>
      <Circle type="lower" />
    </div>
  );
}

export default LoginForm;
