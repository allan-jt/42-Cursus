#include "AMateria.hpp"

/****************************(CON/DE)STRUCTORS****************************/ 
AMateria::AMateria(void) : _type("NULL") {
	std::cout << "Default constructor for AMateria called" << std::endl;
}

AMateria::AMateria(AMateria const &copy) {
	*this = copy;
	std::cout << "Copy constructor for AMateria called" << std::endl;
}

AMateria::AMateria(std::string const & type) :
	_type(type.empty() ? "NULL" : type) {
	std::cout << "Type constructor for AMateria called" << std::endl;
}

AMateria::~AMateria(void) {
	std::cout << "Destructor for AMateria called" << std::endl;
}

AMateria &AMateria::operator=(AMateria const &rhs) {
	if (this != &rhs)
		this->_type = rhs.getType();
	std::cout << "Copy asignment operator for AMateria called" << std::endl;
	return (*this);
}
/*************************************************************************/

std::string const &AMateria::getType(void) const {return (this->_type);}

void	AMateria::use(ICharacter& target) {
	// this should never be called
	std::cout << this->_type << " called from AMasterial on "
		<< target.getName() << std::endl;
}