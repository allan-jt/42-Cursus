/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/10/15 14:49:08                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef RESPONSEHEADER_HPP
# define RESPONSEHEADER_HPP

# include <iostream>
# include <string>
# include "../webserv.hpp"
# include "ResponseUtils.hpp"
# include "MIME.hpp"
# include "Container.hpp"

#define CONTENT_LENGTH_RESPONSE	"Content-Length"
#define CONTENT_TYPE_RESPONSE "Content-Type"
#define CONTENT_LANGUAGE_RESPONSE "Content-Language"
#define LOCATION_RESPONSE "Location"
#define SERVER_RESPONSE "Server"
#define DATE_RESPONSE "Date" 
#define RETRY_AFTER_RESPONSE "Retry-After"

#define STATUS "Status"
#define KO_STR "KO"
#define OK_STR "OK"
#define RETRY_AFTER_TIME "42"
#define Response_Language "en"

class ResponseHeader
{

	private:
    Container                       container_;
    ResponseUtils                   utils_;
    std::map<STRING, STRING>        header_;
    STRING                          headerString_;

	public:

		ResponseHeader(Container container);
		ResponseHeader( ResponseHeader const & src );
		~ResponseHeader();

		ResponseHeader &		operator=( ResponseHeader const & rhs );

    std::map<STRING, STRING> const &  getHeader() const;
    STRING const &                    getHeaderStr() const;
    void                              setHeaderStr() ;

    STRING                            getServerHeader();
    void                              storeHeader();
    void                              storeContentType();
    void                              storeContentLength();
    void                              storeContentLanguage();
    void                              storeLocation();
    void                              storeServer();
    void                              storeDate();
    void                              storeRetryAfter();
    STRING                            checkCGI(STRING key);
    bool                              storeCGIHeaderIfExist(STRING key);

};

std::ostream &			operator<<( std::ostream & o, ResponseHeader const & i );

#endif /* ************************************************** RESPONSEHEADER_H */