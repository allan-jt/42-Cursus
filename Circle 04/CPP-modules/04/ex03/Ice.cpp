#include "Ice.hpp"

/****************************(CON/DE)STRUCTORS****************************/ 
Ice::Ice(void) {
	this->_type = "ice";
	std::cout << "Default constructor for Ice called" << std::endl;
}

Ice::Ice(Ice const &copy) : AMateria() {
	*this = copy;
	std::cout << "Copy constructor for Ice called" << std::endl;
}

Ice::~Ice(void) {
	std::cout << "Destructor for Ice called" << std::endl;
}

Ice &Ice::operator=(Ice const &rhs) {
	if (this != &rhs)
		this->_type = rhs.getType();
	std::cout << "Copy asignment operator for Ice called" << std::endl;
	return (*this);
}
/*************************************************************************/

AMateria *Ice::clone() const {return new(std::nothrow) Ice();}

void	Ice::use(ICharacter& target) {
	std::cout << "* shoots an ice bolt at "
		<< target.getName() << " *" << std::endl;
}