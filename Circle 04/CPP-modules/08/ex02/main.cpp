#include "MutantStack.hpp"

int main()
{
	MutantStack<int> mstack;
	for (int i = 0; i < 10; i++)
		mstack.push(i);
	
	std::cout << "Test1: end vs top" << std::endl;
	std::cout << "End: " << *(mstack.end() - 1) << std::endl;
	std::cout << "Top: " << mstack.top() << std::endl;

	std::cout << std::endl << "Test2: show all values" << std::endl;
	for (MutantStack<int>::iterator cur = mstack.begin();
		cur != mstack.end(); cur++)
		std::cout << *cur << std::endl;
	
	std::cout << std::endl << "Test3: pop" << std::endl;
	for (int i = 0; i < 10; i++)
		mstack.pop();
	for (MutantStack<int>::iterator cur = mstack.begin();
		cur != mstack.end(); cur++)
		std::cout << *cur << std::endl;

	return 0;
}
