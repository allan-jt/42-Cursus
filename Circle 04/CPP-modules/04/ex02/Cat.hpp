#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"

class Cat : public Animal {
	private:
		Brain *brain;
	
	public:
		void	makeSound(void) const;
		Brain	*getBrain(void) const;
	
		// (con/de)structors
		Cat(void);
		Cat(Cat const &copy);
		~Cat(void);
		Cat &operator=(Cat const &rhs);
};

#endif