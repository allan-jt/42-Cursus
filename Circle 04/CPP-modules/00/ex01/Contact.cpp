#include "Contact.hpp"

Contact::Contact(void) {}

std::string	Contact::getField(int field) const {
	if (field >= FIRST_NAME && field < NUM_DETAILS)
		return (this->_details[field]);
	return (NULL);
}

void	Contact::setField(int field, std::string data) {
	if (field < FIRST_NAME || field >= NUM_DETAILS)
		return;
	int	start = 0;
	int	end = data.length() - 1;
	
	// Remove leading and trailing whitespaces
	while (std::isspace(data[start]))
		start++;
	while (std::isspace(data[end]))
		end--;
	
	// Check whether substring is valid before adding data
	if (data == "" || end < start) {
		this->_details[field].clear();
		return;
	}
	int whitespace = 0;
	for (int i = start; i <= end; i++) {
		whitespace += std::isspace(data[i]) ? 1 : -whitespace;
		if (whitespace < 2)
			this->_details[field] += data[i];
	}
}

int		Contact::validData(int field, std::string data) const {
	int	found = 0;
	
	for (int i = 0; data[i]; i++) {
		if (field < PHONE_NUM) {
			// Validate all names
			if (!found)
				found = std::isalpha(data[i]);
			if (!std::isalpha(data[i]) && !std::isspace(data[i]))
				return (0);
		} else if (field  == PHONE_NUM) {
			// Validate phone number
			if (!found)
				found = std::isdigit(data[i]);
			if (!std::isdigit(data[i]) && !std::isspace(data[i]))
				return (0);	
		} else if (field  > PHONE_NUM) {
			// Valide dark secret :O
			if (!found)
				found = std::isalnum(data[i]);
			if (!std::isalnum(data[i]) && !std::isspace(data[i]))
				return (0);
		}
	}
	return (found);
}

Contact::~Contact(void) {}