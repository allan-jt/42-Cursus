#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "Brain.hpp"

class Animal {
	protected:
		std::string type;

	public:
		virtual void	makeSound(void) const;
		std::string		getType(void) const;
		
		// (con/de)structors
		Animal(void);
		Animal(Animal const &copy);
		virtual ~Animal(void);
		Animal &operator=(Animal const &rhs);
};

#endif