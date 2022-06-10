#include "Dog.hpp"

/****************************(CON/DE)STRUCTORS****************************/ 
Dog::Dog(void) {
	this->type = "Dog";
	std::cout << "Default constructor for Dog called" << std::endl;
}

Dog::Dog(Dog const &copy) : Animal() {
	*this = copy;
	std::cout << "Copy constructor for Dog called" << std::endl;
}

Dog::~Dog(void) {
	std::cout << "Destructor for Dog called" << std::endl;
}

Dog &Dog::operator=(Dog const &rhs) {
	if (this != &rhs)
		this->type = rhs.getType();
	std::cout << "Copy asignment operator for Dog called" << std::endl;
	return (*this);
}
/*************************************************************************/

void	Dog::makeSound(void) const {
	std::cout << "Bark bark!" << std::endl;
}