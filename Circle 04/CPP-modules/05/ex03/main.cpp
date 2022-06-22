#include "Intern.hpp"

int main(void) {
	Bureaucrat b1("b1", 150);
	Bureaucrat b2("b2", 40);
	Bureaucrat b3("b3", 1);
	
	Intern	anon;
	Form	*f1 = anon.makeForm("shrubbery", "f1");
	Form	*f2= anon.makeForm("robotomy", "f2");
	Form	*f3 = anon.makeForm("robotomy", "f3");
	Form	*f4 = anon.makeForm("gandu", "f4");

	std::cout << std::endl << "Testing 1" << std::endl;
	std::cout << "b1: " << b1 << std::endl
			  << "b2: " << b2 << std::endl
			  << "b3: " << b3 << std::endl
			  << "f1: " << *f1 << std::endl 
			  << "f2: " << *f2 << std::endl
			  << "f3: " << *f3 << std::endl
			  << "f4: " << f4 << std::endl;

	std::cout << std::endl << "Testing 2" << std::endl;
	b1.signForm(*f1);
	b2.signForm(*f2);
	b3.signForm(*f3);

	std::cout << std::endl << "Testing 3" <<std::endl;
	b1.executeForm(*f3);
	b3.executeForm(*f1);

	std::cout << std::endl << "Testing 3.5" <<std::endl;
	for (int i = 0; i < 10; i++)
		b2.executeForm(*f2);


	std::cout << std::endl << "Testing 4" <<std::endl;
	b3.signForm(*f2);
	b3.signForm(*f1);
	b2.executeForm(*f1);
	b3.executeForm(*f3);
	
	
	std::cout << std::endl << "Testing 5" <<std::endl;
	std::cout << "b1: " << b1 << std::endl
			  << "b2: " << b2 << std::endl
			  << "b3: " << b3 << std::endl
			  << "f1: " << *f1 << std::endl 
			  << "f2: " << *f2 << std::endl
			  << "f3: " << *f3 << std::endl
			  << "f4: " << f4 << std::endl;
	
	delete f1;
	delete f2;
	delete f3;
	delete f4;
}