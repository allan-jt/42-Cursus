#ifndef REPLACER_HPP
#define REPLACER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#define STR std::string

class Replacer {
	public:
		Replacer(STR fname, STR s1, STR s2, int &error);
		~Replacer(void);
	
	private:
		std::fstream	_infile;
		std::ofstream	_outfile;

		void	_replace(STR s1, STR s2);
		int		_putError(STR msg) const;
};

#endif