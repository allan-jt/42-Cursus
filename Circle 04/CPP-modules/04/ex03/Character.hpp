#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "AMateria.hpp"

class Character : public ICharacter {
	protected:
		std::string	_name;
		AMateria	*_materia[4];

	public:		
		AMateria *getAMateria(int idx) const;
		
		//ICharacter functions
		std::string const & getName() const;
		void equip(AMateria* m);
		void unequip(int idx);
		void use(int idx, ICharacter& target);

		// (con/de)structors
		Character(void);
		Character(std::string const &name);
		Character(Character const &copy);
		virtual ~Character(void);
		Character &operator=(Character const &rhs);
};



#endif