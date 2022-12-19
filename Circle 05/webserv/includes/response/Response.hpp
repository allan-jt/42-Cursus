/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/19 14:48:09                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "../request/Request.hpp" // already includes webserv.hpp
# include "../config/ConfigServer.hpp"
# include "../config/Location.hpp"
# include "CGI.hpp"
# include "DirectoryListing.hpp"
# include "ResponseHeader.hpp"
# include "ResponseStatusCode.hpp"
# include "ResponseUtils.hpp"
# include "ConfigConnector.hpp"
# include "Container.hpp"
# include "CommonSetup.hpp"

class ResponseUtils;

class Response
{
	private:
    Container   container_;
	public:
    typedef std::map<STRING, Location>     LocationMap;

    Response(Request  & request, ConfigServer conf);
		Response( Response const & src );
		~Response();

		Response &		operator=( Response const & rhs );

    // Error exception
    class FailRequest : public std::exception {};

    // setters
    void                            setRequest(Request const & req);
    void                            setConfig(ConfigServer const & conf);
    void                            setFilePath(STRING filePath);
    void                            setFullString(STRING fullString);
    void                            setHeader(STRING header);
    void                            setBody(STRING body);
    void                            setStatusCode(size_t statusCode);
    void                            setCGIReadFd(int fd);
    void                            setCGIWriteFd(int fd);
    void                            setCGIReadFdStatus(bool status);
    void                            setCGIWriteFdStatus(bool status);

    // getters
    Request const &                 getRequest() const;
    STRING const &                  getFilePath() const;
    STRING const &                  getFullString() const;
    STRING const &                  getHeader() const;
    STRING const &                  getBody() const;
    size_t const &                  getStatusCode() const;
    bool const &                    getCGIReadFdStatus() const;
    bool const &                    getCGIWriteFdStatus() const;
    int const &                     getCGIWriteFd() const;
    int const &                     getCGIReadFd() const;

    // methods
    void                            setResponseMessage();
    void                            selectMethod();
    int                             send(int fd);
    void                            isDirectoryListing();
    void                            throwExp(size_t statusCode);
    void                            setFailedResponse();
    void                            logRequest();
    void                            logResponse();
    void                            checkRedirection();
    void                            checkConfig();

    // Methods
    void                            GETReq();
    void                            HEADReq();
    void                            POSTReq();
    void                            PUTReq();
    void                            DELETEReq();

    // CGI
    bool                            isCGI();
    size_t                          cgiExecuteWrite();
    void                            cgiExecuteRead();
    void                            processCGI();

};

std::ostream &			operator<<( std::ostream & o, Response const & i );

#endif /* ******************************************************** RESPONSE_H */
