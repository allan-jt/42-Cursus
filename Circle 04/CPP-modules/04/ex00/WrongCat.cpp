#include "WrongCat.hpp"

/****************************(CON/DE)STRUCTORS****************************/ 
WrongCat::WrongCat(void) {
	this->type = "WrongCat";
	std::cout << "Default constructor for WrongCat called" << std::endl;
}

WrongCat::WrongCat(WrongCat const &copy) : WrongAnimal() {
	*this = copy;
	std::cout << "Copy constructor for WrongCat called" << std::endl;
}

WrongCat::~WrongCat(void) {
	std::cout << "Destructor for WrongCat called" << std::endl;
}

WrongCat &WrongCat::operator=(WrongCat const &rhs) {
	if (this != &rhs)
		this->type = rhs.getType();
	std::cout << "Copy asignment operator for WrongCat called" << std::endl;
	return (*this);
}
/*************************************************************************/

void	WrongCat::makeSound(void) const {
	std::cout << "Mrrrrrrrrrrr!" << std::endl;
}