#include "Point.hpp"

static float getFixedPointArea(Point const a, Point const b, Point const c) {
	// return cross product of vector ab and ac
	Point vector_ab(((Fixed) b.getX() - a.getX()).toFloat(),
		((Fixed) b.getY() - a.getY()).toFloat());
	Point vector_ac(((Fixed) c.getX() - a.getX()).toFloat(),
		((Fixed) c.getY() - a.getY()).toFloat());
	Fixed ret(((Fixed) vector_ab.getY() * vector_ac.getX()).toFloat()
		- ((Fixed) vector_ac.getY() * vector_ab.getX()).toFloat());	
	return (ret.toFloat());
}

bool bsp(Point const a, Point const b, Point const c, Point const point) {
	//Fixed triangleArea(getFixedPointArea(a, b, c));
	Fixed abpArea(getFixedPointArea(a, b, point));
	Fixed capArea(getFixedPointArea(c, a, point));
	Fixed bcpArea(getFixedPointArea(b, c, point));
	return (((abpArea < 0) && (capArea < 0) && (bcpArea < 0))
			|| ((abpArea > 0) && (capArea > 0) && (bcpArea > 0)));
	
	
	/*
	Fixed diffOfAreas(triangleArea.toFloat()
		- abpArea.toFloat() - acpArea.toFloat() - bcpArea.toFloat());
	return (diffOfAreas.toFloat() == 0);
	*/
}