/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/19 14:49:24                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/config/ConfigServer.hpp"

ConfigServer::ConfigServer() :  clientMaxBodySize_(0) {
  setupRootDirectives();
  setupLocationDirectives();
}

ConfigServer::ConfigServer(ConfigServer const &copy) { *this = copy; }

ConfigServer    &ConfigServer::operator=( ConfigServer const &rhs) {
  if (this != &rhs) {
    host_ = rhs.host_;
    port_ = rhs.port_;
    serverName_ = rhs.serverName_;
    errorPage_ = rhs.errorPage_;
    clientMaxBodySize_ = rhs.clientMaxBodySize_;
    cgi_ = rhs.cgi_;
    locations_ = rhs.locations_;
    exceptions_ = rhs.exceptions_;
    rootDirectives_ = rhs.rootDirectives_;
    locationDirectives_ = rhs.locationDirectives_;
    locationDirectivesVars_ = rhs.locationDirectivesVars_;
  }
  return *this;
}

ConfigServer::~ConfigServer() {

}

void    ConfigServer::setupRootDirectives() {
  rootDirectives_[DIR_LISTEN] = &ConfigServer::setHost;
  rootDirectives_[DIR_PORT] = &ConfigServer::setPort;
  rootDirectives_[DIR_ERROR_PAGE] = &ConfigServer::setErrorPage;
  rootDirectives_[DIR_SERVER_NAME] = &ConfigServer::setServerName;
  rootDirectives_[DIR_CGI] = &ConfigServer::setCGI;
}

void    ConfigServer::setupLocationDirectives() {
  locationDirectivesVars_[DIR_METHODS] = &Location::setAllowMethods;
  locationDirectivesVars_[DIR_INDEX] = &Location::setIndex;
  locationDirectives_[DIR_CLIENT_MAX_BODY_SIZE] = &Location::setClientBodyBufferSize;
  locationDirectives_[DIR_AUTOINDEX] = &Location::setAutoIndex;
  locationDirectives_[DIR_REDIRECTION] = &Location::setRedirection;
  locationDirectives_[DIR_ROOT] = &Location::setRoot;
}

void    ConfigServer::parseConfig(VECVECSTR::iterator &mainIt, VECVECSTR::iterator &end) {

  Location                        context;
  std::vector<STRING>::iterator   it;

  for ( ; mainIt != end; mainIt++) {
    for (it = mainIt->begin(); it != mainIt->end(); it++) {
      if (rootDirectives_.count(*it))
        (this->*rootDirectives_[*it])(++it);
      else if (locationDirectives_.count(*it))
        (context.*locationDirectives_[*it])(++it);
      else if (locationDirectivesVars_.count(*it))
        (context.*locationDirectivesVars_[*it])(++it, mainIt->end() - 1);
      else
          throw ConfigExceptions::InvalidConfigArg();
    }
  }

  context.setDefault(errorPage_, clientMaxBodySize_);
  locations_.insert(std::pair<STRING, Location>("", context));
}

void    ConfigServer::setLocations(VECVECSTR::iterator &locIt,
  VECVECSTR::iterator &locEnd, STRING dirLocation) {

  std::vector<STRING>::iterator   it;

  Location   context;
  for (; locIt != locEnd; locIt++) {
    for (it = locIt->begin(); it != locIt->end(); it++) {
      if (locationDirectives_.count(*it))
        (context.*locationDirectives_[*it])(++it);
      else if (locationDirectivesVars_.count(*it))
        (context.*locationDirectivesVars_[*it])(++it, locIt->end() - 1);
      else
        throw ConfigExceptions::InvalidConfigArg();
    }
  }
  context.setDefault(errorPage_, clientMaxBodySize_);
  locations_.insert(std::pair<STRING, Location>(dirLocation, context));
}

void    ConfigServer::setHost(std::vector<STRING>::iterator &it) {
    if (!host_.empty())
      throw ConfigExceptions::InvalidHost();
    host_ = *(it);
    if (host_.empty())
        throw ConfigExceptions::InvalidHost();
}

void    ConfigServer::setPort(std::vector<STRING>::iterator &it) {
  int port = -1;
  if (!ft::test_int((*it).c_str(), &port) || (port <  0 || port > 65536))
    throw ConfigExceptions::InvalidPort();

  port_.push_back(port);
  if (ft::checkVectorDuplicates(port_))
    throw ConfigExceptions::InvalidPort();
}

void    ConfigServer::setServerName(std::vector<STRING>::iterator &it) {
    if (!serverName_.empty())
        throw ConfigExceptions::InvalidServerName();
    serverName_ = *(it);
    if (serverName_.empty())
        throw ConfigExceptions::InvalidServerName();
}

void    ConfigServer::setErrorPage(std::vector<STRING>::iterator &it) {
    try {
        int  errorNo = 0;
        if (!ft::test_int((*it++).c_str(), &errorNo) ||
          ((errorNo < 401 || errorNo > 599)))
          throw ConfigExceptions::InvalidErrorPage();

        STRING  errorLocation = *it;
        char    *path = getcwd(NULL, 0);
        STRING  pathString = path + ("/" + errorLocation);
        free(path);
        if (!ft::isValidURI(pathString, 0))
          throw ConfigExceptions::InvalidErrorPage();

        if (ft::checkMapDuplicate(errorPage_, (size_t)errorNo))
          throw ConfigExceptions::InvalidErrorPage();
        errorPage_.insert(std::pair<size_t, STRING>((size_t)errorNo, errorLocation));
    }
    catch (ConfigExceptions &e) {
        throw ConfigExceptions::InvalidErrorPage();
    }
}

void    ConfigServer::setClientMaxBodySize(std::vector<STRING>::iterator &it) {
    if (clientMaxBodySize_ != 0)
        throw ConfigExceptions::InvalidClientMaxBodySize();
    int maxSize = -1;
    if (!ft::test_int((*it).c_str(), &maxSize) || maxSize <= 0)
        throw ConfigExceptions::InvalidClientMaxBodySize();
    clientMaxBodySize_ = maxSize;
}

void    ConfigServer::setCGI(std::vector<STRING>::iterator &it) {
    char    *path = getcwd(NULL, 0);
    STRING  extention = *it++;
    extention = extention.substr(extention.find_first_of('.') + 1);
    STRING  file = *it;
    STRING  extPath = path + ("/cgi-bin/" + file);
    free(path);

    if (ft::checkMapDuplicate(cgi_, extention) || !ft::isValidURI(extPath, 0))
      throw ConfigExceptions::InvalidCgiPass();
    cgi_[extention] = file;
}

bool    ConfigServer::is_number(const std::string& s)
{
    STRING::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

STRING const &  ConfigServer::getHost() const {
    return host_;
}

std::vector<int> const &    ConfigServer::getPort() const {
    return port_;
}

STRING const &  ConfigServer::getServerName() const {
    return serverName_;
}

std::map<size_t, STRING> const & ConfigServer::getErrorPage() const {
    return errorPage_;
}

size_t const &     ConfigServer::getClientMaxBodySize() const {
    return clientMaxBodySize_;
}

std::map<STRING, STRING> const & ConfigServer::getCGI() const {
    return cgi_;
}

ConfigServer::LocationMap &     ConfigServer::getLocations() {
    return locations_;
}
