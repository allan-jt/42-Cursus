#include "Weapon.hpp"

Weapon::Weapon(std::string type) : _type(type) {
	if (this->_type.empty())
		this->_type = "Weapon X";
};

std::string const	&Weapon::getType(void) const {
	return (this->_type);
}

void	Weapon::setType(std::string newType) {
	this->_type = newType.empty() ? "Weapon X" : newType;
}

Weapon::~Weapon(void) {}