#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed {
	public:
		Fixed(void);
		Fixed(Fixed const &copy);
		Fixed(int const literalInt);
		Fixed(float const literalFloat);
		~Fixed(void);
		Fixed &operator=(Fixed const &rhs);


		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		float	toFloat(void) const;
		int		toInt(void)	const;
	
	private:
		int					_fpn;
		static int const	_fracBit;
};

std::ostream &operator<<(std::ostream &out, Fixed const &rhs);

#endif