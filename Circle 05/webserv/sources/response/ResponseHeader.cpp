/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/10/15 14:48:55                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/response/ResponseHeader.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ResponseHeader::ResponseHeader(Container container)
  : container_(container) {

  storeHeader();
  setHeaderStr();
}

ResponseHeader::ResponseHeader( const ResponseHeader & src ) {
  *this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ResponseHeader::~ResponseHeader() {
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ResponseHeader &    ResponseHeader::operator=( ResponseHeader const & rhs ) {
	if ( this != &rhs ) {
		header_ = rhs.header_;
		headerString_ = rhs.headerString_;
    container_ = rhs.container_;
	}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, ResponseHeader const & i ) {
  o << i.getHeaderStr();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

std::map<STRING, STRING> const &    ResponseHeader::getHeader() const{
  return header_;
}

STRING const &    ResponseHeader::getHeaderStr() const {
  return headerString_;
}

void    ResponseHeader::setHeaderStr() {
  std::map<STRING, STRING>::iterator  it = header_.begin();
  for( ; it != header_.end(); it++)
    headerString_ += it->first + KEYVAL + it->second + NEWLINE;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

bool    ResponseHeader::storeCGIHeaderIfExist(STRING key) {
  STRING value = checkCGI(key);
  if (!value.empty()) {
    header_[key] = value;
    return true;
  }
  return false;
}

void    ResponseHeader::storeContentType() {
  if (storeCGIHeaderIfExist(CONTENT_TYPE_RESPONSE))
    return;

  MIME  mime(container_.filePath_);
  if (!mime.getContentType().empty())
    header_[CONTENT_TYPE_RESPONSE] = mime.getContentType();
}

void    ResponseHeader::storeContentLength() {
  if (storeCGIHeaderIfExist(CONTENT_LENGTH_RESPONSE))
    return;
  
  header_[CONTENT_LENGTH_RESPONSE] = ft::toString(container_.body_.length());
}

void    ResponseHeader::storeContentLanguage() {
  if (storeCGIHeaderIfExist(CONTENT_LANGUAGE_RESPONSE))
    return;
  header_[CONTENT_LANGUAGE_RESPONSE] = Response_Language;
}

void    ResponseHeader::storeLocation() {
  if (storeCGIHeaderIfExist(LOCATION_RESPONSE))
    return;
  if (container_.statusCode_ >= 300 && container_.statusCode_ < 400)
    header_[LOCATION_RESPONSE] = container_.newFilePath_;
}

void    ResponseHeader::storeServer() {
  if (storeCGIHeaderIfExist(SERVER_RESPONSE))
    return;
  header_[SERVER_RESPONSE] = HOST_TOAST;
}

void    ResponseHeader::storeDate() {
  if (storeCGIHeaderIfExist(DATE_RESPONSE))
    return;
  header_[DATE_RESPONSE] = ft::getCurrentDateAndTime();
}

void    ResponseHeader::storeRetryAfter() {
  if (storeCGIHeaderIfExist(RETRY_AFTER_RESPONSE))
    return;
  header_[RETRY_AFTER_RESPONSE] = RETRY_AFTER_TIME;
}

STRING    ResponseHeader::checkCGI(STRING key) {
  key += KEYVAL;
  STRING value;
  size_t found = container_.header_.find(key);
  if (found != STRING::npos) {
    size_t newLine = container_.header_.find("\n", found);
    if (newLine != STRING::npos)
      value = container_.header_.substr(found + key.length()
        , newLine - (found + key.length()));
    else
      value = container_.header_.substr(found + key.length()
        , container_.header_.length() - (found + key.length()));
  }
  return value;
}

STRING    ResponseHeader::getServerHeader() {
  STRING  serverHeader;
  serverHeader = HTTP_ONE_ONE;
  serverHeader += SPACE;

  // check cgi status  
  STRING  cgiStatus = checkCGI(STATUS);
  if (!cgiStatus.empty())
    return serverHeader + cgiStatus + NEWLINE;

serverHeader += ft::toString(container_.statusCode_) + SPACE;
  (container_.statusCode_ >= 200 && container_.statusCode_ < 300)
    ? serverHeader += OK_STR
    : serverHeader += KO_STR;
serverHeader += NEWLINE;
  return serverHeader;
}

void    ResponseHeader::storeHeader() {
  headerString_ = getServerHeader();
  if (container_.statusCode_ != 204) {
    storeContentType();
    storeContentLength();
    storeContentLanguage();
  }
  storeLocation();
  storeServer();
  storeDate();
  storeRetryAfter();
}

/* ************************************************************************** */
