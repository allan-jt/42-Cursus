#ifndef INTERN_HPP
#define INTERN_HPP

#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

class	Intern {	
	private:
		Form	*getShrubbery(std::string targ) const;
		Form	*getRobotomy(std::string targ) const;
		Form	*getPresidential(std::string targ) const;
	
	public:
		Form *makeForm(std::string name, std::string target);
		class FormErrorException : public std::exception {
			public: virtual const char	*what() const throw();
		};

		// (con/de)structors
		Intern(void);
		Intern(Intern const &copy);
		~Intern(void);
		Intern &operator=(Intern const &rhs);
		typedef  Form *(Intern::*funcPointer)(std::string targ)const;
};

std::ostream &operator<<(std::ostream &out, Intern const &rhs);

#endif