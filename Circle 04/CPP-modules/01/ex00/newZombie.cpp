#include "Zombie.hpp"

Zombie *newZombie(std::string name) {
	if (name.empty())
		return (new Zombie("no-name"));
	return (new Zombie(name));
}