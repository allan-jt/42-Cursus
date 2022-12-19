/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/19 14:50:26                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/server/ServerManager.hpp"

bool	g_running = true;

/************************CANONICAL & OTHER CONSTRINGUCTORS************************/
ServerManager::ServerManager() {}

ServerManager::ServerManager(Config &config) : mainConfig_(config), highestFd_(0) {
	int	numberOfServers = config.getServers().size();

	FD_ZERO(&allSockets_);
	FD_ZERO(&writeFds_);

	for (int i = 0; i < numberOfServers; i++) {
		std::stringstream 	strPort;
		ConfigServer		*tempConfig = config.getServers()[i];
		STRING				tempHost = tempConfig->getHost();
		std::vector<int>	ports = tempConfig->getPort();

		if (tempHost.empty())
			tempHost = DEFAULT_IP;
		for (size_t i = 0; i < ports.size(); i++) {
			strPort << ports[i];
			createServer_(tempConfig, tempHost + ":" + strPort.str());
			strPort.str(STRING());
		}

		if (ports.size() != 0)
			continue;
		strPort << DEFAULT_PORT;
		createServer_(tempConfig, tempHost + ":" + strPort.str());
	}
}

ServerManager::ServerManager(ServerManager const &copy) {*this = copy;}

ServerManager::~ServerManager() {
	std::vector<ConfigServer *> confs = mainConfig_.getServers();

	for (size_t i = 0; i < confs.size(); i++)
		delete confs[i];
	for (std::map<STRING, Server *>::iterator it = servers_.begin();
		it != servers_.end(); it++)
		delete it->second;
}

ServerManager &ServerManager::operator=(ServerManager const &rhs) {
	if (this != &rhs) {
		mainConfig_ = rhs.mainConfig_;
		servers_ = rhs.servers_;
		sockets_ = rhs.sockets_;
		allSockets_ = rhs.allSockets_;
		writeFds_ = rhs.writeFds_;
		highestFd_ = rhs.highestFd_;
	}

	return *this;
}
/**********************************MAIN FUNCTIONS*********************************/
void	ServerManager::setUpAllServers() {
	for (std::map<STRING, Server *>::iterator it = servers_.begin();
		 it != servers_.end(); it++) {
		if (it->second->setUp() == ERROR)
			throw std::runtime_error("Shutting down because of failed set up!");
	}
}

void	ServerManager::runAllServers() {
	struct timeval	time;

	while (g_running) {
		checkClientTimeOut_();
		fd_set	readFds = allSockets_;
		fd_set	writeFds = writeFds_;

		time.tv_sec = DEFAULT;
		time.tv_usec = DEFAULT;
		if (select(highestFd_ + 1, &readFds, &writeFds, NULL, &time) <= ERROR) {
			if (!g_running)
				break;
			throw std::runtime_error("Error: select() failure");
		}

		processWriteFds_(writeFds, readFds);
		processReadFds_(readFds, writeFds);
	}
}

/*************************************GETTERS*************************************/
Config	const &ServerManager::getMainConfig() const {return mainConfig_;}
fd_set	const &ServerManager::getMainFdSet() const {return allSockets_;}
size_t	const &ServerManager::getHighestFd() const {return highestFd_;}

std::map<STRING, Server *>	const &ServerManager::getAllServers() const {
	return servers_;
}

std::map<STRING, fd_set *>	const &ServerManager::getAllSockets() const {
	return sockets_;
}

Server	*ServerManager::getServerAtListen(STRING listen) const {
	std::map<STRING, Server *>::const_iterator server = servers_.find(listen);
	
	if (server != servers_.end())
		return server->second;
	return NULL;
}

fd_set	*ServerManager::getFdSetAtListen(STRING listen) const {
	std::map<STRING, fd_set *>::const_iterator fdset = sockets_.find(listen);
	
	if (fdset != sockets_.end())
		return fdset->second;
	return NULL;
}

Server	*ServerManager::getServerAtMainSocket(size_t socketFd) {
	for (std::map<STRING, Server *>::iterator it = servers_.begin();
		 it != servers_.end(); it++) {
		if (it->second->getSocket() == socketFd)
			return it->second;
	}
	return NULL;
}

Server	*ServerManager::getServerAtAnySocket(size_t socketFd) {
	for (std::map<STRING, fd_set *>::iterator it = sockets_.begin();
		 it != sockets_.end(); it++) {
		if (FD_ISSET(socketFd, it->second))
			return servers_.at(it->first);
	}
	return NULL;
}