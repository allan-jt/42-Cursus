#include "Data.hpp"

int	main(void) {
	Data test1("Jack", 25);
	Data test2("Jill", 24);
	Data test3;

	std::cout << "Test1: " << test1.getName() << " " << test1.getAge()
		<< std::endl << "Test2: " << test2.getName() << " " << test2.getAge()
		<< std::endl << "Test3: " << test3.getName() << " " << test3.getAge()
		<< std::endl;

	uintptr_t t1 = serialize(&test1);
	uintptr_t t2 = serialize(&test2);
	uintptr_t t3 = serialize(&test3);

	Data *one = deserialize(t1);
	Data *two = deserialize(t2);
	Data *three = deserialize(t3);

	std::cout << "One: " << one->getName() << " " << one->getAge()
		<< std::endl << "Two: " << two->getName() << " " << two->getAge()
		<< std::endl << "Three: " << three->getName() << " " << three->getAge()
		<< std::endl;;
}