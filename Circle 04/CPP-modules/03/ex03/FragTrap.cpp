#include "FragTrap.hpp"

void	FragTrap::highFivesGuys(void) {
	this->printMsg(this->_hitPoint == 0 ? 
		this->_name + " has no hitpoints, so no highfive stuff! (FT)" :
		this->_name + " is positive and wants a highfive! (FT)");
}

/****************************(CON/DE)STRUCTORS****************************/ 
FragTrap::FragTrap(void) {
	this->_name = "NULL";
	this->_hitPoint = 100;
	this->_energyPoint = 100;
	this->_attackDamage = 30;
	this->printMsg("FragTrap is initialized without name!");
}

FragTrap::FragTrap(std::string const name) : ClapTrap(name) {
	this->_hitPoint = 100;
	this->_energyPoint = 100;
	this->_attackDamage = 30;
	if (name.empty()) {
		this->_name = "NULL";
		this->printMsg("FragTrap is initialized with empty name!");
		return;
	}
	this->_name = name;
	this->printMsg("FragTrap " + this->_name + " is initialized!");
}

FragTrap::FragTrap(FragTrap const &copy) : ClapTrap(copy)  {
	this->printMsg(copy.getName() + " will be copied (FT)");
	*this = copy;
}

FragTrap::~FragTrap(void) {
	this->printMsg("FragTrap " + this->_name + " is destroyed!");
}

FragTrap &FragTrap::operator=(FragTrap const &rhs) {
	this->printMsg("All elements of " + this->_name + " are copied! (FT)");
	if (this != &rhs) {
		this->_name = ((FragTrap &) rhs).getName();
		this->_hitPoint = ((FragTrap &) rhs).getHitPoint();
		this->_energyPoint = ((FragTrap &) rhs).getEnergyPoint();
		this->_attackDamage = ((FragTrap &) rhs).getAttackDamage();
	}
	return (*this);
}
/*************************************************************************/