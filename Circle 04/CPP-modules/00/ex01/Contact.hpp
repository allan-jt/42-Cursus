#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cctype>
#include <cstdlib>

#define	FIRST_NAME	0
#define	LAST_NAME	1
#define	NICKNAME	2
#define	PHONE_NUM	3
#define	DARK_SECRET	4
#define NUM_DETAILS	5

class Contact {
	public:
		Contact(void);
		std::string	getField(int field) const;
		void 		setField(int field, std::string data);
		int			validData(int field, std::string data) const;
		~Contact(void);
	
	private:
		std::string	_details[NUM_DETAILS];
};

#endif