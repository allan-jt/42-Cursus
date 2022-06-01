#include "Zombie.hpp"

void	randomChump(std::string name) {
	Zombie zombie = name.empty() ? Zombie("no-name") : Zombie(name);
	zombie.announce();
}