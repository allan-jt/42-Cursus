#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>

template<typename T>
void	iter(T *array, int length, void (*function)(T &t)) {
	for (int i = 0; i < length; i++)
		function(array[i]);
}

#endif