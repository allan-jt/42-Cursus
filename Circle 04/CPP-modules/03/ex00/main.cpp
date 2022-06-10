#include "ClapTrap.hpp"

static void	printCotent(ClapTrap &name) {
	std::cout << "Name: " << name.getName()
		<< " | HP: " << name.getHitPoint()
		<< " | EP: " << name.getEnergyPoint()
		<< " | AD: " << name.getAttackDamage()
		<< std::endl;
}

int main(void) {
	std::cout << "1----------------- " << std::endl;
	ClapTrap one;
	printCotent(one);

	std::cout << "2----------------- " << std::endl;
	ClapTrap jack("Jack");
	printCotent(jack);
	ClapTrap jill("Jill");
	printCotent(jill);

	std::cout << "3----------------- " << std::endl;
	jack.attack("Jill");
	jill.takeDamage(5);
	jack.takeDamage(5);
	printCotent(jack);
	printCotent(jill);

	std::cout << "4----------------- " << std::endl;
	jack.attack("Jill");
	jill.takeDamage(6);
	printCotent(jack);
	printCotent(jill);

	std::cout << "5----------------- " << std::endl;
	jill.attack("Jack");
	jill.beRepaired(5);
	printCotent(jill);
	jack.beRepaired(6);
	printCotent(jack);

	return (0);
}