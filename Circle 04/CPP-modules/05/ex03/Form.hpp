#ifndef FORM_HPP
#define FORM_HPP

#include "Bureaucrat.hpp"

class	Form {
	private:
		std::string const	_name;
		bool				_signed;
		int const			_gradeToSign;
		int const			_gradeToExecute;

	public:
		// Exception handling
		class GradeTooHighException : public std::exception {
			public: virtual const char	*what() const throw();
		};
		class GradeTooLowException : public std::exception {
			public: virtual const char	*what() const throw();
		};
		class NotSignedException : public std::exception {
			public: virtual const char	*what() const throw();
		};
		class AlreadySignedException : public std::exception {
			public: virtual const char	*what() const throw();
		};

		// Getters/utils
		std::string		getName(void) const;
		bool			isSigned(void) const;
		int				getGradeToSign(void) const;
		int				getGradeToExecute(void) const;
		void			beSigned(Bureaucrat &b);
		virtual void	execute(Bureaucrat const &executor) const = 0;

		// (con/de)structors
		Form(void);
		Form(std::string name, int signGrade, int execGrade);
		Form(Form const &copy);
		virtual ~Form(void);
		Form &operator=(Form const &rhs);
};

std::ostream &operator<<(std::ostream &out, Form const &rhs);

#endif