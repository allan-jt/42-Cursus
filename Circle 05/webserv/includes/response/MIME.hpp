/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/10/26 10:36:19                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef MIME_HPP
# define MIME_HPP

# include <iostream>
# include <string>
# include "../webserv.hpp"
# include "ResponseUtils.hpp"
# include "../config/FileParser.hpp"

class MIME
{
	private:
    STRING    filePath_;
    STRING    extension_;
    STRING    contentType_;
    STRING    contentTypeVal_;


	public:

		MIME(STRING filePath);
		MIME( MIME const & src );
		~MIME();

    class InvalidMimeTypes : public std::exception {
      public:
        const char * what() const throw();
    };

		MIME &		operator=( MIME const & rhs );

    STRING                            searchInMIMETypes();

    STRING const &                    getContentType() const;
    STRING const &                    getContentTypeVal() const;


};

std::ostream &			operator<<( std::ostream & o, MIME const & i );

#endif /* ************************************************************ MIME_H */
