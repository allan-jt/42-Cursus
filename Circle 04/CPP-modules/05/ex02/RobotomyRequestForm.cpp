#include "RobotomyRequestForm.hpp"

void	RobotomyRequestForm::execute(Bureaucrat const &executor) const {
	if (!this->isSigned())
		throw NotSignedException();
	if (executor.getGrade() > REXEC)
		throw GradeTooLowException();
	std::cout << "Drrrrrrrrrrrrrrrrr!" << std::endl;
	int randomNum = std::rand() % 2;
	std::cout << this->_target +
		(randomNum ? " is" : " couldn't be") + " robotomized!"
		<< std::endl;
}

std::string	RobotomyRequestForm::getTarget(void) {return this->_target;}

/****************************(CON/DE)STRUCTORS****************************/ 
RobotomyRequestForm::RobotomyRequestForm(void) 
	: Form("UNKNOWN", RSIGN, REXEC), _target("UNKNOWN") {
	std::cout << "Default constructor for RobotomyRequestForm called"
		<< std::endl;
	srand((unsigned int)time(NULL));
}

RobotomyRequestForm::RobotomyRequestForm(std::string target) :
	Form("RobotomyRequest", RSIGN, REXEC), 
	_target(target.empty() ? "UNKNOWN" : target) {
	std::cout << "Type constructor for RobotomyRequestForm called"
		<< std::endl;
	srand((unsigned int)time(NULL));
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const &copy)
	: Form(copy) {
	*this = copy;
	std::cout << "Copy constructor for RobotomyRequestForm called" 
		<< std::endl;
}

RobotomyRequestForm::~RobotomyRequestForm(void) {
	std::cout << "Destructor for RobotomyRequestForm " << this->getName()
		<< " called" << std::endl;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(RobotomyRequestForm const &rhs) {
	if (this != &rhs)
		this->_target = ((RobotomyRequestForm &) rhs).getTarget();
	srand((unsigned int)time(NULL));
	std::cout << "Copy asignment operator for RobotomyRequestForm called"
		<< std::endl;
	return (*this);
}
/*************************************************************************/