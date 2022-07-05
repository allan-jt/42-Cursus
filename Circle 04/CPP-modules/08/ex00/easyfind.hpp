#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>

#include <vector>
#include <deque>
#include <list>

template<typename T>
typename T::iterator easyfind(T &container, int num) {
	typename T::iterator numFound = 
		find(container.begin(), container.end(), num);
	if (numFound == container.end())
		throw std::out_of_range
			("Could not find number in container");
	return numFound;
}

template<typename T>
void	tester(T &container, int valToTest) {
	try {
		typename T::iterator num =
			easyfind(container, valToTest);
		std::cout << *num << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << std::endl;
}

#endif