#include "Cure.hpp"

/****************************(CON/DE)STRUCTORS****************************/ 
Cure::Cure(void) {
	this->_type = "cure";
	std::cout << "Default constructor for Cure called" << std::endl;
}

Cure::Cure(Cure const &copy) : AMateria() {
	*this = copy;
	std::cout << "Copy constructor for Cure called" << std::endl;
}

Cure::~Cure(void) {
	std::cout << "Destructor for Cure called" << std::endl;
}

Cure &Cure::operator=(Cure const &rhs) {
	if (this != &rhs)
		this->_type = rhs.getType();
	std::cout << "Copy asignment operator for Cure called" << std::endl;
	return (*this);
}
/*************************************************************************/

AMateria *Cure::clone() const {return new(std::nothrow) Cure();}

void	Cure::use(ICharacter& target) {
	std::cout << "* heals " << target.getName() 
		<< "'s wounds *" << std::endl;
}