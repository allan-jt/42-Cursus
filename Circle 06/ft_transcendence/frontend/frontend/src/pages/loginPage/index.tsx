import React, { useState, useEffect } from "react";
import LoginAnchor from "./anchorComponent";
import LoginForm from "./formComponent";
import TwoFactorAuth from "./twoFactorAuth/";
import ErrorPage from "../errorPage";

enum UserAuthStatus {
	stage_setUsername,
	stage_2faAuthNew,
	stage_2faAuthOld,
	stage_completed,
  stage_intraLogin
}

function Login() {
  const [loginStatus, setLoginStatus] = useState(0);

  useEffect(() => {
    async function getStatus() {
      const response = await fetch(
        `${process.env.REACT_APP_BE_URL}/auth/getAuthStatus`,
        {
          method: "GET",
          credentials: "include",
        }
      );
      
      if (!response.ok) {
        setLoginStatus(UserAuthStatus.stage_intraLogin);
      } else {
        const body = await response.json();
        setLoginStatus(body.authStatus); 
      }
    }

    getStatus();
  }, []);

  return (
    <div>
      {(() => {
        switch (loginStatus){
          case UserAuthStatus.stage_intraLogin:
            return (<LoginAnchor/>);
          case UserAuthStatus.stage_setUsername:
            return (<LoginForm/>);
          case UserAuthStatus.stage_2faAuthNew:
            return (<TwoFactorAuth isNew={true} />);
          case UserAuthStatus.stage_2faAuthOld:
            return (<TwoFactorAuth isNew={false} />);
          case UserAuthStatus.stage_completed:
            return (<ErrorPage/>);
          default:
            return (<ErrorPage/>);
        }
      }) ()}
    </div>
  );
}

export default Login;
