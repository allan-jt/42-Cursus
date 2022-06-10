#include "Ice.hpp"
#include "Cure.hpp"
#include "MateriaSource.hpp"
#include "Character.hpp"

int main()
{
	std::cout << "1\n";
	IMateriaSource* src = new MateriaSource();
	
	std::cout << "2\n";
	src->learnMateria(new Ice());
	src->learnMateria(new Cure()); 
	
	std::cout << "2.5\n";

	std::cout << "3\n";
	ICharacter* me = new Character("me");
	AMateria* tmp;

	std::cout << "4\n";
	tmp = src->createMateria("ice");
	me->equip(tmp);

	std::cout << "5\n";
	tmp = src->createMateria("cure");
	me->equip(tmp);

	std::cout << "6\n";
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);
	tmp = src->createMateria("ice"); // will not get stored
	me->equip(tmp);						// will not get stored
	delete(tmp);


	std::cout << "7\n";
	ICharacter* bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);
	me->use(3, *bob);
	me->use(4, *bob);
	
	std::cout << "8\n";
	delete bob;
	std::cout << "9\n";
	delete me;
	std::cout << "10\n";
	delete src;


	return 0;
}
