#include "Base.hpp"

Base::~Base(void) {}

Base	*generate(void) {
	int	num = std::rand() % 3;
	if (num == 0) {
		std::cout << "A generated" << std::endl;
		return new(std::nothrow) A;
	} else if (num == 1) {
		std::cout << "B generated" << std::endl;
		return new(std::nothrow) B;
	}
	std::cout << "C generated" << std::endl;
	return new(std::nothrow) C;
}

void	identify(Base *p) {
	std::cout << "This is " << 
		(dynamic_cast<A *>(p) ? "A" : 
		(dynamic_cast<B *>(p) ? "B" :
		(dynamic_cast<C *>(p) ? "C" : 
		"unknown"))) << std::endl;
}

void	identify(Base &p) {
	std::cout << "This is ";
	try {
		Base test = dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
	} catch (std::exception &bc) {
		try {
			Base test = dynamic_cast<B&>(p);
			std::cout << "B" << std::endl;
		} catch (std::exception &e) {
			try {
				Base test = dynamic_cast<C&>(p);
				std::cout << "C" << std::endl;
			} catch (std::exception &f) {
				std::cout << "unknown" << std::endl;
			}
		}
	}
}