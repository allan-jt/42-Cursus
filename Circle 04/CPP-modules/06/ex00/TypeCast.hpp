#ifndef	TYPECAST_HPP
#define TYPECAST_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>

#define TYPES	5
#define INVAL	0
#define CHAR	1
#define INT		2
#define FLOAT	3
#define DOUBLE	4

class TypeCast {
	private:
		char	_ch;
		int		_in;
		float	_fl;
		double	_do;
		int		_invalidSign(std::string val, int i);
		int		_invalidPeriod(std::string val, int i, int periodCount);

	public:
		// getters
		char	getChar(void) const;
		int		getInt(void) const;
		float	getFloat(void) const;
		double	getDouble(void) const;
		
		// setters
		void	setChar(std::string val);
		void	setInt(std::string val);
		void	setFloat(std::string val);
		void	setDouble(std::string val);

		// others
		void	invalidInput(std::string val);
		void	printValues(std::string c, std::string i, 
							std::string f, std::string d) const;
		void	convert(std::string val);

		// (con/de)structors
		TypeCast(void);
		TypeCast(TypeCast const &copy);
		~TypeCast(void);
		TypeCast &operator=(TypeCast const &rhs);

		typedef void (TypeCast::*funcPointer)(std::string val);

};

#endif