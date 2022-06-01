#include <iostream>
#include <string>

int main(void) {
	// Initialize
	std::string str = "HI THIS IS BRAIN";
	std::string *stringPTR = &str;
	std::string &stringREF = str;

	// Print address of <str>
	std::cout << "Addr of <str>: " << &str << std::endl
		<< "Addr held by <stringPtr>: " << stringPTR << std::endl
		<< "Addr held by <stringREF>: " << &stringREF << std::endl;
	
	// Print value of <str>
	std::cout << std::endl << "Val of <str>: " << str
		<< std::endl << "Val held by <stringPTR>: " << *stringPTR
		<< std::endl << "Val held by <stringREF>: " << stringREF
		<< std::endl;
}