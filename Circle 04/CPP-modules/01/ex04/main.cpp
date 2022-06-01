#include "Replacer.hpp"

int	main(int argc, char **argv) {
	int error_status = 0;
	
	if (argc != 4) {
		std::cout << "Error: Invalid number of arguements!"
			<< std::endl;
		error_status = 1;
	} else
		Replacer(argv[1], argv[2], argv[3], error_status);
	return (error_status);
}