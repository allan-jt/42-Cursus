#include "Dog.hpp"
#include "Cat.hpp"

int main()
{	
	{ // test for shallow capy
		Dog *test = new Dog();
		test->getBrain()->setAllIdeas("I hate cats!");
		std::cout << std::endl;
		const Animal* j = new Dog(*test);
		std::cout << std::endl;
		const Animal* i = new Cat();
		std::cout << std::endl;
		
		delete j;
		std::cout << std::endl;
		delete i;
		std::cout << std::endl;
		std::cout << test->getBrain()->getIdea(99) << std::endl;
		delete test;
	}

	// test for virtual destructor
	// Animal p;
	std::cout << std::endl;
	Animal *a[10];
	for (int i = 0; i < 10; i++) {
		if (i < 5)
			a[i] = new(std::nothrow) Dog();
		else
			a[i] = new(std::nothrow) Cat();
	}
	for (int i = 0; i < 10; i++)
		delete a[i];

	return 0;
}
