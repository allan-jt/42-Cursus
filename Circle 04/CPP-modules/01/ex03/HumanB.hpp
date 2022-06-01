#ifndef HUMANB_HPP
#define HUMANB_HPP

#include <iostream>
#include "Weapon.hpp"

class HumanB {
	public: 
		HumanB(std::string name);
		void	attack(void) const;
		void	setWeapon(Weapon &weapon);
		~HumanB(void);
	
	private:
		std::string	_name;
		Weapon		*_weapon;
};

#endif