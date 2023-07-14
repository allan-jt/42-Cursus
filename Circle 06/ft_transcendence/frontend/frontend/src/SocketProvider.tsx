import React, { createContext, useEffect, useState } from "react";
import { io, Socket } from "socket.io-client";
import { useNavigate } from "react-router";

enum UserAuthStatus {
  stage_setUsername,
  stage_2faAuthNew,
  stage_2faAuthOld,
  stage_completed,
  stage_intraLogin,
}

export enum InviteStatus {
  invitee_no_exist,
  invitee_no_available,
  inviter_no_exist,
  inviter_no_available,
  invite_sent,
  response_received,
}

export interface InviteProps {
  inviterName: string;
  inviteeName: string;
  status: InviteStatus;
  accept: boolean;
}

type SocketProviderProps = {
  children: React.ReactNode;
};

export const SocketContext = createContext<Socket | undefined>(undefined);

export const SocketProvider = ({ children }: SocketProviderProps) => {
  const [socket, setSocket] = useState<Socket>();
  const [loginStatus, setLoginStatus] = useState(0);
  const navigate = useNavigate();

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
        window.location.href = "/";
      }
    }

    const interval = setInterval(getStatus, 60000);
    return () => {
      clearInterval(interval);
    };
  }, []);

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
        if (body.authStatus === UserAuthStatus.stage_completed) {
          const newSocket = io(`${process.env.REACT_APP_HOST_URL}/sessions`, {
            transports: ["websocket"],
            withCredentials: true,
          });
          setSocket(newSocket);
          return () => {
            newSocket.disconnect();
          };
        }
      }
    }
    if (loginStatus !== UserAuthStatus.stage_completed) {
      getStatus();
    }
  }, [loginStatus]);

  useEffect(() => {
    if (socket) {
      socket.on("inviteResponse", (data: InviteProps) => {
        if (data.status !== InviteStatus.response_received) {
          navigate("/home");
        }
      });
    }
  }, [navigate, socket]);

  return (
    <SocketContext.Provider value={socket}>{children}</SocketContext.Provider>
  );
};
