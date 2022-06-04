#include "Point.hpp"

/********************************CANONICAL********************************/ 
Point::Point(void) : _x(0), _y(0) {}

Point::Point(Point const &copy) {*this = copy;}

Point::~Point(void) {}

Point &Point::operator=(Point const &rhs) {
	(Fixed &) this->_x = rhs.getX(); // Don't understane why
	(Fixed &) this->_y = rhs.getY(); // references are needed.
	return (*this);
}
/*************************************************************************/


/*************************ADDITIONAL CONSTRUCTORS*************************/
Point::Point(float const x, float const y) : _x(x), _y(y) {}
/*************************************************************************/


/*********************************GETTERS*********************************/
Fixed Point::getX(void) const {return (this->_x);}

Fixed Point::getY(void) const {return (this->_y);}
/*************************************************************************/