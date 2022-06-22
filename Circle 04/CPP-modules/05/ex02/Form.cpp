#include "Form.hpp"

/********************************EXCEPTION********************************/ 
const char	*Form::GradeTooHighException::what() const throw() {
	return ("Error: Grade too high!\n");
}

const char	*Form::GradeTooLowException::what() const throw() {
	return ("Error: Grade too low!\n");
}

const char	*Form::NotSignedException::what() const throw() {
	return ("Error: Form not signed!");
}

const char	*Form::AlreadySignedException::what() const throw() {
	return ("Error: Form already signed!");
}
/*************************************************************************/


/******************************GETTERS/UTILS******************************/ 
std::string	Form::getName(void) const {return this->_name;}

bool	Form::isSigned(void) const {return this->_signed;}

int	Form::getGradeToSign(void) const {return this->_gradeToSign;}

int	Form::getGradeToExecute(void) const {return this->_gradeToExecute;}

void	Form::beSigned(Bureaucrat &b) {
	if (this->_signed)
		throw Form::AlreadySignedException();
	if (b.getGrade() > this->_gradeToSign)
		throw Form::GradeTooLowException();
	this->_signed = true;
}
/*************************************************************************/


/****************************(CON/DE)STRUCTORS****************************/ 
Form::Form(void) : _name("UNKNOWN"), _signed(false),
	_gradeToSign(MIN_GRADE), _gradeToExecute(MIN_GRADE) {
	std::cout << "Default constructor for Form called" << std::endl;
}

Form::Form(std::string name, int signGrade, int execGrade) 
	: _name(name.empty() ? "UNKNOWN" : name), _signed(false),
		_gradeToSign(signGrade), _gradeToExecute(execGrade) {
	std::cout << "Type constructor for Form called" << std::endl;
	if (signGrade > MIN_GRADE || execGrade > MIN_GRADE)
		throw Form::GradeTooLowException();
	if (signGrade < MAX_GRADE || execGrade < MAX_GRADE)
		throw Form::GradeTooHighException();
}

Form::Form(Form const &copy) :
	_gradeToSign(MIN_GRADE), _gradeToExecute(MIN_GRADE) {
	*this = copy;
	std::cout << "Copy constructor for Form called" << std::endl;
}

Form::~Form(void) {
	std::cout << "Destructor for Form " << this->_name 
		<< " called" << std::endl;
}

Form &Form::operator=(Form const &rhs) {
	if (this != &rhs) {
		(std::string &) this->_name = ((Form &)rhs).getName();
		this->_signed = ((Form &)rhs).isSigned();
		(int &) this->_gradeToSign = ((Form &)rhs).getGradeToSign();
		(int &) this->_gradeToExecute = ((Form &)rhs).getGradeToExecute();
	}
	std::cout << "Copy asignment operator for Form called"
		<< std::endl;
	return (*this);
}
/*************************************************************************/


std::ostream &operator<<(std::ostream &out, Form const &rhs) {
	out << "Form name: " << rhs.getName() << std::endl
		<< "Sign status: " << rhs.isSigned() << std::endl
		<< "Grade to sign: " << rhs.getGradeToSign() << std::endl
		<< "Grade to execute: " << rhs.getGradeToExecute() << std::endl;
	return (out);
}