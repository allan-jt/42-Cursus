#include "Dog.hpp"

/****************************(CON/DE)STRUCTORS****************************/ 
Dog::Dog(void) : brain(new(std::nothrow) Brain()) {
	this->type = "Dog";
	if (brain)
		brain->setAllIdeas("Dog ideas");
	std::cout << "Default constructor for Dog called" << std::endl;
}

Dog::Dog(Dog const &copy) : Animal() {
	*this = copy;
	std::cout << "Copy constructor for Dog called" << std::endl;
}

Dog::~Dog(void) {
	std::cout << "Destructor for Dog called" << std::endl;
	delete brain;
}

Dog &Dog::operator=(Dog const &rhs) {
	if (this != &rhs) {
		this->type = rhs.getType();
		brain = new(std::nothrow) Brain(*rhs.getBrain());
	}
	std::cout << "Copy asignment operator for Dog called" << std::endl;
	return (*this);
}
/*************************************************************************/

void	Dog::makeSound(void) const {
	std::cout << "Bark bark!" << std::endl;
}

Brain	*Dog::getBrain(void) const {return (this->brain);}