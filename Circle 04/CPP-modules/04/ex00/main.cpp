#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"

int main()
{
	const Animal* meta = new Animal();
	std::cout << std::endl;
	const Animal* j = new Dog();
	std::cout << std::endl;
	const Animal* i = new Cat();
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound(); //will output the cat sound!
	j->makeSound();
	meta->makeSound();

	std::cout << std::endl;
	delete meta;
	std::cout << std::endl;
	delete j;
	std::cout << std::endl;
	delete i;
	std::cout << std::endl;

	const WrongCat *test1 = new WrongCat();
	const WrongAnimal *test2 = new WrongCat();

	std::cout << std::endl;
	test1->makeSound();
	test2->makeSound();
	std::cout << std::endl;

	delete test1;
	std::cout << std::endl;
	delete test2;
	std::cout << std::endl;

	return 0;
}
