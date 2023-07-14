import { useState } from "react";

export default function useGamePopUp() {
  const [isGameInviteOpen, setIsOpen] = useState(false);

  const handleOpen = () => {
    setIsOpen(true);
  };

  const handleClose = () => {
    setIsOpen(false);
  };

  return {
    isGameInviteOpen,
    handleOpen,
    handleClose,
  };
}
