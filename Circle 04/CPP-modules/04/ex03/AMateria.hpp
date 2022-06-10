#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include <iostream>
#include <string>
#include "ICharacter.hpp"

class AMateria {
	protected:
		std::string _type;

	public:
		std::string const &getType() const;
		virtual AMateria *clone() const = 0;
		virtual void use(ICharacter& target);
		
		// (con/de)structors
		AMateria(void);
		AMateria(AMateria const &copy);
		AMateria(std::string const & type);
		virtual ~AMateria(void);
		AMateria &operator=(AMateria const &rhs);
};

#endif