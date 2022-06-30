#ifndef ARRAY_HPP
#define	ARRAY_HPP

#include <iostream>
#include <stdexcept>
#include <new>

typedef struct data
{
	int     a;
	char    b;
	float   c;
}               complexData;

template<typename T>
class Array {
	private:
		int	_size;
		T 	*_array;

	public:
		// getters
		int	size(void) const {return this->_size;}
		T &operator[](int i) {
			if (i >= this->_size || i < 0)
				throw std::out_of_range("Out of range!");
			return this->_array[i];
		}

		// (con/de)structors
		Array(void) : _size(0), _array(NULL) {}
		
		Array(unsigned int n) : _size(n),
			_array(n > 0 ? new(std::nothrow) T[n] : NULL) {}
		
		Array(Array const &copy) : _size(0), _array(NULL) {*this = copy;}
		
		Array &operator=(Array const &rhs) {
			if (this != &rhs) {
				delete[] this->_array;
				this->_size = rhs.size();
				this->_array = this->_size > 0 ?
					new(std::nothrow) T[this->_size] : NULL;
				for (int i = 0; i < this->_size; i++)
					this->_array[i] = ((Array &) rhs)[i];
			}
			return *this;
		}

		~Array(void) {delete[] _array;}
};

#endif