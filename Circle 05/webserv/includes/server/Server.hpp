/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/19 14:48:26                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "../config/config.hpp"
#include "../utils/SocketManager.hpp"
#include <utility>

#define ERROR			-1
#define LISTEN_BACKLOG	1000
#define REQ_RESP		std::pair<Request *, Response*>
#define REQ				first
#define	RES				second

class	Server {
	private:
		STRING						listen_;
		STRING						host_;
		STRING						port_;
		size_t						socket_;
		struct addrinfo				*address_;
		fd_set						allSockets_;
		size_t						highestFd_;
		std::vector<ConfigServer *>	configs_;
		std::map<int, REQ_RESP>		communications_;
		std::map<int, REQ_RESP>		cgiFds_;		
		fd_set						*managerSockets_;
		size_t						*managerHidhestFd_;

		void	storeAddress_();

	public:
		int	setUp();

	//	Getters
		ConfigServer	*getConfigAt(size_t i) const;
		size_t			getNumberOfConfigs() const;
		STRING			const &getListen() const;
		size_t			const &getSocket() const;
		fd_set			const &getAllSockets() const;
		bool			checkFdSet(size_t fd);
		size_t			const &getHighestFd() const;
		Request			*getRequestAt(int fd);
		Response		*getResponseAt(int fd);
		REQ_RESP		*getCommunicationAt(int fd);
		REQ_RESP		*getCGIFdAt(int fd);

		std::vector<ConfigServer *>	const &getAllConfigs() const;
		std::map<int, REQ_RESP>		*getCommunications();

	//	Setters
		void	setRequest(size_t fd, Request *request);
		void	setResponse(size_t fd, Response *response);
		void	setCommunication(size_t fd, Request *request, Response *response);
		void	setCGIFd(int fd, Request *request, Response *response);
		void	eraseCGIFdAt(int fd);
		void	removeCommunication(size_t fd);
		void	appendConfig(ConfigServer *config);
		void	addFd(size_t fd);
		void	clearFd(size_t fd);
		void	clearFdWithNoClose(size_t fd);

	//	Canonical & other constructors
		Server();
		Server(ConfigServer *&config, fd_set *&allSockets, STRING listen,
			fd_set &allSocks, size_t &highestFd);
		Server(Server const &copy);
		~Server();
		Server &operator=(Server const &rhs);
};

#endif
