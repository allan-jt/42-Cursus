import { useState } from "react";

export default function UsePopUp() {
  const [isOpen, setIsOpen] = useState(false);

  

  const toggleOn = () => {
    setIsOpen(true);
  };

  const toggleOff = () => {
    setIsOpen(false);
  };

  return {
    isOpen,
    toggleOn,
    toggleOff,
  };
}
