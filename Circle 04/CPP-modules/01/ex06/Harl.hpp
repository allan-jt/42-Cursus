#ifndef HARL_HPP
#define HARL_HPP

#include <string>
#include <iostream>

#define NUM_OF_FUNC 4

class Harl {
	public:
		Harl(void);
		~Harl(void);

		void	complain(std::string level);
	
	private:
		void	_debug(void) const;
		void	_info(void) const;
		void	_warning(void) const;
		void	_error(void) const;

};

#endif