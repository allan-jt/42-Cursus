#ifndef POINT_HPP
#define POINT_HPP

#include "Fixed.hpp"

class Point {
	public:
		Point(void);
		Point(float const x, float const y);
		Point(Point const &copy);
		~Point(void);
		Point &operator=(Point const &rhs);

		Fixed getX(void) const;
		Fixed getY(void) const;
	
	private:
		Fixed const _x;
		Fixed const _y;
};

#endif