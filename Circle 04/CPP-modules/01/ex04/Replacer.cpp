#include "Replacer.hpp"

Replacer::Replacer(STR fname, STR s1, STR s2, int &error) {
	// Open files and validate data
	this->_infile.open(fname.c_str());
	if (fname.empty() || s1.empty() || s2.empty())
		error = this->_putError("One or more arguements are empty!");
	else if (!this->_infile.is_open() || !this->_infile.good())
		error = this->_putError(fname + " failed to open!");
	else {
		this->_outfile.open((fname + ".replace").c_str());
		if (!this->_outfile.is_open()) {
			error = this->_putError(fname + ".replace failed to open!");
			return;
		}
		this->_replace(s1, s2);
	}
}

void	Replacer::_replace(STR s1, STR s2) {
	// Convert content from file to string format
	std::stringstream temp;
	temp << this->_infile.rdbuf();
	std::string fileContent = temp.str();

	// Replace every s1 in fileContent with s2
	int	curPos = 0, s1Pos;
	while ((s1Pos = fileContent.find(s1, curPos)) != -1) {
		fileContent.erase(s1Pos, s1.length());
		fileContent.insert(s1Pos, s2);
		curPos = s1Pos + s2.length();
	}
	
	// Copy contents of file_content into outfile
	this->_outfile << fileContent;
}

int	Replacer::_putError(STR msg) const {
	std::cout << "Error: " << msg << std::endl;
	return (1);
}

Replacer::~Replacer(void) {
	if (this->_infile.is_open())
		this->_infile.close();
	if (this->_outfile.is_open())
		this->_outfile.close();
};