/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/16 14:18:50                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/response/CommonSetup.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

CommonSetup::CommonSetup(Container container) : container_(container) {
  setHeader();
  storeFullString();
}

CommonSetup::CommonSetup( const CommonSetup & src ) {
  *this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

CommonSetup::~CommonSetup() {
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

CommonSetup &				CommonSetup::operator=( CommonSetup const & rhs ) {
	if ( this != &rhs ) {
		container_ = rhs.container_;
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void    CommonSetup::readFile() {
  if (container_.isDirectoryListed_ || container_.isDefaultErrorPage_
    || container_.request_.getMethod() == POST)
      return;
  container_.body_ = ft::getFileContent(container_.filePath_);
}

void    CommonSetup::setStatus() {
  ResponseStatusCode  statusCode(container_.filePath_,
    container_.configData_.getIndexString(), container_.errorPagesPath_,
    container_.configServer_.getErrorPage(), container_.statusCode_);
  if (container_.statusCode_ < 200 || container_.statusCode_ >= 300) {
    container_.filePath_ = statusCode.getFilePath();
    container_.body_ = statusCode.getBody();
    container_.isDefaultErrorPage_ = statusCode.isDefaultErrorPage();
  }
}

void    CommonSetup::setHeader() {
  if (!container_.utils_.isCGI(container_.request_.getURI(), container_.filePath_,
    container_.configServer_.getCGI())) {
    setStatus();
    readFile();
  }
  trimBody(HEAD);
  trimBody(PUT);
  trimBody(DELETE);
  storeHeader();
}

void    CommonSetup:: storeHeader() {
  ResponseHeader responseHeader(container_);
  container_.header_ =   responseHeader.getHeaderStr() + CRLF;
}


void   CommonSetup::trimBody(size_t method) {
  if (container_.request_.getMethod() == method)
    container_.body_.clear();
}

void    CommonSetup::storeFullString() {
  container_.fullString_ += container_.header_;
  container_.fullString_ += container_.body_;
} 

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

Container const &    CommonSetup::getContainer() const {
  return container_;
}

/* ************************************************************************** */
