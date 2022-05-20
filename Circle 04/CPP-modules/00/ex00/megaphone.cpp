#include <iostream>
#include <cctype>

int	main(int argc, char **argv) {
	int	text_found = 0;
	
	// Output if argument is given
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] && !text_found)
			text_found = 1;
		std::string str(argv[i]);
		for (std::string::iterator cur = str.begin();
			cur != str.end(); cur++)
			std::cout << (char) std::toupper(*cur);
	}
	
	// Output if no or empty arguments are given
	if (argc == 1 || !text_found)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";

	// End both output types with new line
	std::cout << std::endl;
	return (0);
}