#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>
#include <string>
#include <new>

class Brain {
	private:
		std::string ideas[100];
	
	public:
		std::string getIdea(unsigned int i) const;
		void	setIdea(std::string txt, unsigned int i);
		void	setAllIdeas(std::string txt);
	
		// (con/de)structors
		Brain(void);
		Brain(Brain const &copy);
		~Brain(void);
		Brain &operator=(Brain const &rhs);
};

#endif