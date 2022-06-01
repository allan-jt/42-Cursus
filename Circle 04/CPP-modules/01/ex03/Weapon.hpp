#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>

class Weapon {
	public: 
		Weapon(std::string type);
		std::string const	&getType(void) const;
		void				setType(std::string newType);
		~Weapon(void);
	
	private:
		std::string	_type;
};

#endif