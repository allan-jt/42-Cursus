#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &weapon) 
	: _name(name), _weapon(weapon) {
		if (this->_name.empty())
			this->_name = "no-name";
	}

void	HumanA::attack(void) const {
	std::cout << this->_name << " attacks with their " 
		<< this->_weapon.getType() << std::endl;
}

HumanA::~HumanA(void) {}