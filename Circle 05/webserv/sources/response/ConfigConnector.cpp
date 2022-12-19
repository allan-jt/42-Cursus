/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/16 11:44:50                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/response/ConfigConnector.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ConfigConnector::ConfigConnector(STRING uri, ConfigServer configServer)
: uri_(uri), orgUri_(uri), configServer_(configServer) {

  checkURIWithConfig();
}

ConfigConnector::ConfigConnector( const ConfigConnector & src ) {
  *this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ConfigConnector::~ConfigConnector() {
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ConfigConnector &				ConfigConnector::operator=( ConfigConnector const & rhs ) {
	if ( this != &rhs )
	{
		uri_ = rhs.uri_;
		configData_ = rhs.configData_;
	}
	return *this;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

STRING  ConfigConnector::setConfigIndex(STRING filePath, std::vector<STRING> vec) {
  if (!ft::isDirectory(filePath) && *filePath.rbegin() == '/')
    return STRING();
  for (std::vector<STRING>::iterator it = vec.begin(); it != vec.end(); it++)
    if (ft::isValidURI(filePath + *it, 0))
      return *it;
  return STRING();
}

void    ConfigConnector::storeLocationParameters(LocationMap::iterator & it) {
  configData_ = it->second;
  configData_.setIndexString(setConfigIndex(
    filePath_ + utils_.addForwardSlash(filePath_), it->second.getIndex()
    ));
}

void    ConfigConnector::compareURIWithLocations(STRING uri, bool & found) {
  LocationMap::iterator it = configServer_.getLocations().begin();
  for ( ; it != configServer_.getLocations().end(); it++) {
    if (uri == it->first) {
      found = true;
      filePath_ = orgUri_;
      filePath_.erase(filePath_.begin(), filePath_.begin() + uri.length());
      filePath_ = configData_.getRoot()
        + utils_.addForwardSlash(configData_.getRoot()) + filePath_;
      storeLocationParameters(it);
    }
  }
}

void    ConfigConnector::checkURIWithConfig() {
  bool found = false;
  while (!uri_.empty()) {
    compareURIWithLocations(uri_, found);
    if (found)
      break ;
    else
      uri_.erase(uri_.length()-1, 1);
  }
  compareURIWithLocations(uri_, found);
  utils_.trimMultipleForwardSlashes(filePath_);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

STRING const &    ConfigConnector::getUri() const {
  return orgUri_;
}

STRING const &    ConfigConnector::getFilePath() const {
  return filePath_;
}

Location const &  ConfigConnector::getConfigData() const {
  return configData_;
}

/* ************************************************************************** */
