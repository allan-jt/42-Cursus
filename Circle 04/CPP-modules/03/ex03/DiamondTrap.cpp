#include "DiamondTrap.hpp"

void	DiamondTrap::whoAmI(void) const {
	this->printMsg("I'm DiamondTrap " + this->_name
		+ " and Claptrap " + ClapTrap::_name + "!");
}

std::string	DiamondTrap::getName(void) const {
	return (this->_name);
}

/****************************(CON/DE)STRUCTORS****************************/ 
DiamondTrap::DiamondTrap(void) : _name("NULL") {
	ClapTrap::_name = this->_name + "_clap_name";
	this->_attackDamage = 30;
	this->printMsg("DiamondTrap is initialized with no name!");
}

DiamondTrap::DiamondTrap(std::string const name) :
	_name(name.empty() ? "NULL" : name) {
	ClapTrap::_name = this->_name + "_clap_name";
	this->_attackDamage = 30;
	this->printMsg(name.empty() ? "DiamondTrap is initialized with no name!"
		: "DiamondTrap " + this->_name + " is initialized!");
}

DiamondTrap::DiamondTrap(DiamondTrap const &copy) : ClapTrap(copy), 
	FragTrap(copy), ScavTrap(copy) {
	this->printMsg("DiamondTrap " + copy.getName() + " will be copied!");
	*this = copy;
}

DiamondTrap::~DiamondTrap(void) {
	this->printMsg("DiamondTrap " + this->_name + " is destroyed!");
}

DiamondTrap &DiamondTrap::operator=(DiamondTrap const &rhs) {
	if (this != &rhs) {
		this->_name = ((DiamondTrap &) rhs).getName();
		this->_hitPoint = ((DiamondTrap &) rhs).getHitPoint();
		this->_energyPoint = ((DiamondTrap &) rhs).getEnergyPoint();
		this->_attackDamage= ((DiamondTrap &) rhs).getAttackDamage();
	}
	this->printMsg("Elements of DiamondTrap " + rhs.getName() 
		+ " are copied!");
	return (*this);
}
/*************************************************************************/