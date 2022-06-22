#ifndef	DATA_HPP
#define DATA_HPP

#include <iostream>
#include <string>
#include <stdint.h>

class Data {
	private:
		int			_age;
		std::string	_name;

	public:
		// getters
		int			getAge(void) const;
		std::string	getName(void) const;	

		// (con/de)structors
		Data(void);
		Data(std::string name, int age);
		Data(Data const &copy);
		~Data(void);
		Data &operator=(Data const &rhs);
};

uintptr_t	serialize(Data* ptr);
Data		*deserialize(uintptr_t raw);

#endif