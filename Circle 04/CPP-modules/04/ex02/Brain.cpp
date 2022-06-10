#include "Brain.hpp"

/****************************(CON/DE)STRUCTORS****************************/ 
Brain::Brain(void) {
	std::cout << "Default constructor for Brain called" << std::endl;
}

Brain::Brain(Brain const &copy) {
	std::cout << "Copy constructor for Brain called" << std::endl;
	*this = copy;
}

Brain::~Brain(void) {
	std::cout << "Destructor for Brain called" << std::endl;
}

Brain &Brain::operator=(Brain const &rhs) {
	if (this != &rhs)
		for (int i = 0; i < 100; i++)
			this->ideas[i] = rhs.getIdea(i);
	std::cout << "Copy asignment operator for Brain called" << std::endl;
	return (*this);
}
/*************************************************************************/

std::string	Brain::getIdea(unsigned int i) const {
	return (i < 100 ? this->ideas[i] : "");		
}

void	Brain::setIdea(std::string txt, unsigned int i) {
	if (i < 100) {
		this->ideas[i] = txt;
		return;
	}
	std::cout << "Error: Invalid index!" << std::endl;
}

void	Brain::setAllIdeas(std::string txt) {
	for (int i = 0; i < 100; i++)
		this->ideas[i] = txt;
}