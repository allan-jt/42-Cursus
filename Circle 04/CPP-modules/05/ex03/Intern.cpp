#include "Intern.hpp"

Form *Intern::makeForm(std::string name, std::string target) {
	std::string forms[3] = {"shrubbery", "robotomy", "presidential"};
	funcPointer listOfForms[3] = 
		{&Intern::getShrubbery, &Intern::getRobotomy, &Intern::getPresidential}; 
	
	try {
		int i = -1; 
		while (++i < 3)
			if (name.find(forms[i]) != std::string::npos)
				return (this->*listOfForms[i])(target);
		throw Intern::FormErrorException();
	} catch (Intern::FormErrorException &e) {
		std::cout << e.what() << std::endl;
		return (NULL);
	}
}

char const *Intern::FormErrorException::what() const throw() {
	return ("Could not create form!");
}

Form	*Intern::getShrubbery(std::string targ) const {
	return (new(std::nothrow) ShrubberyCreationForm(targ));
}

Form	*Intern::getRobotomy(std::string targ) const {
	return (new(std::nothrow) RobotomyRequestForm(targ));
}

Form	*Intern::getPresidential(std::string targ) const {
	return (new(std::nothrow) PresidentialPardonForm(targ));
}
/****************************(CON/DE)STRUCTORS****************************/ 
Intern::Intern(void) {
	std::cout << "Default constructor for Intern called" << std::endl;
}

Intern::Intern(Intern const &copy) {
	*this = copy;
	std::cout << "Copy constructor for Intern called" << std::endl;
}

Intern::~Intern(void) {
	std::cout << "Destructor for Intern called" << std::endl;
}

Intern &Intern::operator=(Intern const &rhs) {
	if (this != &rhs)
		*this = rhs;
	std::cout << "Copy asignment operator for Intern called"
		<< std::endl;
	return (*this);
}
/*************************************************************************/