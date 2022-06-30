#include "iter.hpp"

template<typename T>
void	addOne(T &num) {num += 1;}

template<typename T>
void	print(T num) {
	std::cout << num << std::endl;
}

int main() {
	int		num1[5] = {1, 2, 3, 4, 5};
	char	char2[4] = {'a', 'b', 'c', 'd'};

	std::cout << "Testing 1" << std::endl;
	iter(num1, 5, addOne);
	iter(num1, 5, print);

	std::cout << std::endl << "Testing 2" << std::endl;
	iter(char2, 4, addOne);
	iter(char2, 4, print);

	return (0);
}