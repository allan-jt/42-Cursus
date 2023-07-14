import React from "react";
import { useState, useEffect } from "react";
import { useLocation, useNavigate } from "react-router-dom";
import Circle from "../../../components/Circle/index";
import style from "./style.module.css";
import GroupLogo from "../../../assets/logo+ch.png";
import FortyTwoLogo from "../../../assets/42AD.png";
import AuthLogo from "../../../assets/Google_Authenticator_for_Android_icon.svg.png";

interface props {
  isNew: boolean;
}

function NewTwoFactorAuth(state: props) {
  const [code, setCode] = useState("");
  const [QrCode_Url, setQrCodeUrl] = useState("");
  const [errorMsg, setErrorMsg] = useState("");
  const navigate = useNavigate();
  const location = useLocation();

  const handleCodeChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    setCode(event.target.value);
  };

  const handleCodeSubmit: React.MouseEventHandler<HTMLButtonElement> = async (
    event
  ) => {
    event.preventDefault();
    const response = await fetch(
      `${process.env.REACT_APP_BE_URL}/auth/verify`,
      {
        credentials: "include",
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ code: `${code}` }),
      }
    );
    const data = await response.json();
    if (response.ok && data.valid === "True") {
      if (location.pathname === '/login') {
        navigate('/');
      } else {
        navigate(0);
      }
    } else {
      setErrorMsg("Wrong code");
    }
  };

  const fetchQrCodeUrl = async () => {
    try {
      const response = await fetch(
        `${process.env.REACT_APP_BE_URL}/auth/qrcode`,
        {
          method: "GET",
          credentials: "include",
        }
      );
      setQrCodeUrl(await response.text());
    } catch (error) {
      console.error(`Unable to fetch QR Code`);
    }
  };

  useEffect(() => {
    if (state.isNew === true) fetchQrCodeUrl();
  }, [state]);

  return (
    <div className={style["authPage"]}>
      <Circle type="upper" />

      <div className={style["middle"]}>
        <img className={style["logo"]} src={GroupLogo} alt="logo" />
        <h3 className={style["text"]}>Two Factor Auth</h3>

        {state.isNew ? (
          <div className={style["qr_code"]}>
            <div className={style["downloadSection"]}>
              <p className={style["steps"]}>
                1. Download Google Authenticator app.
              </p>
              <img
                className={style["QR"]}
                src={AuthLogo}
                alt="Google-Authenticator-Logo"
              />
            </div>
            <div className={style["middleLine"]}></div>
            <div className={style["qrSection"]}>
              <p className={style["steps"]}>2. Setup via QR</p>
              <img className={style["QR"]} src={QrCode_Url} alt="QR Code" />
            </div>
            <div className={style["middleLine"]}></div>
            <div className={style["codeSection"]}>
              <p className={style["steps"]}>3. Enter code</p>
              <input
                className={style["code"]}
                onChange={handleCodeChange}
              ></input>
              <p className={style["error"]}>{errorMsg}</p>
              <button className={style["validate"]} onClick={handleCodeSubmit}>
                Validate
              </button>
            </div>
          </div>
        ) : (
          <div className={style["codeSectionSolo"]}>
            <div className={style["codeSectionSolo"]}>
              <p className={style["steps"]}>Enter code</p>
              <input
                className={style["codeSolo"]}
                onChange={handleCodeChange}
              ></input>
              <p className={style["error"]}>{errorMsg}</p>
            </div>

            <button
              className={style["validateSolo"]}
              onClick={handleCodeSubmit}
            >
              Validate
            </button>
          </div>
        )}
      </div>

      <div>
        <img className={style["ft-logo"]} src={FortyTwoLogo} alt="42" />
      </div>
    </div>
  );
}

export default NewTwoFactorAuth;
