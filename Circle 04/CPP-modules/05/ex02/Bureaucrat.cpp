#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"

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
	if (this->_grade == MAX_GRADE)
		throw Bureaucrat::GradeTooHighException();
	this->_grade--;
}

void	Bureaucrat::decrementGrade(void) {
	if (this->_grade == MIN_GRADE)
		throw Bureaucrat::GradeTooLowException();
	this->_grade++;
}

void	Bureaucrat::signForm(Form const &form) const {
	try {
		((Form &)form).beSigned((Bureaucrat &) *this);
		std::cout << this->_name + " signed " + form.getName()
			<< std::endl;
	} catch (Form::AlreadySignedException &e) {
		std::cout << this->_name + " couldn't sign " + form.getName()
			+ " because the form is already signed" << std::endl;
	} catch (Form::GradeTooLowException &e) {
		std::cout << this->_name + " couldn't sign " + form.getName()
			+ " because the grade is too low" << std::endl;
	}
}

void	Bureaucrat::executeForm(Form const &form) const {
	try {
		((Form &)form).execute((Bureaucrat &) *this);
		std::cout << this->_name + " executed " + form.getName()
			<< std::endl;
	} catch (Form::NotSignedException &e) {
		std::cout << this->_name + " couldn't execute " + form.getName()
			+ " because the form is not signed" << std::endl;
	} catch (Form::GradeTooLowException &e) {
		std::cout << this->_name + " couldn't execute " + form.getName()
			+ " because the grade is too low" << std::endl;
	} catch (ShrubberyCreationForm::FileErrorException &e) {
		std::cout << this->_name + " couldn't execute " + form.getName()
			+ " because of file couldn't open" << std::endl;
	}
}
/*************************************************************************/


/****************************(CON/DE)STRUCTORS****************************/ 
Bureaucrat::Bureaucrat(void) : _name("UNKNOWN"), _grade(MIN_GRADE) {
	std::cout << "Default constructor for Bureaucrat called" << std::endl;
}

Bureaucrat::Bureaucrat(std::string name, int grade) :
	_name(name), _grade(MIN_GRADE) {
	std::cout << "Type constructor for Bureaucrat called" << std::endl;
	if (grade > MIN_GRADE)
		throw Bureaucrat::GradeTooLowException();
	if (grade < MAX_GRADE)
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