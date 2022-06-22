#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>

#define	MAX_GRADE 1
#define MIN_GRADE 150

class	Form;

class	Bureaucrat {
	private:
		std::string const	_name;
		int					_grade;

	public:
		// Exception handling
		class GradeTooHighException : public std::exception {
			public: virtual const char	*what() const throw();
		};
		class GradeTooLowException : public std::exception {
			public: virtual const char	*what() const throw();
		};
		
		// Getters/utils
		std::string	getName(void) const;
		int			getGrade(void) const;
		void		incrementGrade(void);
		void		decrementGrade(void);
		void		signForm(Form &f) const;
		
		// (con/de)structors
		Bureaucrat(void);
		Bureaucrat(std::string name, int grade);
		Bureaucrat(Bureaucrat const &copy);
		~Bureaucrat(void);
		Bureaucrat &operator=(Bureaucrat const &rhs);
};

std::ostream &operator<<(std::ostream &out, Bureaucrat const &rhs);

#endif