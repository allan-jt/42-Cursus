#include "Form.hpp"

int main(void) {
	Bureaucrat b1("b1", 100);
	Bureaucrat b2("b2", 40);
	Form f1("f1", 90, 80);
	Form f2("f2", 1, 75);

	
	std::cout << "Testing 0" << std::endl;
	std::cout << "b1: " << b1 << std::endl
		<< "b2: " << b2 << std::endl
		<< "f1: " << f1 << std::endl
		<< "f2: " << f2 << std::endl;
	
	std::cout << "Testing 1" << std::endl;
	b1.signForm(f1);

	std::cout << "Testing 2" << std::endl;
	b2.signForm(f1);

	std::cout << "Testing 3" <<std::endl;
	b2.signForm(f2);

	std::cout << "Testing 4" <<std::endl;
	std::cout << "b1: " << b1 << std::endl
		<< "b2: " << b2 << std::endl
		<< "f1: " << f1 << std::endl
		<< "f2: " << f2 << std::endl;
}