#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

#define	PB_SIZE		8
#define COL_WIDTH	10

class PhoneBook {
	public:
		PhoneBook(void);
		// user commands
		void	addContact(void);
		void	searchContact(void) const;
		~PhoneBook(void);
	
	private:
		// initializations
		Contact _contact[PB_SIZE];
		int		_curIdx;

		// private function utils
		void	_reorderPB(void);
		void	_getIndex(void) const;
		void	_printColumn(std::string *buffer) const;
		void	_printDetail(int detail) const;
};

#endif