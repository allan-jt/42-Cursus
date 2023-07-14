import React from "react";
import { BrowserRouter, Routes, Route } from "react-router-dom";
import Login from "./pages/loginPage";
import Profile from "./pages/profilePage/index";
import Error from "./pages/errorPage/index";
import GamePage from "./pages/gamePage/index";
import HomePage from "./pages/homePage/index";
import WatchPage from "./pages/watch/index";
import OtherUser from "./pages/userPage";
import SearchPage from "./pages/searchPage";

import "./index.css";
import ProtectedRouts from "./protectedRouts";
import ChatPage from "./pages/chatPage";
import { SocketProvider } from "./SocketProvider";

function App() {
  return (
    <BrowserRouter>
      <SocketProvider>
        <Routes>
          {/* public route */}
          <Route path="/login" element={<Login />}></Route>,
          {/* private routes */}
          <Route element={<ProtectedRouts />}>
            <Route path="/" element={<HomePage />}></Route>,
            <Route path="/home" element={<HomePage />}></Route>,
            <Route path="/profile" element={<Profile />}></Route>,
            <Route path="/pong" element={<GamePage />}></Route>,
            <Route path="/chat" element={<ChatPage />}></Route>,
            <Route path="/watch" element={<WatchPage />}></Route>,
            <Route path="/user" element={<OtherUser />}></Route>,
            <Route path="/search" element={<SearchPage />}></Route>,
          </Route>
          <Route path="/*" element={<Error />}></Route>,
        </Routes>
      </SocketProvider>
    </BrowserRouter>
  );
}

export default App;
