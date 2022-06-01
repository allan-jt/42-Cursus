#include "Zombie.hpp"

Zombie::Zombie(std::string name) : _name(name) {}

void	Zombie::announce(void) const {
	std::cout << this->_name << ": BraiiiiiiinnnzzzZ..."
		<< std::endl;
}

Zombie::~Zombie(void) {
	std::cout << this->_name << " is destroyed! :D"
		<< std::endl;
}