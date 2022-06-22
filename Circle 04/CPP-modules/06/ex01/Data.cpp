#include "Data.hpp"

int			Data::getAge(void) const {return this->_age;}

std::string	Data::getName(void) const {return this->_name;}

/********************************CANONICAL********************************/ 
Data::Data(void) : _age(0), _name("UNKNOWN") {}

Data::Data(std::string name, int age) : _age(age), _name (name) {}

Data::Data(Data const &copy) {*this = copy;}

Data::~Data(void) {}

Data &Data::operator=(Data const &rhs) {
	if (this != &rhs) {
		this->_age = rhs.getAge();
		this->_name = rhs.getName();
	}
	return *this;
}
/*************************************************************************/ 


/********************************NON-CLASS********************************/
uintptr_t	serialize(Data* ptr) {
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data		*deserialize(uintptr_t raw) {
	return (reinterpret_cast<Data *>(raw));
}
/*************************************************************************/