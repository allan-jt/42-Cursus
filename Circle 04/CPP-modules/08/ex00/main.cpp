#include "easyfind.hpp"

int	getNum(void) {
	static int i;
	return (i = i + 1 == 10 ? 0 : i + 1);
}

int main(void) {
	// Initialize and fill containers
	std::vector<int> numsVector(10);
	std::generate(numsVector.begin(), numsVector.end(), getNum);

	std::deque<int> numsDeque(10);
	std::generate(numsDeque.begin(), numsDeque.end(), getNum);

	std::list<int> numsList(10);
	std::generate(numsList.begin(), numsList.end(), getNum);

	// Testing
	std::cout << "Testing 1: vector works" << std::endl;
	tester(numsVector, 1);

	std::cout << "Testing 2: vector error" << std::endl;
	tester(numsVector, 10);

	std::cout << "Testing 3: deque works" << std::endl;
	tester(numsDeque, 3);

	std::cout << "Testing 4: deque error" << std::endl;
	tester(numsDeque, 10);

	std::cout << "Testing 5: list works" << std::endl;
	tester(numsList, 5);

	std::cout << "Testing 6: list error" << std::endl;
	tester(numsList, 10);
}