#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"

class Dog : public Animal {
	private:
		Brain *brain;
	
	public:
		void	makeSound(void) const;
		Brain	*getBrain(void) const;
	
		// (con/de)structors
		Dog(void);
		Dog(Dog const &copy);
		~Dog(void);
		Dog &operator=(Dog const &rhs);
};

#endif