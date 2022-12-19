/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/19 14:50:04                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/response/Response.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Response::Response(Request & request, ConfigServer conf) {
  container_.request_ = request;
  container_.configServer_ = conf;
  container_.requestedFile_ = container_.request_.getURI();
  container_.statusCode_ = container_.request_.getStatusClass().getStatusCode();

  logRequest();
  try {
    setResponseMessage();
  }
  catch(const FailRequest& e) {
    setFailedResponse();
  }
}

Response::Response( const Response & src ) {
  *this = src;
}

Response::~Response() {
}

Response &    Response::operator=( Response const & rhs ) {
	if ( this != &rhs )
    container_ = rhs.container_;
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Response const & i ) {
	o << i.getFullString();
	return o;
}

void    Response::isDirectoryListing() {
  if (container_.utils_.isValidDirectoryListing(container_.filePath_,
    container_.configData_.getIndexString(), container_.configData_.getAutoIndex())) {

    container_.isDirectoryListed_ = true;
    DirectoryListing  dir(container_.configData_.getRoot()
      + container_.requestedFile_, container_.pagesPath_);
    container_.filePath_ = container_.pagesPath_ + DEFAULT_DIRLIST_FILE;
    container_.body_ += dir.getbody();
  }
  else if (*container_.requestedFile_.rbegin() == '/')
    container_.filePath_ += container_.configData_.getIndexString();
  else if (ft::isDirectory(container_.requestedFile_)) {
    container_.filePath_ += "/";
    container_.filePath_ += container_.configData_.getIndexString();
  }

}

void    Response::HEADReq() {
  GETReq();
}

void    Response::GETReq() {
  isDirectoryListing();
  if ((ft::isDirectory(container_.filePath_)
    && container_.configData_.getIndexString().empty())
    || !ft::isValidURI(container_.filePath_, 0))
      throwExp(NOT_FOUND);
}

void    Response::POSTReq() {
  container_.body_ = container_.request_.getBody();
  if (container_.body_.length() > container_.configData_.getClientMaxBodySize()
    && container_.configData_.getClientMaxBodySize())
    throwExp(CONTENT_TOO_LARGE);
  else if (ft::createFile(container_.filePath_, container_.body_, false))
    container_.statusCode_ = CREATED;
  else
    container_.statusCode_ = OK;
}

void    Response::PUTReq() {
  if (container_.body_.length() > container_.configData_.getClientMaxBodySize()
      && container_.configServer_.getClientMaxBodySize())
    throwExp(CONTENT_TOO_LARGE);

  if (ft::createFile(container_.filePath_,
    container_.request_.getBody(), true))
      container_.statusCode_ = CREATED;
  else
    container_.statusCode_ = NO_CONTENT;
}

void    Response::DELETEReq() {
  if (ft::isValidURI(container_.filePath_, 0)) {
    ft::deleteFile(container_.filePath_);
    container_.statusCode_ = NON_AUTHORITATIVE_INFO;
  }
  else
    throwExp(NOT_FOUND);
}

void    Response::checkConfig() {
  ConfigConnector configConnector(container_.requestedFile_, container_.configServer_);
  container_.configData_ = configConnector.getConfigData();
  container_.requestedFile_ = configConnector.getUri();
  container_.filePath_ = configConnector.getFilePath();
}

void    Response::checkRedirection() {
  std::pair<size_t, STRING> redir = container_.configData_.getRedirections();
  if (!redir.second.empty()) {
    container_.statusCode_ = redir.first;
    container_.newFilePath_ = redir.second;
    throwExp(container_.statusCode_);
  }
}

bool    Response::isCGI() {
  return container_.utils_.isCGI(container_.request_.getURI(), container_.filePath_,
    container_.configServer_.getCGI());
}

void    Response::setResponseMessage() {
  if (container_.statusCode_ != OK)
    throwExp(container_.statusCode_);
  
  checkConfig();
  checkRedirection();
  selectMethod();
}

void  Response::setFailedResponse() {
  container_ = CommonSetup(container_).getContainer();
}

void  Response::throwExp(size_t statusCode) {
  container_.statusCode_ = statusCode;
  throw Response::FailRequest();
}

void   Response::logRequest() {
  container_.utils_.log((struct sockaddr *)&container_.request_.getClientAddr(),
    container_.request_.getStringMethod(), container_.request_.getURI());
  if (LOG)
    container_.utils_.logOutput((struct sockaddr *)&container_.request_.getClientAddr(),
      container_.request_.getStringMethod(), container_.request_.getURI());
}

void   Response::logResponse() {
  container_.utils_.log((struct sockaddr *)&container_.request_.getClientAddr(),
    container_.statusCode_, container_.filePath_);
  if (LOG)
    container_.utils_.logOutput((struct sockaddr *)&container_.request_.getClientAddr(),
      container_.statusCode_, container_.filePath_);
}

