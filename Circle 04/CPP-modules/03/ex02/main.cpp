#include "FragTrap.hpp"
#include "ScavTrap.hpp"

static void	printCotent(ClapTrap &name) {
	std::cout << "Name: " << name.getName()
		<< " | HP: " << name.getHitPoint()
		<< " | EP: " << name.getEnergyPoint()
		<< " | AD: " << name.getAttackDamage()
		<< std::endl;
}

int main(void) {
	std::cout << "1----------------- " << std::endl;
	FragTrap jack ("Jack");
	printCotent(jack);
	FragTrap jill ("Jill");
	printCotent(jill);

	std::cout << "2----------------- " << std::endl;
	for (int i = 0; i < 7; i++) {
		jill.attack("jack");
		jack.takeDamage(20);
	}
	printCotent(jill);
	printCotent(jack);

	std::cout << "3----------------- " << std::endl;
	jack.highFivesGuys();
	jill.highFivesGuys();

	return (0);
}