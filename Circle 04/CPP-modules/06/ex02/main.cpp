#include "Base.hpp"

int main(void) {
	std::srand((unsigned int)std::time(NULL));
	Base *test[10];
	
	for (int i = 0; i < 10; i++)
		test[i] = generate();
	for (int i = 0; i < 10; i++)
		(i < 5 ? identify(test[i]) : identify(*test[i]));
	for (int i = 0; i < 10; i++)
		delete test[i];
}