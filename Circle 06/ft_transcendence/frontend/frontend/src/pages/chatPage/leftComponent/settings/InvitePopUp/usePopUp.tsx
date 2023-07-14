import { useState } from "react";

export default function UsePopUp() {
  const [isInviteOpen, setIsInviteOpen] = useState(false);

  const handleInviteOpen = () => {
    setIsInviteOpen(true);
  };

  const handleInviteClose = () => {
    setIsInviteOpen(false);
  };

  return {
    isInviteOpen,
    handleInviteOpen,
    handleInviteClose,
  };
}
