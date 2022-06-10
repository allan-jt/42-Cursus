#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"

class Dog : public Animal {
	public:
		void	makeSound(void) const;
	
		// (con/de)structors
		Dog(void);
		Dog(Dog const &copy);
		~Dog(void);
		Dog &operator=(Dog const &rhs);
};

#endif