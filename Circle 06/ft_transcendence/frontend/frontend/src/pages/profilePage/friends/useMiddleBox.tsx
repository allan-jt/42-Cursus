import { useState } from "react";

export default function UseMiddleBox() {
  const [isOpen, setIsOpen] = useState(false);

  const toggle = () => {
    setIsOpen(!isOpen);
  };

  return {
    isOpen,
    toggle
  };
}
