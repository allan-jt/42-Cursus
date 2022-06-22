#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "Form.hpp"
#include <fstream>

#define SSIGN	145
#define	SEXEC	137

class	ShrubberyCreationForm : public Form {
	private:
		std::string	_target;
	
	public:
		class FileErrorException : public std::exception {
			public: virtual const char	*what() const throw();
		};
		
		void		execute(Bureaucrat const &executor) const;
		std::string	getTarget(void);

		// (con/de)structors
		ShrubberyCreationForm(void);
		ShrubberyCreationForm(std::string target);
		ShrubberyCreationForm(ShrubberyCreationForm const &copy);
		~ShrubberyCreationForm(void);
		ShrubberyCreationForm &operator=(ShrubberyCreationForm const &rhs);
};

#endif