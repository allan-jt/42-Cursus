/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/19 14:48:32                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef SERVER_MANAGER_HPP
#define SERVER_MANAGER_HPP

#include "Server.hpp"

class	ServerManager {
	private:
		Config						mainConfig_;
		std::map<STRING, Server *>	servers_;	// <listen, server>
		std::map<STRING, fd_set *>	sockets_;	// <listen, fd_set>
		fd_set						allSockets_;
		fd_set						writeFds_;
		size_t						highestFd_;

	//	General utils
		void	createServer_(ConfigServer *&conf, STRING listen);
		void	checkClientTimeOut_();
		bool	clientNeedsToClose_(int writeStatus, Request *);

	//	Read utils
		void	processReadFds_(fd_set &readFds, fd_set &writeFds);
		void	acceptClient_(Server *server, int socketFd);
		void	recieveClient_(Server *server, int clientFd);

	//	Write utils
		void			processWriteFds_(fd_set &writeFds, fd_set &readFds);
		void			handleResponse_(Server *, Request *, Response *, int clientFd);
		void			handleOldResponse_(Server *, Request *, Response *, int clientFd);
		void			handleNewResponse_(Server *, Request *, int clientFd);
		bool			checkCGIisReady(Server *, Response *, Request *);
		ConfigServer	*getConfig_(Server *server, Request *request);

	public:
	//	Main function
		void	setUpAllServers();
		void	runAllServers();

	//	Getters
		Config						const &getMainConfig() const;
		std::map<STRING, Server *>	const &getAllServers() const;
		std::map<STRING, fd_set *>	const &getAllSockets() const;
		fd_set						const &getMainFdSet() const;
		size_t						const &getHighestFd() const;

		Server	*getServerAtListen(STRING listen) const;
		fd_set	*getFdSetAtListen(STRING listen) const;
		Server	*getServerAtMainSocket(size_t socketFd);
		Server	*getServerAtAnySocket(size_t socketFd);

	//	Canonical & other constructors
		ServerManager();
		ServerManager(Config &config);
		ServerManager(ServerManager const &copy);
		~ServerManager();
		ServerManager &operator=(ServerManager const &rhs);
};

extern bool	g_running;
void		handleSignals(int sig);

#endif
