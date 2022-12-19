/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/10 13:46:22                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/config/Location.hpp"

Location::Location() : root_(""),fileUpload_(false), autoIndex_(false),
  clientBodyBufferSize_(0) {
}

Location::Location( Location const &cp ) { *this = cp; }

Location    &Location::operator=( Location const &rhs ) {
    if (this != &rhs) {
      allowMethods_ = rhs.allowMethods_;
      index_ = rhs.index_;
      indexString_ = rhs.indexString_;
      redirection_ = rhs.redirection_;
      root_ = rhs.root_;
      cgiPass_ = rhs.cgiPass_;
      fileUpload_ = rhs.fileUpload_;
      autoIndex_ = rhs.autoIndex_;
      clientBodyBufferSize_ = rhs.clientBodyBufferSize_;
      errorPage_ = rhs.errorPage_;
      clientMaxBodySize_ = rhs.clientMaxBodySize_;
    }
    return (*this);
}

Location::~Location() {
}

void    Location::setAllowMethods(std::vector<STRING>::iterator &it,
  std::vector<STRING>::iterator end) {

  while (true) {
    if (*it == "GET" || *it == "POST" || *it == "DELETE" || *it == "PUT" || *it == "HEAD")
      allowMethods_.push_back(*it);
    else
      throw ConfigExceptions::InvalidAllowMethods();
    if (it == end)
      break ;
    it++;
  }
    if (ft::checkVectorDuplicates(allowMethods_))
      throw ConfigExceptions::InvalidAllowMethods();
}

void    Location::setAutoIndex(std::vector<STRING>::iterator &it) {
  STRING  autoIndex = *it;
  if (autoIndex != "on" && autoIndex != "off")
      throw ConfigExceptions::InvalidAutoIndex();
  if (autoIndex == "on")
      autoIndex_ = true;
}

void    Location::setCgiPass(std::vector<STRING>::iterator &it) {
  cgiPass_ = *it;
}

void    Location::setClientBodyBufferSize(std::vector<STRING>::iterator &it) {
    if (clientBodyBufferSize_ != 0)
        throw ConfigExceptions::InvalidClientMaxBodySize();
    int bufferSize = -1;
    if (!ft::test_int((*it).c_str(), &bufferSize) || bufferSize <= 0)
        throw ConfigExceptions::InvalidClientMaxBodySize();
    clientBodyBufferSize_ = bufferSize;
}

void    Location::setFileUpload(std::vector<STRING>::iterator &it) {
  STRING upload = *it;
  if (upload != "on" && upload != "off")
      throw ConfigExceptions::InvalidFileUpload();
  if (upload == "on")
      fileUpload_ = true;
}

void    Location::setIndex(std::vector<STRING>::iterator &it,
  std::vector<STRING>::iterator end) {

  if (!index_.empty())
    throw ConfigExceptions::InvalidIndex();
  while (true) {
    index_.push_back(*it);
    if (it == end)
      break ;
    it++;
  }
  if (ft::checkVectorDuplicates(index_))
    throw ConfigExceptions::InvalidIndex();
}

void    Location::setIndexString(STRING index) {
  indexString_ = index;
}

void    Location::setRedirection(std::vector<STRING>::iterator &it) {
  if (redirection_.first != 0 && redirection_.second.empty())
    throw ConfigExceptions::InvalidRedirection();
  std::pair<size_t, STRING> redir;
  int statusCode = 0;
  if (!ft::test_int((*(it++)).c_str(), &statusCode)
    || (statusCode < 300 || statusCode >= 400))
      throw ConfigExceptions::InvalidRedirection();
  redir.first = (size_t)statusCode;
  redir.second = *it;
  redirection_ = redir;
}

void    Location::setRoot(std::vector<STRING>::iterator &it) {
    if (!root_.empty())
      throw ConfigExceptions::InvalidRoot();
    root_ = *it;
    char    *path = getcwd(NULL, 0);
    STRING  pathString = path + ("/" + root_);
    free(path);
    if (!ft::isDirectory(pathString) || root_.empty())
        throw ConfigExceptions::InvalidRoot();
}

void    Location::setDefault(std::map<size_t, STRING> errorPage, size_t clientMaxBody) {
  errorPage_ = errorPage;
  clientMaxBodySize_ = clientMaxBody;
  if (root_.empty())
    root_ = "www/";
  if (index_.empty())
    index_.push_back(DEFAULTINDEX);
}

std::vector<STRING> const &   Location::getAllowMethods() const{
    return (allowMethods_);
}

std::vector<STRING> const &   Location::getIndex() const{
    return (index_);
}

STRING const &    Location::getIndexString() const{
    return (indexString_);
}

std::pair<size_t, STRING> const &    Location::getRedirections() const{
    return (redirection_);
}

STRING const &    Location::getRoot() const{
    return (root_);
}

STRING const &    Location::getCGIPass() const{
    return (cgiPass_);
}

bool const &    Location::getFileUpload() const{
    return (fileUpload_);
}

bool const &    Location::getAutoIndex() const{
    return (autoIndex_);
}

std::map<size_t, STRING> const &    Location::getErrorPage() const {
  return (errorPage_);
}

size_t const &    Location::getClientMaxBodySize() const {
  return (clientBodyBufferSize_);
}

bool    Location::is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
