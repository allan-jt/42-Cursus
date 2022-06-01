#include "HumanA.hpp"
#include "HumanB.hpp"

int main(void) {
	{
		Weapon club = Weapon("crude spiked club");
		HumanA bob("Bob", club);
		bob.attack();
		club.setType("some other type of club");
		bob.attack();
	}
	{
		Weapon club = Weapon("crude spiked club");
		Weapon plo = Weapon("");
		HumanB jim("Jim");
		jim.attack();
		jim.setWeapon(club); // my addition
		jim.attack();
		club.setType("some other type of club");
		jim.attack();
	}
	return 0;
}
