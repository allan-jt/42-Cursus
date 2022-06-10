#include "DiamondTrap.hpp"

static void	printCotent(DiamondTrap &name) {
	std::cout << "Name: " << name.getName()
		<< " | HP: " << name.getHitPoint()
		<< " | EP: " << name.getEnergyPoint()
		<< " | AD: " << name.getAttackDamage()
		<< std::endl;
}

int main(void) {
	DiamondTrap dt("Allan");
	std::cout << std::endl;
	printCotent(dt);
	
	std::cout << std::endl;
	dt.attack("John");

	DiamondTrap dt2(dt);
	std::cout << std::endl;
	printCotent(dt);

	dt2.whoAmI();
	std::cout << std::endl;
	return (0);
}