#include "Harl.hpp"

Harl::Harl(void) {}

void	Harl::complain(std::string level) {
	// Init function and level arrays to match by index
	void	(Harl::*lvl[NUM_OF_FUNC]) (void) const = 
		{&Harl::_debug, &Harl::_info, &Harl::_warning, &Harl::_error};
	std::string levels[NUM_OF_FUNC] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	
	// Execute the matching function
	for (int i = 0; i < NUM_OF_FUNC; i++)
		if (levels[i] == level)
			return (this->*(lvl[i]))();
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