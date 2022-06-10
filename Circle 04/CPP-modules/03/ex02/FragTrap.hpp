#ifndef FragTrap_HPP
#define FragTrap_HPP

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {
	public:
		void	highFivesGuys(void);

		// (con/de)structors
		FragTrap(void);
		FragTrap(std::string const name);
		FragTrap(FragTrap const &copy);
		~FragTrap(void);
		FragTrap &operator=(FragTrap const &rhs);
};


#endif