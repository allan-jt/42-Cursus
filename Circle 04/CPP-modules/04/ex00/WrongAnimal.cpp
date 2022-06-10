#include "WrongAnimal.hpp"

/****************************(CON/DE)STRUCTORS****************************/ 
WrongAnimal::WrongAnimal(void) : type("UNKNOWN WRONG ANIMAL") {
	std::cout << "Default constructor for WrongAnimal called" << std::endl;
}

WrongAnimal::WrongAnimal(WrongAnimal const &copy) {
	*this = copy;
	std::cout << "Copy constructor for WrongAnimal called" << std::endl;
}

WrongAnimal::~WrongAnimal(void) {
	std::cout << "Destructor for WrongAnimal called" << std::endl;
}

WrongAnimal &WrongAnimal::operator=(WrongAnimal const &rhs) {
	if (this != &rhs)
		this->type = rhs.getType();
	std::cout << "Copy asignment operator for WrongAnimal called" << std::endl;
	return (*this);
}
/*************************************************************************/

void	WrongAnimal::makeSound(void) const {
	std::cout << "Makes wrong unknown noise!" << std::endl;
}

std::string	WrongAnimal::getType(void) const {return (this->type);}