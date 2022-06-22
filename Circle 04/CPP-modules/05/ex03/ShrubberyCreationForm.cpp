#include "ShrubberyCreationForm.hpp"

char const *ShrubberyCreationForm::FileErrorException::what() const throw() {
	return ("File error!");
}

void	ShrubberyCreationForm::execute(Bureaucrat const &executor) const {
	if (!this->isSigned())
		throw NotSignedException();
	if (executor.getGrade() > SEXEC)
		throw GradeTooLowException();
	std::ofstream file((this->_target + "_shrubbery").c_str());
	if (!file.is_open() || !file.good()) {
		file.close();
		throw FileErrorException();
	}
	file << std::string("         _-_			\n" 
						"	   /~~   ~~\\		\n" 
						"   /~~         ~~\\	\n" 
						"  {               }	\n" 
						"  \\  _-     -_  /		\n" 
						"	 ~   \\ //  ~		\n" 
						"	 _- - | | _- _		\n" 
						"	 _ -  | |   -_		\n"
						"	     // \\			\n");
	file.close();
}

std::string	ShrubberyCreationForm::getTarget(void) {return this->_target;}

/****************************(CON/DE)STRUCTORS****************************/ 
ShrubberyCreationForm::ShrubberyCreationForm(void) 
	: Form("UNKNOWN", SSIGN, SEXEC), _target("UNKNOWN") {
	std::cout << "Default constructor for ShrubberyCreationForm called"
		<< std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) :
	Form("ShrubberyCreation", SSIGN, SEXEC), 
	_target(target.empty() ? "UNKNOWN" : target) {
	std::cout << "Type constructor for ShrubberyCreationForm called"
		<< std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &copy)
	: Form(copy) {
	*this = copy;
	std::cout << "Copy constructor for ShrubberyCreationForm called" 
		<< std::endl;
}

ShrubberyCreationForm::~ShrubberyCreationForm(void) {
	std::cout << "Destructor for ShrubberyCreationForm " << this->getName()
		<< " called" << std::endl;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(ShrubberyCreationForm const &rhs) {
	if (this != &rhs)
		this->_target = ((ShrubberyCreationForm &) rhs).getTarget();
	
	std::cout << "Copy asignment operator for ShrubberyCreationForm called"
		<< std::endl;
	return (*this);
}
/*************************************************************************/