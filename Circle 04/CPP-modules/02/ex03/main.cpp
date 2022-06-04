#include "Point.hpp"

bool bsp(Point const a, Point const b, Point const c, Point const point);

int main( void ) {
	// https://www.math10.com/en/geometry/geogebra/geogebra.html
	
	// Triangle for testing (use above link for visualization)
	Point a(-4.88, 4.47);
	Point b(4.28, -8.49);
	Point c(7.16, 5.75);
	
	// Points for testing
	Point d(2.5, 2.5);		// in (within border)
	Point e(-1.72, 0);		// in (at border)
	Point f(5.34, 5.67);	// out (close to border)
	Point g(4324, 434);		// out (far from border)

	// Output tests
	std::cout << (bsp(a, b, c, d)) << std::endl;
	std::cout << (bsp(a, b, c, e)) << std::endl;
	std::cout << (bsp(a, b, c, f)) << std::endl;
	std::cout << (bsp(a, b, c, g)) << std::endl;


	return 0;
}