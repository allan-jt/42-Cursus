#include "Zombie.hpp"

Zombie::Zombie(void) {}

void	Zombie::announce(void) const {
	std::cout << this->_name << ": BraiiiiiiinnnzzzZ..."
		<< std::endl;
}

void	Zombie::setName(std::string name) {
	this->_name = name.empty() ? "no-name" : name;
}

Zombie::~Zombie(void) {
	std::cout << this->_name << " is destroyed! :D"
		<< std::endl;
}