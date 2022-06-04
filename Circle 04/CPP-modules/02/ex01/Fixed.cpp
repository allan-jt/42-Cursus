#include "Fixed.hpp"

int const	Fixed::_fracBit = 8;

/********************************CANONICAL********************************/ 
Fixed::Fixed(void) : _fpn(0) {
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(Fixed const &copy) {
	std::cout << "Copy constructor called" << std::endl;
	*this = copy;
}

Fixed::~Fixed(void) {
	std::cout << "Destructor called" << std::endl;
}

Fixed &Fixed::operator=(Fixed const &rhs) {
	std::cout << "Copy assignment operator called" << std::endl;
	this->_fpn = rhs.getRawBits();
	return (*this);
}
/*************************************************************************/ 

/*************************ADDITIONAL CONSTRUCTORS*************************/
Fixed::Fixed(int const literalInt) : _fpn(literalInt << Fixed::_fracBit) {
	std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(float const literalFloat) :
	_fpn((int)roundf(literalFloat * (1 << Fixed::_fracBit))) {
	std::cout << "Float constructor called" << std::endl;
}
/*************************************************************************/

/**********************OTHER PUBLIC MEMBER FUNCTION***********************/
int Fixed::getRawBits(void) const {
	std::cout << "getRawBits member function called" << std::endl;
	return (this->_fpn);
}

void	Fixed::setRawBits(int const raw) {
	std::cout << "setRawBits member function called" << std::endl;
	this->_fpn = raw;
}

float	Fixed::toFloat(void) const {
	return (((float)this->_fpn / (float)(1 << Fixed::_fracBit)));
}

int	Fixed::toInt(void) const {
	return (this->_fpn >> Fixed::_fracBit);
}
/*************************************************************************/

std::ostream &operator<<(std::ostream &out, Fixed const &rhs) {
	out << rhs.toFloat();
	return (out);
}