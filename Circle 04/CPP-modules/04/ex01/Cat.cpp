#include "Cat.hpp"

/****************************(CON/DE)STRUCTORS****************************/ 
Cat::Cat(void) : brain(new(std::nothrow) Brain()) {
	this->type = "Cat";
	if (brain)
		brain->setAllIdeas("Cat ideas");
	std::cout << "Default constructor for Cat called" << std::endl;
}

Cat::Cat(Cat const &copy) : Animal() {
	*this = copy;
	std::cout << "Copy constructor for Cat called" << std::endl;
}

Cat::~Cat(void) {
	std::cout << "Destructor for Cat called" << std::endl;
	delete brain;
}

Cat &Cat::operator=(Cat const &rhs) {
	if (this != &rhs) {
		this->type = rhs.getType();
		brain = new(std::nothrow) Brain(*rhs.getBrain());
	}
	std::cout << "Copy asignment operator for Cat called" << std::endl;
	return (*this);
}
/*************************************************************************/

void	Cat::makeSound(void) const {
	std::cout << "Meeeeoooowww!" << std::endl;
}

Brain	*Cat::getBrain(void) const {return (this->brain);}