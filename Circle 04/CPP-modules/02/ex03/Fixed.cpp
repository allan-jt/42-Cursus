#include "Fixed.hpp"

int const	Fixed::_fracBit = 8;

std::ostream &operator<<(std::ostream &out, Fixed const &rhs) {
	out << rhs.toFloat();
	return (out);
}

/********************************CANONICAL********************************/ 
Fixed::Fixed(void) : _fpn(0) {}

Fixed::Fixed(Fixed const &copy) {*this = copy;}

Fixed::~Fixed(void) {}

Fixed &Fixed::operator=(Fixed const &rhs) {
	this->_fpn = rhs.getRawBits();
	return (*this);
}
/*************************************************************************/ 


/*************************ADDITIONAL CONSTRUCTORS*************************/
Fixed::Fixed(int const literalInt) : _fpn(literalInt << Fixed::_fracBit) {}

Fixed::Fixed(float const literalFloat) :
	_fpn((int)roundf(literalFloat * (1 << Fixed::_fracBit))) {}
/*************************************************************************/


/***************************COMPARISON OPERATORS**************************/
bool Fixed::operator>(Fixed const &rhs) {
	return (this->_fpn > rhs.getRawBits());
}

bool Fixed::operator<(Fixed const &rhs) {
	return (this->_fpn < rhs.getRawBits());
}

bool Fixed::operator>=(Fixed const &rhs) {
	return (this->_fpn >= rhs.getRawBits());
}

bool Fixed::operator<=(Fixed const &rhs) {
	return (this->_fpn <= rhs.getRawBits());
}

bool Fixed::operator==(Fixed const &rhs) {
	return (this->_fpn == rhs.getRawBits());
}

bool Fixed::operator!=(Fixed const &rhs) {
	return (this->_fpn != rhs.getRawBits());
}
/*************************************************************************/


/***************************ARITHMATIC OPERATORS**************************/
Fixed Fixed::operator+(Fixed const &rhs) {
	Fixed ret(this->toFloat() + rhs.toFloat());
	return (ret);
}

Fixed Fixed::operator-(Fixed const &rhs) {
	Fixed ret(this->toFloat() - rhs.toFloat());
	return (ret);
}

Fixed Fixed::operator*(Fixed const &rhs) {
	Fixed ret(this->toFloat() * rhs.toFloat());
	return (ret);
}

Fixed Fixed::operator/(Fixed const &rhs) {
	Fixed ret(this->toFloat() / rhs.toFloat());
	return (ret);
}
/*************************************************************************/


/***************************INCREMENT OPERATORS***************************/
Fixed &Fixed::operator++(void) {
	++this->_fpn;
	return (*this);
}

Fixed &Fixed::operator--(void) {
	--this->_fpn;
	return (*this);
}

Fixed Fixed::operator++(int) {
	Fixed ret = *this;
	this->_fpn++;
	return (ret);
}

Fixed Fixed::operator--(int) {
	Fixed ret = *this;
	this->_fpn--;
	return (ret);
}
/*************************************************************************/


/**********************OTHER PUBLIC MEMBER FUNCTION***********************/
int Fixed::getRawBits(void) const {return (this->_fpn);}

void	Fixed::setRawBits(int const raw) {this->_fpn = raw;}

float	Fixed::toFloat(void) const {
	return (((float)this->_fpn / (float)(1 << Fixed::_fracBit)));
}

int	Fixed::toInt(void) const {return (this->_fpn >> Fixed::_fracBit);}
/*************************************************************************/


/****************************STATIC FUNCTIONS*****************************/
Fixed	&Fixed::min(Fixed &f1, Fixed &f2) {
	if (f1.getRawBits() < f2.getRawBits())
		return (f1);
	return (f2);
}

Fixed const	&Fixed::min(Fixed const &f1, Fixed const &f2) {
	if (f1.getRawBits() < f2.getRawBits())
		return (f1);
	return (f2);
}

Fixed	&Fixed::max(Fixed &f1, Fixed &f2) {
	if (f1.getRawBits() > f2.getRawBits())
		return (f1);
	return (f2);
}

Fixed const	&Fixed::max(Fixed const &f1, Fixed const &f2) {
	if (f1.getRawBits() > f2.getRawBits())
		return (f1);
	return (f2);
}
/*************************************************************************/