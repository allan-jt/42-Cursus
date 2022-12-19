/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/19 14:50:32                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/server/ServerManager.hpp"

/************************************GENERAL***********************************/
void	ServerManager::createServer_(ConfigServer *&conf, STRING listen) {
	if (servers_.find(listen) != servers_.end())
		servers_[listen]->appendConfig(new ConfigServer(*conf));
	else if (!(servers_[listen] = new(std::nothrow)
		Server(conf, sockets_[listen], listen, allSockets_, highestFd_)))
		throw std::runtime_error("Error: memory failure");
}

void	ServerManager::checkClientTimeOut_() {
	for (std::map<STRING, Server *>::iterator serv = servers_.begin();
		serv != servers_.end(); serv++) {

		std::map<int, REQ_RESP> *communications = serv->second->getCommunications();
		for (std::map<int, REQ_RESP>::iterator com = communications->begin();
			com != communications->end(); com++) {
			Request *request = com->second.REQ;
			if (!request || !request->checkTimeOut())
				continue;
			FD_CLR(request->getClientFd(), &allSockets_);
			FD_SET(request->getClientFd(), &writeFds_);
		}
	}
}

bool	ServerManager::clientNeedsToClose_(int writeStatus, Request *request) {
	return (writeStatus <= ERROR || request->getRequestStatus() <= READ_ERROR
		|| request->getHeaderAt(CONNECTION) == CLOSE);
}

void	handleSignals(int sig) {
	(void) sig;
	g_running = false;
}

/*************************************READ*************************************/
void	ServerManager::processReadFds_(fd_set &readFds, fd_set &writeFds) {
	size_t	maxFd = highestFd_;

	for (size_t i = 0; i <= maxFd; i++) {
		if (!FD_ISSET(i, &readFds))
			continue;

		Server	*server = getServerAtAnySocket(i);
		server->getSocket() == i ? acceptClient_(server, i)
			: recieveClient_(server, i);
		FD_CLR(i, &writeFds);
	}
}

void	ServerManager::acceptClient_(Server *server, int socketFd) {
	int	clientFd = accept(socketFd, NULL, NULL);

	if (clientFd <= ERROR) {
		std::cerr << "Error: accept failed at listen "
			<< server->getListen() << std::endl;
		return;
	}
	fcntl(clientFd, F_SETFL, O_NONBLOCK);
	server->addFd(clientFd);
	server->setRequest(clientFd, new Request(clientFd));
}

void	ServerManager::recieveClient_(Server *server, int clientFd) {
	REQ_RESP *cgiFd = server->getCGIFdAt(clientFd);
	if (cgiFd && cgiFd->RES && cgiFd->RES->getCGIReadFd() == clientFd) {
		cgiFd->RES->setCGIReadFdStatus(true);
		return server->eraseCGIFdAt(clientFd);
	}

	Request *request = server->getRequestAt(clientFd);
	if (!request || request->getRequestStatus() != INCOMPLETE)
		server->setRequest(clientFd, new Request(clientFd)); 

	int requestStatus = server->getRequestAt(clientFd)->recieve();
	if (requestStatus == FINISHED) {
		server->clearFd(clientFd);
		FD_CLR(clientFd, &writeFds_);
	} else if (requestStatus != INCOMPLETE)
		FD_SET(clientFd, &writeFds_);
}

/************************************WRITE************************************/
void	ServerManager::processWriteFds_(fd_set &writeFds, fd_set &readFds) {
	size_t	maxFd = highestFd_;

	for (size_t i = 0; i <= maxFd; i++) {
		if (!FD_ISSET(i, &writeFds))
			continue;
		Server	*server = getServerAtAnySocket(i);
		if (!server || server->getSocket() == i)
			continue;
		
		REQ_RESP *cgiFd = server->getCGIFdAt(i);
		if (cgiFd && cgiFd->RES && cgiFd->RES->getCGIWriteFd() == (int) i) {
			cgiFd->RES->setCGIWriteFdStatus(true);
			FD_CLR(i, &writeFds_);
			FD_CLR(i, &readFds);
			server->eraseCGIFdAt(i);
			continue;
		}

		REQ_RESP *com = server->getCommunicationAt(i);
		if (!com || !com->REQ || com->REQ->getRequestStatus() == INCOMPLETE)
			continue;
		handleResponse_(server, com->REQ, com->RES, i);
		FD_CLR(i, &readFds);
	}
}

void	ServerManager::handleResponse_(Server *server, Request *request,
		Response *response, int clientFd) {
	request->startTime();
	response == NULL ? handleNewResponse_(server, request, clientFd)
					: handleOldResponse_(server, request, response, clientFd);
}

void	ServerManager::handleOldResponse_(Server *server, Request *request,
		Response *response, int clientFd) {
	int	bytesLeftToSend;
	
	if (!checkCGIisReady(server, response, request) 
		|| (bytesLeftToSend = response->send(clientFd)) > EMPTY) {
		return;
	} else if (clientNeedsToClose_(bytesLeftToSend, request)) {
		server->clearFd(clientFd);
	} else {
		server->setResponse(clientFd, NULL);
		request->startTime();
	}
	FD_CLR(clientFd, &writeFds_);
}

void	ServerManager::handleNewResponse_(Server *server, Request *request,
		int clientFd) {
	ConfigServer	*config = getConfig_(server, request);
	Response		*response = new Response(*request, *config);
	int				bytesLeftToSend;
	
	if (!checkCGIisReady(server, response, request) 
		|| (bytesLeftToSend = response->send(clientFd)) > EMPTY) {
		return server->setResponse(clientFd, response);
	} else if (clientNeedsToClose_(bytesLeftToSend, request)) {
		server->clearFd(clientFd);
	} else
		request->startTime();

	delete response;
	FD_CLR(clientFd, &writeFds_);
}

bool	ServerManager::checkCGIisReady(Server *serv, Response *res, Request *req) {
	bool	sendReady = res->getCGIWriteFdStatus();
	bool	readReady = res->getCGIReadFdStatus();
	int		sendFd = res->getCGIWriteFd();
	int		readFd = res->getCGIReadFd();

	if (sendReady && readReady)
		return true;
	if (!sendReady && !FD_ISSET(sendFd, &writeFds_)) {
		serv->setCGIFd(sendFd, req, res);
		FD_SET(sendFd, &writeFds_);
	}
	if (!readReady && !FD_ISSET(readFd, &allSockets_))
		serv->setCGIFd(readFd, req, res);
	return false;
}

ConfigServer	*ServerManager::getConfig_(Server *server, Request *request) {
	int	numberOfConfigs = server->getNumberOfConfigs();

	for (int i = 0; i < numberOfConfigs; i++) {
		ConfigServer *tempConfig = server->getConfigAt(i);
		if (tempConfig->getServerName() == request->getHostName())
			return tempConfig;
	}
	return server->getConfigAt(DEFAULT);
}
