#include "MateriaSource.hpp"

/****************************(CON/DE)STRUCTORS****************************/ 
MateriaSource::MateriaSource(void) {
	for (int i = 0; i < 4; i++)
		this->_materia[i] = NULL;
	std::cout << "Default constructor for MateriaSource called" << std::endl;
}

MateriaSource::MateriaSource(MateriaSource const &copy) {
	*this = copy;
	std::cout << "Copy constructor for MateriaSource called" << std::endl;
}

MateriaSource::~MateriaSource(void) {
	std::cout << "Destructor for MateriaSource called" << std::endl;
	for (int i = 0; i < 4; i++)
		delete this->_materia[i];
}

MateriaSource &MateriaSource::operator=(MateriaSource const &rhs) {
	if (this != &rhs) {
		for (int i = 0; i < 4; i++) {
			delete this->_materia[i];
			this->_materia[i] = ((MateriaSource &) rhs).createMateria(
				this->_materia[i]->getType());
		}
	}
	std::cout << "Copy asignment operator for MateriaSource called"
		<< std::endl;
	return (*this);
}
/*************************************************************************/

void	MateriaSource::learnMateria(AMateria *m) {
	for (int i = 0; i < 4; i++) {
		if (this->_materia[i])
			continue;
		this->_materia[i] = m;
		break;
	}
}

AMateria	*MateriaSource::createMateria(std::string const & type) {
	for (int i = 0; i < 4; i++) {
		if (this->_materia[i] && this->_materia[i]->getType() == type)
			return _materia[i]->clone();
	}
	return NULL;
}
