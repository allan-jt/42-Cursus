/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/19 14:50:19                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/server/Server.hpp"

/**********************CANONICAL & OTHER CONSTRINGUCTORS**********************/
Server::Server() {}

Server::Server(ConfigServer *&config, fd_set *&allSockets, STRING listen,
	fd_set &allSocks, size_t &highestFd) :
	listen_(listen), host_(listen.substr(0, listen.find(':'))),
	port_(listen.substr(listen.find(':') + 1)), highestFd_(0), 
	managerSockets_(&allSocks), managerHidhestFd_(&highestFd) {

	configs_.push_back(new ConfigServer(*config));
	FD_ZERO(&allSockets_);
	allSockets = &allSockets_;
	storeAddress_();
}

Server::Server(Server const &copy) {*this = copy;}

Server::~Server() {
	freeaddrinfo(address_);
	for (int i = 0; i <= (int) highestFd_; i++)
		if (FD_ISSET(i, &allSockets_))
			clearFd(i);

	size_t numberOfConfigs = configs_.size();
	for (size_t i = 0; i < numberOfConfigs; i++) {
		delete configs_[i];
		configs_[i] = NULL;
	}
}

Server &Server::operator=(Server const &rhs) {
	if (this != &rhs) {
		listen_ = rhs.listen_;
		socket_ = rhs.socket_;
		allSockets_ = rhs.allSockets_;
		highestFd_ = rhs.highestFd_;
		configs_ = rhs.configs_;
		communications_ = rhs.communications_;
		cgiFds_ = rhs.cgiFds_;
		managerSockets_ = rhs.managerSockets_;
		managerHidhestFd_ = rhs.managerHidhestFd_;
	}
	return *this;
}

/**********************************MAIN FUNCTIONS*********************************/
int	Server::setUp() {
	int sockOpt = 1;
	int	tempSocket;

	if ((tempSocket = socket(AF_INET, SOCK_STREAM, DEFAULT)) <= ERROR) {
		std::cerr << "Error: socket failed on " <<  listen_ << std::endl;
		return ERROR;
	}
	socket_ = tempSocket;
	fcntl(socket_, F_SETFL, O_NONBLOCK);
	setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &sockOpt, sizeof(sockOpt));
	addFd(socket_);
	
/*	struct addrinfo *p = address_;
	int a = 0;
	if (!p)
		std::cout << "uo";
	while (p) {
		a++;
		p = p->ai_next;
	}
	std::cout << a <<std::endl;*/

	if (bind(socket_, address_->ai_addr, sizeof(*(address_->ai_addr))) <= ERROR) {
		std::cerr << "Error: binding failed on " << listen_ << std::endl;
		return ERROR;
	}
	if (listen(socket_, LISTEN_BACKLOG) <= ERROR) {
		std::cerr << "Error: listen failed on " << listen_ << std::endl;
		return ERROR;
	}

	return EXIT_SUCCESS;
}

/*************************************SETTERS************************************/
void	Server::storeAddress_() {
	struct addrinfo	hints;
	bzero(&hints, sizeof(struct addrinfo));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(NULL, port_.c_str(), &hints, &address_) != 0) {
		throw std::runtime_error("Error: cannot aquire address!");
	}
}

void	Server::addFd(size_t fd) {
	FD_SET(fd, &allSockets_);
	FD_SET(fd, managerSockets_);
	communications_[fd] = std::make_pair((Request *) NULL, (Response *) NULL);

	if (fd > *managerHidhestFd_)
		*managerHidhestFd_ = fd;
	if (fd > highestFd_)
		highestFd_ = fd;
}

void	Server::clearFd(size_t fd) {
	close(fd);
	removeCommunication(fd);
	clearFdWithNoClose(fd);
}

