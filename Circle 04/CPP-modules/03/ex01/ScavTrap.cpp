#include "ScavTrap.hpp"

void	ScavTrap::attack(const std::string& target) {
	std::string targ = target.empty() ? "someone" : target;
	
	if (!this->_hitPoint)
		 return (this->printMsg(this->_name + " cannot attack because it"
			 + " has no hit points (ST)"));
	if (!this->_energyPoint)
		return (this->printMsg(this->_name + " cannot attack because it"
			+ " has no energy points (ST)"));
	this->_energyPoint--;
	std::cout << this->_name << " attacked " << targ << ", causing "
		<< this->_attackDamage << " points of damage. (ST)" << std::endl;
}

void 	ScavTrap::guardGate(void) {
	this->printMsg(this->_hitPoint == 0 ? 
		this->_name + " has no hitpoints, so no gatekeeper stuff! (ST)" :
		this->_name + " is now in gatekeeper mode! (ST)");
}

/****************************(CON/DE)STRUCTORS****************************/ 
ScavTrap::ScavTrap(void) {
	this->_name = "NULL";
	this->_hitPoint = 100;
	this->_energyPoint = 50;
	this->_attackDamage = 20;
	this->printMsg("ScavTrap is initialized without name!");
}

ScavTrap::ScavTrap(std::string const name) : ClapTrap(name) {
	this->_hitPoint = 100;
	this->_energyPoint = 50;
	this->_attackDamage = 20;
	if (name.empty()) {
		this->_name = "NULL";
		this->printMsg("ScavTrap is initialized with empty name!");
		return;
	}
	this->_name = name;
	std::cout << "ScavTrap " << this->_name << " is initialized!"
		<< std::endl;
}

ScavTrap::ScavTrap(ScavTrap const &copy) : ClapTrap(copy)  {
	this->printMsg(copy.getName() + " will be copied (ST)");
	*this = copy;
}

ScavTrap::~ScavTrap(void) {
	this->printMsg("ScavTrap " + this->_name + " is destroyed!");
}

ScavTrap &ScavTrap::operator=(ScavTrap const &rhs) {
	this->printMsg("All elements of " + this->_name + " are copied! (ST)");
	if (this != &rhs) {
		this->_name = ((ScavTrap &) rhs).getName();
		this->_hitPoint = ((ScavTrap &) rhs).getHitPoint();
		this->_energyPoint = ((ScavTrap &) rhs).getEnergyPoint();
		this->_attackDamage = ((ScavTrap &) rhs).getAttackDamage();
	}
	return (*this);
}
/*************************************************************************/