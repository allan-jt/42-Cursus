#include "Character.hpp"

/****************************(CON/DE)STRUCTORS****************************/ 
Character::Character(void) : _name("NULL") {
	for (int i = 0; i < 4; i++)
		this->_materia[i] = NULL;
	std::cout << "Default constructor for Character called" << std::endl;
}

Character::Character(std::string const &name) :
	_name(name.empty() ? "NULL" : name) {
	for (int i = 0; i < 4; i++)
		this->_materia[i] = NULL;
	std::cout << "Name constructor for Character called" << std::endl;
}

Character::Character(Character const &copy) {
	*this = copy;
	std::cout << "Copy constructor for Character called" << std::endl;
}

Character::~Character(void) {
	std::cout << "Destructor for Character called" << std::endl;
	for (int i = 0; i < 4; i++)
		delete this->_materia[i];
}

Character &Character::operator=(Character const &rhs) {
	if (this != &rhs) {
		for (int i = 0; i < 4; i++) {
			delete this->_materia[i];
			this->_materia[i] = ((Character &)rhs).getAMateria(i)->clone();
		}
	}
	std::cout << "Copy asignment operator for Character called"
		<< std::endl;
	return (*this);
}
/*************************************************************************/


/***************************ICharacter Functions**************************/ 
std::string const &Character::getName() const {return (this->_name);}

void	Character::equip(AMateria* m) {
	for (int i = 0; i < 4; i++) {
		if (this->_materia[i])
			continue;
		this->_materia[i] = m;
		break;
	}
}

void	Character::unequip(int idx) {
	if (idx < 4 && idx >= 0)
		this->_materia[idx] = NULL;
}

void	Character::use(int idx, ICharacter &target) {
	if (idx < 4 && idx >= 0 && this->_materia[idx])
		this->_materia[idx]->use(target);
}

/*************************************************************************/

AMateria	*Character::getAMateria(int idx) const {
	if (idx < 4 && idx >= 0)
		return (this->_materia[idx]);
	return (NULL);
}