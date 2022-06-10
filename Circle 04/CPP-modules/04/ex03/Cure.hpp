#ifndef CURE_HPP
#define CURE_HPP

#include "AMateria.hpp"

class Cure : public AMateria {
	public:
		virtual AMateria *clone() const;
		virtual void use(ICharacter& target);
		
		// (con/de)structors
		Cure(void);
		Cure(Cure const &copy);
		virtual ~Cure(void);
		Cure &operator=(Cure const &rhs);
};

#endif