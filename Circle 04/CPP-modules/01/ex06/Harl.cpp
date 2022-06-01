#include "Harl.hpp"

Harl::Harl(void) {}

void	Harl::complain(std::string level) {
	std::string levels[NUM_OF_FUNC] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	int i = -1;

	while (++i < NUM_OF_FUNC)
		if (levels[i] == level)
			break;
	switch (i) {
		case 0:
			this->_debug();
			std::cout << std::endl;
			//fall-through
		case 1:
			this->_info();
			std::cout << std::endl;
			//fall-through
		case 2:
			this->_warning();
			std::cout << std::endl;
			//fall-through
		case 3:
			this->_error();
			std::cout << std::endl;
			break;
		default:
			std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
			break;
	}
}

void	Harl::_debug(void) const{
	std::cout << "[ DEBUG ]" << std::endl << "I love having extra "
		<< "bacon for my 7XL-double-cheese-triple-pickle-special-ketchup"
		<< " burger." << std::endl << "I really do!" << std::endl;
}

void	Harl::_info(void) const{
	std::cout << "[ INFO ]" << std::endl 
		<< "I cannot believe adding extra bacon costs more money." 
		<< std::endl << "You didn't put enough bacon in my burger!" 
		<< std::endl << "If you did, I wouldn't be asking for more!"
		<< std::endl;
}

void	Harl::_warning(void) const{
	std::cout << "[ WARNING ]" << std::endl
		<< "I think I deserve to have some extra bacon for free."
		<< std::endl << "I've been coming for years whereas you "
		<< " started working here since last month." << std::endl;
}

void	Harl::_error(void) const{
	std::cout << "[ ERROR ]" << std::endl << "This is unacceptable!"
		<< std::endl << "I want to speak to the manager now." << std::endl;
}

Harl::~Harl(void) {}