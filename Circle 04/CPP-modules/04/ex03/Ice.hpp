#ifndef ICE_HPP
#define ICE_HPP

#include "AMateria.hpp"

class Ice : public AMateria {
	public:
		virtual AMateria *clone() const;
		virtual void use(ICharacter& target);
		
		// (con/de)structors
		Ice(void);
		Ice(Ice const &copy);
		virtual ~Ice(void);
		Ice &operator=(Ice const &rhs);
};

#endif