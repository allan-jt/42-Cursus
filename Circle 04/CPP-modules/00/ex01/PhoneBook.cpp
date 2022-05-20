#include "PhoneBook.hpp"

PhoneBook::PhoneBook(void) : _curIdx(0) {}

/********************************* COMMANDS **********************************/
void	PhoneBook::addContact(void) {
	std::string	input[NUM_DETAILS];
	int 		i = 0;

	std::cout << std::endl;
	// Get user to input contact details
	while (i < NUM_DETAILS) {
		std::cout << "Enter ";
		this->_printDetail(i);
		std::getline(std::cin, input[i]);
		// Ensure basic validity of input
		if (std::cin.eof())
			exit(0);
		if (!this->_contact[this->_curIdx].validData(i, input[i])) {
			std::cout << "Invalid input! ";
			continue;
		}
		i++;
	}
	// Populate the contact class with details
	this->_reorderPB();
	for (int j = 0; j < NUM_DETAILS; j++)
		this->_contact[this->_curIdx].setField(j, input[j]);
	this->_curIdx++;
	std::cout << std::endl;
}

void	PhoneBook::searchContact(void) const {
	std::string buffer[3] = {"First Name", "Last Name", "Nickname"};
	
	// Create header of contact table
	std::cout << std::endl << std::string(COL_WIDTH * 4 + 5, '-') << std::endl
		<< "|" << std::setw(COL_WIDTH) << "Index" << std::right << "|";
	this->_printColumn(buffer);
	
	// Enter individual contacts
	for (int i = 0; i < this->_curIdx; i++) {
		// Ensure output is within column width (i.e. 10 chars)
		for (int j = 0; j < 3; j++) {
			buffer[j] = this->_contact[i].getField(j).substr(0, COL_WIDTH);
			if (this->_contact[i].getField(j).length() > COL_WIDTH)
				buffer[j][COL_WIDTH - 1] = '.';
		}
		// Output results
		std::cout << "|" << std::setw(COL_WIDTH) << i << std::right << "|";
		this->_printColumn(buffer);	
	}
	this->_getIndex();
}
/*****************************************************************************/

/********************************* UTILS *************************************/
void	PhoneBook::_reorderPB(void) {
	if (this->_curIdx < PB_SIZE)
		return;
	
	// If size exceeds PB_SIZE (8), shift everything up
	for (int i = 0; i < PB_SIZE - 1; i++)
		this->_contact[i] = this->_contact[i+1];
	for (int i = 0; i < NUM_DETAILS; i++)
		this->_contact[PB_SIZE - 1].setField(i, "");
	this->_curIdx = PB_SIZE - 1; // i.e. 7
}

void	PhoneBook::_getIndex(void) const {
	std::cout << std::endl;
	if (this->_curIdx == 0)
		return;
	int	index;

	// Get valid index
	std::cout << "Enter contact index for details: ";
	if (!(std::cin >> index) || index >= this->_curIdx) {
		if (std::cin.eof())
			exit(0);
		std::cin.clear();
		std::cout << "Invalid index!" << std::endl;
		std::cin.ignore(1000, '\n');
		return;
	}
	// Print contact using index
	for (int detail = 0; detail < NUM_DETAILS; detail++) {
		std::cout << std::setw(16);
		this->_printDetail(detail);
		std::cout << this->_contact[index].getField(detail) << std::endl;
	}
	std::cout << std::endl;
	std::cin.ignore(1000, '\n');
}

void	PhoneBook::_printColumn(std::string *buffer) const {
	std::cout << std::setw(COL_WIDTH) << buffer[0] << std::right << "|"
		<< std::setw(COL_WIDTH) << buffer[1] << std::right << "|"
		<< std::setw(COL_WIDTH) << buffer[2] << std::right << "|"
		<< std::endl << std::string(COL_WIDTH * 4 + 5, '-') << std::endl;	
}

void	PhoneBook::_printDetail(int detail) const {
	if (detail == FIRST_NAME)
		std::cout << "First Name: ";
	else if (detail == LAST_NAME)
		std::cout << "Last Name: ";
	else if (detail == NICKNAME)
		std::cout << "Nickname: ";
	else if (detail == PHONE_NUM)
		std::cout << "Phone Number: ";
	else if (detail == DARK_SECRET)
		std::cout << "Darkest Secret: ";
}
/*****************************************************************************/

PhoneBook::~PhoneBook(void) {
	std::cout << std::endl << "Phonebook destroyed :(" << std::endl;
}