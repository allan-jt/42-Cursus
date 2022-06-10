#ifndef DIAMONDTRAP_HPP
#define DIAMONDTRAP_HPP

#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class DiamondTrap : public FragTrap, public ScavTrap {
	private:
		std::string _name;

	public:
		void		whoAmI(void) const;
		std::string	getName(void) const;

		// (con/de)structors
		DiamondTrap(void);
		DiamondTrap(std::string const name);
		DiamondTrap(DiamondTrap const &copy);
		~DiamondTrap(void);
		DiamondTrap &operator=(DiamondTrap const &rhs);
};

#endif