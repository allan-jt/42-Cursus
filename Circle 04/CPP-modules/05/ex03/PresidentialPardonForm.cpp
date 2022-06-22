#include "PresidentialPardonForm.hpp"

void	PresidentialPardonForm::execute(Bureaucrat const &executor) const {
	if (!this->isSigned())
		throw NotSignedException();
	if (executor.getGrade() > PEXEC)
		throw GradeTooLowException();
	std::cout << this->_target + " has been pardoned by Zaphod Beeblebrox"
		<< std::endl;
}

std::string	PresidentialPardonForm::getTarget(void) {return this->_target;}

/****************************(CON/DE)STRUCTORS****************************/ 
PresidentialPardonForm::PresidentialPardonForm(void) 
	: Form("UNKNOWN", PSIGN, PEXEC), _target("UNKNOWN") {
	std::cout << "Default constructor for PresidentialPardonForm called"
		<< std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(std::string target) :
	Form("PresidentialPardon", PSIGN, PEXEC), 
	_target(target.empty() ? "UNKNOWN" : target) {
	std::cout << "Type constructor for PresidentialPardonForm called"
		<< std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const &copy)
	: Form(copy) {
	*this = copy;
	std::cout << "Copy constructor for PresidentialPardonForm called" 
		<< std::endl;
}

PresidentialPardonForm::~PresidentialPardonForm(void) {
	std::cout << "Destructor for PresidentialPardonForm " << this->getName()
		<< " called" << std::endl;
}

PresidentialPardonForm &PresidentialPardonForm::operator=(PresidentialPardonForm const &rhs) {
	if (this != &rhs)
		this->_target = ((PresidentialPardonForm &) rhs).getTarget();
	
	std::cout << "Copy asignment operator for PresidentialPardonForm called"
		<< std::endl;
	return (*this);
}
/*************************************************************************/