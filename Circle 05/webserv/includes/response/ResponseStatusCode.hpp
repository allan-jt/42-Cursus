/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/10/23 10:55:34                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef RESPONSESTATUSCODE_HPP
# define RESPONSESTATUSCODE_HPP

# include <iostream>
# include <string>
# include "../webserv.hpp"
# include "ResponseUtils.hpp"
# include "../utils/StatusCode.hpp"

class ResponseStatusCode
{
    typedef std::map<size_t, STRING>  errors_map;

	private:
        ResponseUtils   utils_;
        size_t          statusCode_;
        STRING          filePath_;
        STRING          index_;
        STRING          errorPagesPath_;
        STRING          defaultErrorPage_;
        STRING          body_;
        STRING          html_;
        errors_map      configErrorPages_;
        StatusCode      statusCodeMap_;

	public:
		ResponseStatusCode(STRING path, STRING index, STRING errorPagesPath,
            errors_map configErrorPages, size_t statusCode = 200);
		ResponseStatusCode(ResponseStatusCode const & src);
		~ResponseStatusCode();

		ResponseStatusCode &		operator=(ResponseStatusCode const & rhs);
    
    void            storefilePath();
    void            storeHtmlBody();
    void            insertIntoHtmlBody();
    void            insertStatusCodeTitle();
    void            insertStatusCodeNumber();
    void            insertStatusCodeMessage();
    bool            checkConfigErrorPages();
    bool            isDefaultErrorPage();

    size_t const &  getStatusCode() const;
    STRING const &  getFilePath() const;
    STRING const &  getBody() const;

};

std::ostream &			operator<<( std::ostream & o, ResponseStatusCode const & i );

#endif /* ****************************************************** STATUSCODE_H */