#ifndef WRONGCAT_HPP
#define WRONGCAT_HPP

#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal {
	public:
		void	makeSound(void) const;
	
		// (con/de)structors
		WrongCat(void);
		WrongCat(WrongCat const &copy);
		~WrongCat(void);
		WrongCat &operator=(WrongCat const &rhs);
};

#endif