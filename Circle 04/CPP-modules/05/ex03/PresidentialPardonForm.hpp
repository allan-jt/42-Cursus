#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "Form.hpp"

#define PSIGN	25
#define	PEXEC	5

class	PresidentialPardonForm : public Form {
	private:
		std::string	_target;
	
	public:
		void		execute(Bureaucrat const &executor) const;
		std::string	getTarget(void);

		// (con/de)structors
		PresidentialPardonForm(void);
		PresidentialPardonForm(std::string target);
		PresidentialPardonForm(PresidentialPardonForm const &copy);
		~PresidentialPardonForm(void);
		PresidentialPardonForm &operator=(PresidentialPardonForm const &rhs);
};

#endif