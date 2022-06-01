#include "HumanB.hpp"

HumanB::HumanB(std::string name) : _name(name), _weapon(NULL) {
	if (this->_name.empty())
		this->_name = "no-name";
}

void	HumanB::attack(void) const {
	if (this->_weapon == NULL) {
		std::cout << this->_name << " has no weapon!" << std::endl;
		return;
	}
	std::cout << this->_name << " attacks with their " 
		<< (*this->_weapon).getType() << std::endl;
}

void HumanB::setWeapon (Weapon &weapon) {
	this->_weapon = &weapon;
}

HumanB::~HumanB(void) {}