/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/16 14:56:01                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/response/Container.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Container::Container() : statusCode_(0), isDirectoryListed_(false)
  , isDefaultErrorPage_(false), pagesPath_(DEFAULTPAGES)
  , errorPagesPath_(DEFAULTPAGES), sentBytes_(0), cgiReadFd_(-1)
  , cgiWriteFd_(-1), cgiReadFdStatus_(true), cgiWriteFdStatus_(true) {
}

Container::Container( const Container & src ) {
  *this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Container::~Container() {
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Container &				Container::operator=( Container const & rhs ) {
	if ( this != &rhs ) {
		request_ = rhs.request_;
    configServer_ = rhs.configServer_;
    utils_ = rhs.utils_;
    configData_ = rhs.configData_;
    statusClass_ = rhs.statusClass_;
    filePath_ = rhs.filePath_;
    fullString_ = rhs.fullString_;
    header_ = rhs.header_;
    body_ = rhs.body_;
    requestedFile_ = rhs.requestedFile_;
    statusCode_ = rhs.statusCode_;
    isDirectoryListed_ = rhs.isDirectoryListed_;
    isDefaultErrorPage_ = rhs.isDefaultErrorPage_;
    pagesPath_ = rhs.pagesPath_;
    errorPagesPath_ = rhs.errorPagesPath_;
    newFilePath_ = rhs.newFilePath_;
    sentBytes_ = rhs.sentBytes_;
    cgiReadFd_ = rhs.cgiReadFd_;
    cgiWriteFd_ = rhs.cgiWriteFd_;
    cgiReadFdStatus_ = rhs.cgiReadFdStatus_;
    cgiWriteFdStatus_ = rhs.cgiWriteFdStatus_;
	}
	return *this;
}

/* ************************************************************************** */