void	Server::clearFdWithNoClose(size_t fd) {
	FD_CLR(fd, &allSockets_);
	FD_CLR(fd, managerSockets_);
	if (fd == *managerHidhestFd_) {
		for (int i = fd - 1; i >= 0; i--) {
			if (FD_ISSET(i, managerSockets_)) {
				*managerHidhestFd_ = i;
				break;
			}
		}
	}
	if (fd == highestFd_) {
		for (int i = fd - 1; i >= 0; i--) {
			if (FD_ISSET(i, &allSockets_)) {
				highestFd_ = i;
				break;
			}
		}
	}
}

void	Server::setRequest(size_t fd, Request *request) {
	REQ_RESP *communication = getCommunicationAt(fd);

	if (!communication)
		return setCommunication(fd, request, NULL);
	delete communication->REQ;
	communication->REQ = request;
}

void	Server::setResponse(size_t fd, Response *response) {
	REQ_RESP *communication = getCommunicationAt(fd);

	if (!communication)
		return setCommunication(fd, NULL, response);
	delete communication->RES;
	communication->RES = response;
}

void	Server::setCommunication(size_t fd, Request *request, Response *response) {
	REQ_RESP *communication = getCommunicationAt(fd);
	
	if (!communication) {
		communications_[fd] = std::make_pair(request, response);
		return;
	}

	delete communication->REQ;
	delete communication->RES;
	communication->REQ = request;
	communication->RES = response;
}

void	Server::setCGIFd(int fd, Request *request, Response *response) {
	REQ_RESP *cgiFd = getCGIFdAt(fd);

	if (!cgiFd) {
		cgiFds_[fd] = std::make_pair(request, response);
	} else {
		cgiFd->REQ = request;
		cgiFd->RES = response;
	}
	
	FD_SET(fd, &allSockets_);
	FD_SET(fd, managerSockets_);
	if ((size_t)fd > *managerHidhestFd_)
		*managerHidhestFd_ = fd;
	if ((size_t)fd > highestFd_)
		highestFd_ = fd;
}

void	Server::eraseCGIFdAt(int fd) {
	cgiFds_.erase(fd);
	clearFdWithNoClose(fd);
}

void	Server::removeCommunication(size_t fd) {
	REQ_RESP *communication = getCommunicationAt(fd);

	if (!communication)
		return;
	delete communication->REQ;
	delete communication->RES;
	communications_.erase(fd);
}

void	Server::appendConfig(ConfigServer *config) {
	configs_.push_back(config);
}

/*************************************GETTERS************************************/
ConfigServer	*Server::getConfigAt(size_t i) const {return configs_.at(i);}
size_t			Server::getNumberOfConfigs() const {return configs_.size();}
STRING			const &Server::getListen() const {return listen_;}
size_t			const &Server::getSocket() const {return socket_;}
fd_set			const &Server::getAllSockets() const {return allSockets_;}
bool			Server::checkFdSet(size_t fd) {return FD_ISSET(fd, &allSockets_);}
size_t			const &Server::getHighestFd() const {return highestFd_;}

std::vector<ConfigServer *>	const &Server::getAllConfigs() const {
	return configs_;
}
std::map<int, REQ_RESP> *Server::getCommunications() {
	return &communications_;
}

Request	*Server::getRequestAt(int fd) {
	std::map<int, REQ_RESP>::iterator it = communications_.find(fd);
	if (it == communications_.end())
		return NULL;
	return it->second.REQ;
}

Response	*Server::getResponseAt(int fd) {
	std::map<int, REQ_RESP>::iterator it = communications_.find(fd);
	if (it == communications_.end())
		return NULL;
	return it->second.RES;
}

REQ_RESP	*Server::getCommunicationAt(int fd) {
	std::map<int, REQ_RESP>::iterator it = communications_.find(fd);
	if (it == communications_.end())
		return NULL;
	return &(it->second);
}

REQ_RESP	*Server::getCGIFdAt(int fd) {
	std::map<int, REQ_RESP>::iterator it = cgiFds_.find(fd);
	if (it == cgiFds_.end())
		return NULL;
	return &(it->second);
}