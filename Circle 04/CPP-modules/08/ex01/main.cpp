#include "Span.hpp"

int main(void) {
	Span test1(100000);
	std::cout << "Testing 1" << std::endl;
	for (int i = 0; i < 100001; i++) {
		try {
			test1.addNumber(i);
		} catch (std::exception &e) {
			std::cout << e.what() << " i val: " << i << std::endl;
		}
	}
	
	std::cout << std::endl << "Testing 2" << std::endl;
	Span test2(100000);
	try {
		test2.addRangeOfIterators(test1.getVec().begin(), test1.getVec().end());
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	
	(test1.getVec())[0] = 999;
	for (int i = 0; i < 10; i++)
		std::cout << test2.getVec()[i] << " " << test1.getVec()[i]
			<< std::endl;

	std::cout << std::endl << "Testing 3" << std::endl;
	Span test3(5);
	test3.addNumber(6);
	test3.addNumber(3);
	test3.addNumber(17);
	test3.addNumber(9);
	test3.addNumber(11);
	std::cout << "test3 longest span: " << test3.longestSpan() << std::endl
			<< "test3 shortest span: " << test3.shortestSpan() << std::endl
			<< "test2 longest span: " << test2.longestSpan() << std::endl
			<< "test2 shortest span: " << test2.shortestSpan() << std::endl;
}