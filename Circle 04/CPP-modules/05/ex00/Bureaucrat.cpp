#include "Bureaucrat.hpp"

/********************************EXCEPTION********************************/ 
const char	*Bureaucrat::GradeTooHighException::what() const throw() {
	return ("Error: Grade too high!\n");
}

const char	*Bureaucrat::GradeTooLowException::what() const throw() {
	return ("Error: Grade too low!\n");
}
/*************************************************************************/


/******************************GETTERS/UTILS******************************/ 
std::string	Bureaucrat::getName(void) const {return (this->_name);}

int	Bureaucrat::getGrade(void) const {return (this->_grade);}

void	Bureaucrat::incrementGrade(void) {
	if (this->_grade == 1)
		throw Bureaucrat::GradeTooHighException();
	this->_grade--;
}

void	Bureaucrat::decrementGrade(void) {
	if (this->_grade == 150)
		throw Bureaucrat::GradeTooLowException();
	this->_grade++;
}
/*************************************************************************/


/****************************(CON/DE)STRUCTORS****************************/ 
Bureaucrat::Bureaucrat(void) : _name("UNKNOWN"), _grade(150) {
	std::cout << "Default constructor for Bureaucrat called" << std::endl;
}

Bureaucrat::Bureaucrat(std::string name, int grade) :
	_name(name), _grade(150) {
	std::cout << "Type constructor for Bureaucrat called" << std::endl;
	if (grade > 150)
		throw Bureaucrat::GradeTooLowException();
	if (grade < 1)
		throw Bureaucrat::GradeTooHighException();
	_grade = grade;
}

Bureaucrat::Bureaucrat(Bureaucrat const &copy) {
	*this = copy;
	std::cout << "Copy constructor for Bureaucrat called" << std::endl;
}

Bureaucrat::~Bureaucrat(void) {
	std::cout << "Destructor for Bureaucrat " << this->_name 
		<< " called" << std::endl;
}

Bureaucrat &Bureaucrat::operator=(Bureaucrat const &rhs) {
	if (this != &rhs) {
		(std::string &) this->_name = ((Bureaucrat &)rhs).getName();
		this->_grade = ((Bureaucrat &)rhs).getGrade();
	}
	std::cout << "Copy asignment operator for Bureaucrat called"
		<< std::endl;
	return (*this);
}
/*************************************************************************/

std::ostream &operator<<(std::ostream &out, Bureaucrat const &rhs) {
	out << rhs.getName() << ", bureaucrat grade " << rhs.getGrade()
		<< "." << std::endl;
	return (out);
}