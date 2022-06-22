#include "TypeCast.hpp"

void	TypeCast::convert(std::string val) {
	int		type[TYPES] = {INVAL, CHAR, INT, FLOAT, DOUBLE};
	funcPointer types[TYPES] = {&TypeCast::invalidInput, &TypeCast::setChar,
		&TypeCast::setInt, &TypeCast::setFloat, &TypeCast::setDouble};
	
	int	period = 0;
	if (val[val.length() - 1] != 'f')
		type[FLOAT] = 0;
	for (int i = 0; val[i]; i++) {
		period += (val[i] == '.');
		if (type[CHAR] && (i > 0 || std::isdigit(val[i])))
			type[CHAR] = 0;
		if (type[INT] && (!std::isdigit(val[i])
			&& this->_invalidSign(val, i)))
			type[INT] = 0;
		if (type[FLOAT] && val[i+1] &&
			(!std::isdigit(val[i]) && this->_invalidPeriod(val, i, period)
			&& this->_invalidSign(val, i)))
			type[FLOAT] = 0;
		if (type[DOUBLE] && (!std::isdigit(val[i]) &&
			this->_invalidPeriod(val, i, period) && 
			this->_invalidSign(val, i)))
			type[DOUBLE] = 0;
		if (!type[CHAR] && !type[INT] && !type[FLOAT] && !type[DOUBLE])
			break;
	}
	if (period == 0)
		type[DOUBLE] = 0;
	(this->*types[type[CHAR] + type[INT] + type[FLOAT] + type[DOUBLE]])(val);
}

int	TypeCast::_invalidSign(std::string val, int i) {
	if ((val[i] == '+' || val[i] == '-') &&
		(i == 0 && val[i+1])) 
		return 0;
	return 1;
}

int	TypeCast::_invalidPeriod(std::string val, int i, int periodCount) {
	if (val[i] == '.' && (i != 0 && val[i+1] && periodCount < 2))
		return 0;
	return 1;
}

void	TypeCast::printValues(std::string c, std::string i,
							  std::string f, std::string d) const {
	std::cout << "char: ";
	if (c.empty() && std::isprint(this->_ch))
		std::cout << "'" << this->_ch << "'" << std::endl;
	else
		std::cout << (!c.empty() ? c : "Non displayable") << std::endl;
	std::cout << "int: ";
	if (i.empty())
		std::cout << this->_in << std::endl;
	else
		std::cout << i << std::endl;
	std::cout << "float: ";
	if (f.empty())
		std::cout << this->_fl << (static_cast<int>(this->_fl) == this->_fl ?
			".0f" : "f") << std::endl;
	else
		std::cout << f << std::endl;
	std::cout << "double: ";
	if (d.empty())
		std::cout << this->_do << (static_cast<int>(this->_fl) == this->_fl ?
			".0" : "") << std::endl;
	else
		std::cout << d << std::endl;	
}

/*********************************GETTERS*********************************/ 
char	TypeCast::getChar(void) const {return this->_ch;}

int		TypeCast::getInt(void) const {return this->_in;}

float	TypeCast::getFloat(void) const {return this->_fl;}

double	TypeCast::getDouble(void) const {return this->_do;}
/*************************************************************************/


/*********************************SETTERS*********************************/ 
void	TypeCast::invalidInput(std::string val) {
	if (val == "-inff" || val == "+inff" || val == "nanf")
		return this->setFloat(val);
	if (val == "-inf" || val == "+inf" || val == "nan")
		return this->setDouble(val);
	std::cout << val + " is an invalid input!" << std::endl;
	std::exit(1);
}

void	TypeCast::setChar(std::string val) {
	this->_ch = val[0];
	this->_in = static_cast<int>(this->_ch);
	this->_fl = static_cast<float>(this->_ch);
	this->_do = static_cast<double>(this->_ch);
	printValues("", "", "", "");
}

void	TypeCast::setInt(std::string val) {
	std::string charOut = "", intOut = "";
	std::stringstream valInput(val);

	if (!(valInput >> this->_in))
		intOut = "impossible";
	this->_ch = static_cast<char>(this->_in);
	if (this->_in < 0 || this->_in > 127)
		charOut = "impossible";
	this->_fl = static_cast<float>(this->_in);
	this->_do = static_cast<double>(this->_in);
	printValues(charOut, intOut, "", "");
}

void	TypeCast::setFloat(std::string val) {
	std::string charOut = "", intOut = "", floatOut = "", doubleOut = "";
	this->_fl = static_cast<float>(std::atof(val.c_str()));

	if (val == "nanf" || val == "+inff" || val == "-inff")
		floatOut = val;
	else if (std::isinf(this->_fl))
		floatOut = val[0] == '-' ? "-inff" : "+inff";
	else if (std::isnan(this->_fl))
		floatOut = "nanf";
	this->_ch = static_cast<char>(this->_fl);
	this->_in = static_cast<int>(this->_fl);
	this->_do = static_cast<double>(this->_fl);
	if (floatOut == "nanf" || floatOut == "+inff" || floatOut == "-inff")
		charOut = "impossible", intOut = "impossible";
	printValues(charOut, intOut, floatOut, doubleOut);
}

void	TypeCast::setDouble(std::string val) {
	std::string charOut = "", intOut = "", floatOut = "", doubleOut = "";
	this->_do = static_cast<double>(std::atof(val.c_str()));

	if (val == "nan" || val == "+inf" || val == "-inf")
		doubleOut = val;
	else if (std::isinf(this->_do))
		doubleOut = val[0] == '-' ? "-inf" : "+inf";
	else if (std::isnan(this->_do))
		doubleOut = "nanf";
	this->_ch = static_cast<char>(this->_do);
	this->_in = static_cast<int>(this->_do);
	this->_fl = static_cast<float>(this->_do);
	if (std::isinf(this->_fl) || std::isnan(this->_fl))
		charOut = "impossible", intOut = "impossible";
	printValues(charOut, intOut, floatOut, doubleOut);
}

/*************************************************************************/


/********************************CANONICAL********************************/ 
TypeCast::TypeCast(void) : _ch(0), _in(0), _fl(0), _do(0) {}

TypeCast::TypeCast(TypeCast const &copy) {*this = copy;}

TypeCast::~TypeCast(void) {}

TypeCast &TypeCast::operator=(TypeCast const &rhs) {
	if (this != &rhs) {
		this->_ch = rhs.getChar();
		this->_in = rhs.getInt();
		this->_fl = rhs.getFloat();
		this->_do = rhs.getDouble();
	}
	return *this;
}
/*************************************************************************/ 