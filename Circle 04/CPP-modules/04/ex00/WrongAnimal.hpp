#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <iostream>
#include <string>

class WrongAnimal {
	protected:
		std::string type;

	public:
		void	makeSound(void) const;
		std::string		getType(void) const;
		
		// (con/de)structors
		WrongAnimal(void);
		WrongAnimal(WrongAnimal const &copy);
		~WrongAnimal(void);
		WrongAnimal &operator=(WrongAnimal const &rhs);
};

#endif