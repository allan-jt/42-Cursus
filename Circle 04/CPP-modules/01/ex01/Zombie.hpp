#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>
#include <iostream>
#include <new>
#include <climits>

class Zombie {
	public:
		Zombie(void);
		void	announce(void) const;
		void	setName(std::string name);
		~Zombie(void);

	private:
		std::string	_name;
};

Zombie*	zombieHorde(int N, std::string name);

#endif