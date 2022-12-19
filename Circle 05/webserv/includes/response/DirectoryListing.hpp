/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/10/02 11:30:08                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef DIRECTORYLISTING_HPP
# define DIRECTORYLISTING_HPP

# include <iostream>
# include <string>
# include "../webserv.hpp"
# include "ResponseUtils.hpp"

class DirectoryListing
{

	public:

		DirectoryListing(STRING path, STRING pagesPath);
		DirectoryListing( DirectoryListing const & src );
		~DirectoryListing();

		DirectoryListing &		operator=( DirectoryListing const & rhs );

        STRING const &           getPath() const;
        STRING const &           getbody() const;

        void                     storeDirectoryFilesNames();
        void                     storeHtmlHead();
        void                     storeHtmlBody(std::vector<STRING> vec);
        STRING                   storeHtmlElement(std::vector<STRING>::reverse_iterator & file);

	private:
        ResponseUtils    utils_;
        STRING           path_;
        STRING           pagesPath_;
        STRING           htmlFile_;
        size_t           elementsPos_;
        STRING           body_;
        STRING           html_;
};

std::ostream &			operator<<( std::ostream & o, DirectoryListing const & i );

#endif /* ************************************************ DIRECTORYLISTING_H */