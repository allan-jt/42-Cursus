#include "Zombie.hpp"

int main(void) {
	Zombie	*zombs1 = zombieHorde(5, "test1");
	Zombie	*zombs2 = zombieHorde(5, "test2");
	for (int i = 0; i < 5; i++) {
		if (zombs1)
			zombs1[i].announce();
		if (zombs2)
			zombs2[i].announce();
	}
	delete [] zombs2;
	delete [] zombs1;

	Zombie	*zombs3 = zombieHorde(INT_MAX/1000, "test3");
	Zombie	*zombs4 = zombieHorde(INT_MIN, "test4");
	for (int i = 0; i < 5; i++) {
		if (zombs3)
			zombs3[i].announce();
		if (zombs4)
			zombs4[i].announce();
	}
	delete [] zombs3;
	delete [] zombs4;
}