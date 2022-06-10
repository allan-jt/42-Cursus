#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : virtual public ClapTrap {
	public:
		void	attack(const std::string& target);
		void 	guardGate(void);

		// (con/de)structors
		ScavTrap(void);
		ScavTrap(std::string const name);
		ScavTrap(ScavTrap const &copy);
		~ScavTrap(void);
		ScavTrap &operator=(ScavTrap const &rhs);
};


#endif