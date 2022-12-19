/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/10/15 19:01:38                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef RESPONSEUTILS_HPP
# define RESPONSEUTILS_HPP

# include <iostream>
# include <string>
# include "../webserv.hpp"
# include "../utils/Timer.hpp"
#include "../../includes/response/MIME.hpp"

class ResponseUtils
{
	public:
		ResponseUtils();
		~ResponseUtils();

    bool    isValidDirectoryListing(STRING filePath, STRING index, bool autoIndex);
    bool    isNotValidMethod(STRING method, std::vector<STRING> allowMethods_);
    bool    isCGI(STRING uri, STRING filePath, std::map<STRING, STRING> cgi_map);

    std::pair<STRING, STRING>    parseCGIBody(STRING body);

    // logs
    STRING  getClientIpAddrv4(sockaddr *addr);
    void    logOutput(sockaddr *addr, STRING method, STRING uri); // Request
    void    log(sockaddr *addr, STRING method, STRING uri); // Request
    void    logOutput(sockaddr *addr, size_t status, STRING filePath); // Response
    void    log(sockaddr *addr, size_t status, STRING filePath); // Response

    STRING  addForwardSlash(STRING dir);
    void    trimMultipleForwardSlashes(STRING & path);

};

#endif /* *************************************************** RESPONSEUTILS_H */
