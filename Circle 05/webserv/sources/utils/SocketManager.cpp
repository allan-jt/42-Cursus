/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/07/01 15:34:32                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/utils/SocketManager.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

SocketManager::SocketManager() :	_domain(AF_INET), _type(SOCK_STREAM), 
									_protocol(0), _ipAddress(DEFAULT_IP), 
									_port(DEFAULT_PORT), _socketFd(0), 
									_readValue(0) { setAddress();
}

SocketManager::SocketManager(std::string ipAddress, int port,
							int domain, int type, int protocol) 
		: _domain(domain), _type(type), _protocol(protocol),
		_ipAddress(ipAddress), _port(port), _socketFd(0), _readValue(0) 
	{setAddress();}

SocketManager::SocketManager( const SocketManager & src ) {
	*this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

SocketManager::~SocketManager() {}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

SocketManager &				SocketManager::operator=( SocketManager const & rhs )
{
	if ( this != &rhs )
	{
		_ipAddress = rhs._ipAddress;
		_domain = rhs._domain;
		_type = rhs._type;
		_protocol = rhs._protocol;
		_port = rhs._port;
		_socketFd = rhs._socketFd;
		_readValue = rhs._readValue;
		_address = rhs._address;
	}
	return *this;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

int 	SocketManager::checkIfValid(int num, std::string str, bool imediatTerminate, size_t period) {
	if (num >= 0)
		return 1;
  else {
    if (imediatTerminate)
	    std::cerr << RED << str << RESET << "\033[1A" << std::endl;
    else {
      if (getTimer().getCurTime() > period) {
        std::cerr << "\r\033[1A\033[0K" << RED << str << RESET << std::endl;
        return -1;
      }
      else {
        loading(1);
        return 0;
      }
    }
  }
	return -1;
}

void	SocketManager::loading(size_t num) {
	for (size_t i = 0; i < num; i++) {
    std::cout << "\r\033[1A\033[0KWaiting    [ - ]" << std::endl;
    usleep(150000);
    std::cout << "\r\033[1A\033[0KWaiting.   [ \\ ]" << std::endl;
    usleep(150000);
    std::cout << "\r\033[1A\033[0KWaiting..  [ | ]" << std::endl;
    usleep(150000);
    std::cout << "\r\033[1A\033[0KWaiting... [ / ]" << std::endl;
    usleep(150000);
  }
}


/*
** --------------------------------- Getters ---------------------------------
*/

std::string const &			SocketManager::getIpAddress() const {
	return _ipAddress;
}

int const &							SocketManager::getDomain() const {
	return _domain;
}

int const &							SocketManager::getType() const {
	return _type;
}

int const &							SocketManager::getProtocol() const {
	return _protocol;
}

int const &							SocketManager::getPort() const {
	return _port;
}

int const &							SocketManager::getSocketFd() const {
	return _socketFd;
}

long const &						SocketManager::getReadValue() const {
	return _readValue;
}

struct sockaddr_in &		SocketManager::getAddress() {
	return _address;
}

char * 			 						SocketManager::getBuffer() {
	return _buffer;
}

Timer &                 SocketManager::getTimer() {
  return _timer;  
}


/*
** --------------------------------- Setters ---------------------------------
*/

void		SocketManager::setAddress() {
	memset(&_address, DEFAULT, sizeof(_address));
	_address.sin_family = _domain;
	_address.sin_addr.s_addr = inet_addr(_ipAddress.c_str());
	_address.sin_port = htons(_port);
}

void		SocketManager::setIpAddress(std::string ipAddress) {
	_ipAddress = ipAddress;
}

void		SocketManager::setDomain(int domain) {
	_domain = domain;
}

void		SocketManager::setType(int type) {
	_type = type;
}

void		SocketManager::setProtocol(int protocol) {
	_protocol = protocol;
}

void		SocketManager::setPort(int port) {
	_port = port;
}

void		SocketManager::setSocketFd(int socket) {
	_socketFd = socket;
}

void		SocketManager::setReadValue(long readValue) {
	_readValue = readValue;
}

void		SocketManager::setSinFamily(int domain) {
	_address.sin_family = domain;
}

void		SocketManager::setSinAddress(int Address) {
	_address.sin_addr.s_addr = Address;
}

void		SocketManager::setSinPort(int port) {
	_address.sin_port = htons(port);
}

void		SocketManager::setBuffer(char const * buffer) {
  size_t i;
  for (i = 0; buffer[i]; i++) {
	  _buffer[i] = buffer[i];
  }
  _buffer[i] = '\0';
}


/* ************************************************************************** */