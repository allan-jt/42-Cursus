#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>
#include <string>

class	ClapTrap {
	protected:
		std::string		_name;
		unsigned int	_hitPoint;
		unsigned int	_energyPoint;
		unsigned int	_attackDamage;
		void			printMsg(std::string msg) const;

	public:
		// actions
		void	attack(const std::string& target);
		void	takeDamage(unsigned int amount);
		void	beRepaired(unsigned int amount);

		// getters & other utils
		std::string		getName(void) const;
		unsigned int	getHitPoint(void) const;
		unsigned int	getEnergyPoint(void) const;
		unsigned int	getAttackDamage(void) const;

		// (con/de)structors
		ClapTrap(void);
		ClapTrap(ClapTrap const &copy);
		ClapTrap(std::string const name);
		~ClapTrap(void);
		ClapTrap &operator=(ClapTrap const &rhs);
};


#endif