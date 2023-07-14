import { Outlet } from "react-router-dom";
import React, { useState, useEffect } from "react";
import Login from "./pages/loginPage";

function ProtectedRouts() {
  const [authComplete, setAuthComplete] = useState<boolean>();

  async function isAuth() {
    const response = await fetch(
      `${process.env.REACT_APP_BE_URL}/auth/checkLogged`,
      {
        method: "GET",
        credentials: "include",
      }
    );
    setAuthComplete(response.ok ? true : false);
  }

  useEffect(() => {
    isAuth();
  });

  return authComplete && authComplete === true ? <Outlet /> : <Login />;
}

export default ProtectedRouts;
