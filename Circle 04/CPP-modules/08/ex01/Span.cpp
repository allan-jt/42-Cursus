#include "Span.hpp"

/********************************CANONICAL********************************/
Span::Span(void) {}

Span::Span(unsigned int N) {ints.reserve(N);}

Span::Span(Span const &copy) {*this = copy;}

Span::~Span(void) {}

Span	&Span::operator=(Span const &rhs) {
	if (this != &rhs) {
		ints.clear();
		ints.reserve(rhs.ints.capacity());
		ints = rhs.ints;
	}
	return *this;
}
/*************************************************************************/

void	Span::addRangeOfIterators(std::vector<int>::iterator first, 
									std::vector<int>::iterator end) {
	if (end - first + this->ints.size() > this->ints.capacity())
		throw std::out_of_range("Span's capacity cannot handle this!");
	this->ints.insert(this->ints.end(), first, end);
}

void	Span::addNumber(int N) {
	if (ints.size() == ints.capacity())
		throw std::out_of_range("Span capacity reached!");
	ints.push_back(N);
}

unsigned int	Span::shortestSpan(void) const {
	if (ints.size() < 2)
		throw std::length_error("Span has less than 2 elements!");
	
	std::vector<int> copy(this->ints);
	std::sort(copy.begin(), copy.end());
	
	std::vector<int> ranges(this->ints.size());
	std::adjacent_difference(copy.begin(), copy.end(), ranges.begin());
	return *min_element(ranges.begin() + 1, ranges.end());
}

unsigned int	Span::longestSpan(void) const {
	if (ints.size() < 2)
		throw std::length_error("Span has less than 2 elements!");
	return *max_element(ints.begin(), ints.end()) - 
		*min_element(ints.begin(), ints.end());
}

std::vector<int>	&Span::getVec(void) const {return (std::vector<int>	&)ints;}