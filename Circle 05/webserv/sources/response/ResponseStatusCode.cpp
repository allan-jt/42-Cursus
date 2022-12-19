/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/10/23 10:55:41                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/response/ResponseStatusCode.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ResponseStatusCode::ResponseStatusCode(STRING filePath, STRING index,
  STRING errorPagesPath, errors_map configErrorPages, size_t statusCode)
  : statusCode_(statusCode), filePath_(filePath), index_(index),
  errorPagesPath_(errorPagesPath), defaultErrorPage_("error.html"),
  configErrorPages_(configErrorPages) {

  if (!isDefaultErrorPage())
    return ;
  storefilePath();
  storeHtmlBody();
}

ResponseStatusCode::ResponseStatusCode( const ResponseStatusCode & src ) {
  *this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ResponseStatusCode::~ResponseStatusCode() {
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ResponseStatusCode &    ResponseStatusCode::operator=( ResponseStatusCode const & rhs ) {
	if ( this != &rhs ) {
		this->statusCode_ = rhs.statusCode_;
		this->filePath_ = rhs.filePath_;
		this->errorPagesPath_ = rhs.errorPagesPath_;
	}
	return *this;
}

std::ostream &    operator<<( std::ostream & o, ResponseStatusCode const & i )
{
	o << i.getStatusCode();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

bool    ResponseStatusCode::checkConfigErrorPages() {
  for (errors_map::iterator it = configErrorPages_.begin();
    it != configErrorPages_.end(); it++)

    if (statusCode_ == it->first) {
      filePath_ = it->second;
      return true;
    }
  return false;
}

bool                ResponseStatusCode::isDefaultErrorPage() {
  return statusCode_ != 200 && !checkConfigErrorPages();
}

void                ResponseStatusCode::storefilePath() {
  filePath_ = errorPagesPath_ + defaultErrorPage_;
}

void                ResponseStatusCode::storeHtmlBody() {
  if (!ft::isValidURI(filePath_, 'r'))
    return ;
  html_ = ft::getFileContent(filePath_);
  if (html_.empty())
    return ;

  insertIntoHtmlBody();
  body_ = html_;
}

void                ResponseStatusCode::insertIntoHtmlBody() {
  insertStatusCodeTitle();
  insertStatusCodeNumber();
  insertStatusCodeMessage();
}

void                ResponseStatusCode::insertStatusCodeTitle() {
  STRING  keyStr("<title>");
  size_t elementsPos = html_.find(keyStr);
  if (elementsPos == STRING::npos)
    return ;
  elementsPos += + keyStr.length();


  html_.insert(elementsPos, ft::toString(statusCode_));
}

void                ResponseStatusCode::insertStatusCodeNumber() {
  STRING  keyStr("<h1>");
  size_t elementsPos = html_.find(keyStr);
  if (elementsPos == STRING::npos)
    return ;
  elementsPos += + keyStr.length();

  html_.insert(elementsPos, ft::toString(statusCode_));
}

void                ResponseStatusCode::insertStatusCodeMessage() {
  STRING  keyStr("<h2>");
  size_t elementsPos = html_.find(keyStr);
  if (elementsPos == STRING::npos)
    return ;
  elementsPos += + keyStr.length();

  html_.insert(elementsPos, statusCodeMap_.getStatusMessageAt(statusCode_));
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/

size_t const &  ResponseStatusCode::getStatusCode() const {
  return statusCode_;
}

STRING const &  ResponseStatusCode::getFilePath() const {
  return filePath_;
}

STRING const &  ResponseStatusCode::getBody() const {
  return body_;
}

/* ************************************************************************** */