#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <vector>
#include <numeric>

class Span {
	private:
		std::vector<int>	ints;
		Span(void);

	public:
		void	addRangeOfIterators(std::vector<int>::iterator first, 
									std::vector<int>::iterator end);
		void				addNumber(int N);
		unsigned int		shortestSpan(void) const;
		unsigned int		longestSpan(void) const;
		std::vector<int>	&getVec(void) const;

		Span(unsigned int N);
		Span(Span const &copy);
		~Span(void);
		Span &operator=(Span const &rhs);

};

#endif