int   Response::send(int fd) {
  int len = write(fd, container_.fullString_.c_str() + container_.sentBytes_,
    container_.fullString_.length() - container_.sentBytes_);

  container_.sentBytes_ += len;
  if (len == -1 || container_.fullString_.length() == container_.sentBytes_)
	  logResponse();
  if (len == -1)
    return -1;
  return container_.fullString_.length() - container_.sentBytes_;
}

void    Response::selectMethod() {
  if (container_.utils_.isNotValidMethod(container_.request_.getStringMethod(),
    container_.configData_.getAllowMethods()))
      throwExp(METHOD_NOT_ALLOWED);

  if (container_.request_.getMethod() == HEAD)
    HEADReq();
  else if (container_.request_.getMethod() == GET)
    GETReq();

  if (isCGI()) {
    processCGI();
    if (container_.statusCode_ > 400)
      throwExp(container_.statusCode_);
  }
  else {
    if (ft::isDirectory(container_.filePath_) && 
      (container_.request_.getMethod() == PUT
      || container_.request_.getMethod() == DELETE))
        throwExp(FORBIDDEN);
    if (container_.request_.getMethod() == POST)
      POSTReq();
    else if (container_.request_.getMethod() == PUT)
      PUTReq();
    else if (container_.request_.getMethod() == DELETE)
      DELETEReq();
  }

  if (!isCGI())
    container_ = CommonSetup(container_).getContainer();
}

void   Response::processCGI() {
  container_.cgiWriteFdStatus_ = false;
  MIME mime(container_.request_.getURI());
  container_.cgi_.setDefault(getRequest(), container_.configServer_.getCGI(),
    container_.filePath_, mime.getContentTypeVal());
  if ((container_.statusCode_ = container_.cgi_.initCGI()) > BAD_REQUEST) {
    container_.cgiWriteFdStatus_ = true;
    return ;
  }

  container_.cgiWriteFd_ = container_.cgi_.getWriteFd();
  container_.cgiReadFd_ = container_.cgi_.getReadFd();
  container_.statusCode_ = container_.cgi_.executeCGI();

}

size_t  Response::cgiExecuteWrite() {
  container_.statusCode_ = container_.cgi_.parentProcess();
  return container_.statusCode_;
}

void  Response::cgiExecuteRead() {
  container_.body_ = container_.cgi_.readBody();
  std::pair<STRING, STRING> content = container_.utils_.parseCGIBody(container_.body_);
  container_.header_ = content.first;
  container_.body_ = content.second;

}

void    Response::setCGIReadFdStatus(bool status) {
  container_.cgiReadFdStatus_ = status;
  if (container_.cgiReadFdStatus_ == true) {
    cgiExecuteRead();
    container_ = CommonSetup(container_).getContainer();
  }
}

void    Response::setCGIWriteFdStatus(bool status) {
  container_.cgiWriteFdStatus_ = status;
  if (container_.cgiWriteFdStatus_ == true){
    if ((container_.statusCode_ = cgiExecuteWrite()) == OK)
      container_.cgiReadFdStatus_ = false;
    else {
      container_ = CommonSetup(container_).getContainer();
    }
  }
}

void    Response::setRequest(Request const & req) {
  container_.request_ = req;
}

void    Response::setConfig(ConfigServer const & conf) {
  container_.configServer_ = conf;
}

void    Response::setFilePath(STRING filePath) {
  container_.filePath_ = filePath;
}

void    Response::setFullString(STRING fullString) {
  container_.fullString_ = fullString;
}

void    Response::setHeader(STRING header) {
  container_.header_ = header;
}

void    Response::setBody(STRING body) {
  container_.body_ = body;
}

void    Response::setStatusCode(size_t statusCode) {
  container_.statusCode_ = statusCode;
}

void    Response::setCGIReadFd(int fd) {
  container_.cgiReadFd_ = fd;
}

void    Response::setCGIWriteFd(int fd) {
  container_.cgiWriteFd_ = fd;
}

Request const &   Response::getRequest() const {
  return container_.request_;
}

STRING const &    Response::getFilePath() const {
  return container_.filePath_;
}

STRING const &    Response::getFullString() const {
  return container_.fullString_;
}

STRING const &    Response::getHeader() const {
  return container_.header_;
}

STRING const &    Response::getBody() const {
  return container_.body_;
}

size_t const &    Response::getStatusCode() const {
  return container_.statusCode_;
}

int const & Response::getCGIReadFd() const {
  return (container_.cgiReadFd_);
}

int const & Response::getCGIWriteFd() const {
  return (container_.cgiWriteFd_);
}

bool const & Response::getCGIReadFdStatus() const {
  return (container_.cgiReadFdStatus_);
}

bool const & Response::getCGIWriteFdStatus() const {
  return (container_.cgiWriteFdStatus_);
}
