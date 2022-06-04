#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed {
	public:
		Fixed(void);
		Fixed(Fixed const &copy);
		~Fixed(void);
		Fixed &operator=(Fixed const &rhs);

		int		getRawBits(void) const;
		void	setRawBits(int const raw);
	
	private:
		int					_fpn;
		static int const	_fracBit;
};

#endif