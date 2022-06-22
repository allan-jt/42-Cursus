#include "TypeCast.hpp"

int	main(int argc, char **argv) {
	std::string val;
	if (argc != 2 || (val = 
		static_cast<std::string>(argv[1])).empty()) {
		std::cout << "Invalid arguments!" << std::endl;
		return 1;
	}
	
	TypeCast letsConvert;
	letsConvert.convert(val);
	return (0);
}