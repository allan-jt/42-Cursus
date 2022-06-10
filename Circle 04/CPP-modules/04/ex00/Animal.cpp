#include "Animal.hpp"

/****************************(CON/DE)STRUCTORS****************************/ 
Animal::Animal(void) : type("UNKNOWN ANIMAL") {
	std::cout << "Default constructor for Animal called" << std::endl;
}

Animal::Animal(Animal const &copy) {
	*this = copy;
	std::cout << "Copy constructor for Animal called" << std::endl;
}

Animal::~Animal(void) {
	std::cout << "Destructor for Animal called" << std::endl;
}

Animal &Animal::operator=(Animal const &rhs) {
	if (this != &rhs)
		this->type = rhs.getType();
	std::cout << "Copy asignment operator for Animal called" << std::endl;
	return (*this);
}
/*************************************************************************/

void	Animal::makeSound(void) const {
	std::cout << "Makes unknown noise!" << std::endl;
}

std::string	Animal::getType(void) const {return (this->type);}