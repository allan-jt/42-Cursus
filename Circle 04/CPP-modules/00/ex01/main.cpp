#include "PhoneBook.hpp"

int	main(void)
{
	PhoneBook	pb;
	std::string	cmd;

	while (true) {
		std::cout << "Enter a valid command: ";
		std::getline(std::cin, cmd);
		if (std::cin.eof())
			exit(0);
		if (cmd.compare("ADD") == 0)
			pb.addContact();
		else if (cmd.compare("SEARCH") == 0)
			pb.searchContact();
		else if (cmd.compare("EXIT") == 0)
			break;
		else if (!cmd.empty())
			std::cout << "Invalid command! ";
	}
	return (0);
}