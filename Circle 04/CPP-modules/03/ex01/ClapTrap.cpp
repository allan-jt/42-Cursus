#include "ClapTrap.hpp"

/*********************************ACTIONS*********************************/
void	ClapTrap::attack(const std::string& target) {
	std::string targ = target.empty() ? "someone" : target;
	
	if (!this->_hitPoint)
		return (this->printMsg(this->_name + " cannot attack because it" +
			" has no hit points"));
	if (!this->_energyPoint)
		return (this->printMsg(this->_name + " cannot attack because it" +
			" has no energy points"));
	this->_energyPoint--;
	std::cout << this->_name << " attacked " << targ << ", causing "
		<< this->_attackDamage << " points of damage." << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount) {
	if (!this->_hitPoint)
		return (this->printMsg(this->_name + " cannot be attacked because it" +
			" has no hit points"));
	this->_hitPoint -= this->_hitPoint <= amount ? this->_hitPoint : amount;
	std::cout << this->_name << " was attacked and now has " <<
		this->_hitPoint << " hit points!" << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount) {
	if (!this->_hitPoint)
		return (this->printMsg("Too late! " + this->_name + 
			" has already reached 0 hit points :("));
	if (!this->_energyPoint)
		return (this->printMsg(this->_name + " cannot be repaired "
			+ "because it has 0 energy points!"));
	this->_energyPoint--;
	this->_hitPoint += amount;
	std::cout << this->_name << "'s hit points has been increased to "
		<< this->_hitPoint << "!" << std::endl;
}
/*************************************************************************/


/******************************GETTERS/UTILS******************************/
std::string	ClapTrap::getName(void) const {return (this->_name);}

unsigned int ClapTrap::getHitPoint(void) const {return (this->_hitPoint);}

unsigned int ClapTrap::getEnergyPoint(void) const {return (this->_energyPoint);}

unsigned int ClapTrap::getAttackDamage(void) const {return (this->_attackDamage);}

void	ClapTrap::printMsg(std::string msg) const {
	std::cout << msg << std::endl;
}
/*************************************************************************/


/****************************(CON/DE)STRUCTORS****************************/ 
ClapTrap::ClapTrap(void) : _name("NULL"), _hitPoint(10),
	_energyPoint(10), _attackDamage(0) {
	this->printMsg("ClapTrap is initialized without name!");
}

ClapTrap::ClapTrap(ClapTrap const &copy) {
	this->printMsg("ClapTrap " + this->_name + " will be copied!");
	*this = copy;
}

ClapTrap::ClapTrap(std::string const name) : _name(name), _hitPoint(10),
	_energyPoint(10), _attackDamage(0) {
	if (_name.empty()) {
		_name = "NULL";		
		std::cout << "ClapTrap " << this->_name 
			<< " is initialized with empty name!" << std::endl;
		return;
	}
	this->printMsg("ClapTrap " + this->_name + " is initialized!");
}

ClapTrap::~ClapTrap(void) {
	this->printMsg("ClapTrap " + this->_name + " is destroyed!");
}

ClapTrap &ClapTrap::operator=(ClapTrap const &rhs) {
	this->printMsg("All elements of Claptrap " + rhs.getName() + " are copied!");
	if (this != &rhs) {
		this->_name = ((ClapTrap &) rhs).getName();
		this->_hitPoint = ((ClapTrap &) rhs).getHitPoint();
		this->_energyPoint = ((ClapTrap &) rhs).getEnergyPoint();
		this->_attackDamage = ((ClapTrap &) rhs).getAttackDamage();
	}
	return (*this);
}
/*************************************************************************/