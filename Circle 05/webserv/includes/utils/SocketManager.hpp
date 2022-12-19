/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/07/01 15:35:17                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef SOCKETMANAGER_HPP
# define SOCKETMANAGER_HPP

# include "Timer.hpp"
# include "../response/Response.hpp"

class SocketManager {
  protected:
    // main attributes for socket creation
    std::string           _listen;
    int 				          _domain;
    int					          _type;
    int 					        _protocol;
    std::string		        _ipAddress;
    int						        _port;

    // needed info for connection
    int										_socketFd;
    long									_readValue;
    struct sockaddr_in		_address;

    // buffers for received and senet messeges
    char	                _buffer[30000];
    Timer                 _timer;

  public:

    SocketManager();
    SocketManager(std::string ipAddress = DEFAULT_IP, int port = DEFAULT_PORT,
                  int domain = AF_INET, int type = SOCK_STREAM, int protocol = 0);
    SocketManager( SocketManager const & src );
    virtual ~SocketManager();

    SocketManager &		operator=( SocketManager const & rhs );

    std::string const &										getIpAddress() const;
    int const &														getDomain() const;
    int const &														getType() const;
    int const &														getProtocol() const;
    int const &														getPort() const;
    int const &														getSocketFd() const;
    long const &													getReadValue() const;
    struct sockaddr_in &									getAddress();
    char *																getBuffer();
    Timer &                               getTimer();
    
    void                                  setAddress();
    void																	setIpAddress(std::string ipAddress);
    void																	setDomain(int domain);
    void																	setType(int type);
    void																	setProtocol(int protocol);
    void																	setPort(int port);
    void																	setSocketFd(int sock);
    void																	setReadValue(long readValue);
    void																	setBuffer(char const * buffer);
    void																	setSinFamily(int domain);
    void																	setSinAddress(int Address);
    void																	setSinPort(int port);

    int 																	checkIfValid(int num, std::string str, bool imediatTerminate, size_t period = 3);
    void																	loading(size_t num);



};

#endif