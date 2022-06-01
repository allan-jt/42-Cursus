#include "Zombie.hpp"

Zombie	*zombieHorde(int N, std::string name) {
	if (N <= 0)
		return (NULL);
	Zombie	*listOfZombs = new(std::nothrow) Zombie[N];
	for (int i = 0; listOfZombs && i < N; i++)
		listOfZombs[i].setName(name);
	return (listOfZombs);
}