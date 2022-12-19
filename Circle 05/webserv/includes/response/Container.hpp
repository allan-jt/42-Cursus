/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/16 14:56:08                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef CONTAINER_HPP
# define CONTAINER_HPP

# include <iostream>
# include <string>
# include "../request/Request.hpp"
# include "../config/ConfigServer.hpp"
# include "ResponseStatusCode.hpp"
# include "ResponseUtils.hpp"
# include "CGI.hpp"

class Container
{

	public:

		Container();
		Container( Container const & src );
		~Container();

		Container &		operator=( Container const & rhs );

    Request                        request_;
    ConfigServer                   configServer_;
    ResponseUtils                  utils_;
    Location                       configData_;
    StatusCode                     statusClass_;
    STRING                         filePath_;
    STRING                         fullString_;
    STRING                         header_;
    STRING                         body_;
    STRING                         requestedFile_;
    size_t                         statusCode_;
    bool                           isDirectoryListed_;
    bool                           isDefaultErrorPage_;
    STRING                         pagesPath_;
    STRING                         errorPagesPath_;
    STRING                         newFilePath_;
    size_t                         sentBytes_;
    int                            cgiReadFd_;
    int                            cgiWriteFd_;
    bool                           cgiReadFdStatus_;
    bool                           cgiWriteFdStatus_;
    CGI                            cgi_;


};

#endif /* ******************************************************* CONTAINER_H */
