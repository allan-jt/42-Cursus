#include "Harl.hpp"

int	main(int argc, char **argv) {
	if (argc != 2 || std::string(argv[1]).empty()) {
		std::cout << "Error: Invalid args!"
			<< std::endl;
		return (1);
	}
	
	Harl test;
	test.complain(argv[1]);
	return (0);
}