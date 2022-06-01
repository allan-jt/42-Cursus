#include "Zombie.hpp"

int main(void) {
	Zombie *test1 = newZombie("test1");
	Zombie *test3 = newZombie("test3");
	test1->announce();
	randomChump("test2");
	delete test1;
	test3->announce();
	delete test3;
	randomChump("test4");
	Zombie *test4 = newZombie("");
	test4->announce();
	delete test4;
	randomChump("");
}