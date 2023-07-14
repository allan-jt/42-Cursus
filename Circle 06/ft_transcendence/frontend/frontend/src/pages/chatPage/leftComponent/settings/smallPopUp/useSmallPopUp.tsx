import { useState } from "react";

export default function UsePopUp() {
  const [isSmallOpen, setIsOpen] = useState(false);

  const handleOpen = () => {
    setIsOpen(true);
  };

  const handleClose = () => {
    setIsOpen(false);
  };

  return {
    isSmallOpen,
    handleOpen,
    handleClose,
  };
}
