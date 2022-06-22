#include "Bureaucrat.hpp"

int main(void) {
	Bureaucrat test1;
	Bureaucrat test2("test2", 1);
	Bureaucrat test3(test2);
	Bureaucrat test4("test4", 150);


	std::cout << std::endl << "Testing 0" << std::endl;
	try {
		test1 = Bureaucrat("test5", 0);
	} catch(std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	
	std::cout << "Testing 1" << std::endl;
	try {
		test2.decrementGrade();
	} catch (Bureaucrat::GradeTooLowException &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "Testing 2" << std::endl;
	try {
		test3.incrementGrade();
	} catch (Bureaucrat::GradeTooHighException &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "Testing 3" <<std::endl;
	try {
		test4.decrementGrade();
	} catch (Bureaucrat::GradeTooLowException &e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "Testing 4" <<std::endl;
	std::cout << "test1: " << test1 << std::endl
		<< "test2: " << test2 << std::endl
		<< "test3: " << test3 << std::endl
		<< "test4: " << test4 << std::endl;
}