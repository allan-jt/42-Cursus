#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "Form.hpp"
#include <cstdlib>

#define RSIGN	72
#define	REXEC	45

class	RobotomyRequestForm : public Form {
	private:
		std::string	_target;
	
	public:
		void		execute(Bureaucrat const &executor) const;
		std::string	getTarget(void);

		// (con/de)structors
		RobotomyRequestForm(void);
		RobotomyRequestForm(std::string target);
		RobotomyRequestForm(RobotomyRequestForm const &copy);
		~RobotomyRequestForm(void);
		RobotomyRequestForm &operator=(RobotomyRequestForm const &rhs);
};

#endif