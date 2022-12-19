/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/19 14:49:18                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/config/config.hpp"

Config::Config() : workers_(0) {
    parser(DEFAULT_CONFIG);
    parseConfig();
}

Config::Config(const char* filePath) : workers_(0) {
    parser(filePath);
    parseConfig();
}

Config::Config(Config const &copy) { *this = copy; }

Config &Config::operator=(Config const &rhs)
{
    if (this != &rhs) {
        servers_ = rhs.servers_;
        workers_ = rhs.workers_;
    }
    return (*this);
}

Config::~Config() {
}

/**
 * connects with File Parser class and fetch the data from the file
 * @param scopes: is a vector of MainScope class
 * @param MainScope: is "server" scope in conf.
 *      It containes elements that is under root and a vector of NestedScope
 * @param NestedScope: is "location" scope in conf.
 *      Every NestedScope containes elements and and argument in STRING type along with location
 * * Elements under the classes are in VECVECSTR type that represents lines:vector -> arg:vector -> element:STRING
 */
void    Config::parser(STRING filePath) {

    FileParser parser(filePath);
    scopes_ = parser.getScopes(MAIN_SCOPE, NESTED_SCOPE);
    confValues_ = parser.getLines();
}

void    Config::parseConfig() {
    std::vector<MainScope>::iterator it;

    for (it = scopes_.begin(); it != scopes_.end(); it++) {
      ConfigServer    *serv = new ConfigServer();
      setConfigServ(it, *serv);
      setServLocation(it, *serv);
      servers_.push_back(serv);

    }
}

void    Config::setConfigServ(std::vector<MainScope>::iterator &it, ConfigServer &serv) {
  VECVECSTR elem = it->getElements();
  if (elem.size() == 0)
    throw ConfigExceptions::InvalidConfigArg();

  VECVECSTR::iterator start = elem.begin();
  VECVECSTR::iterator end = elem.end();

  serv.parseConfig(start, end);
}

void    Config::setServLocation(std::vector<MainScope>::iterator &it, ConfigServer &serv) {
  std::vector<NestedScope>              location = it->getNestedScopes();
  std::vector<NestedScope>::iterator    locIt = location.begin();
  std::vector<NestedScope>::iterator    locEnd = location.end();

  for (; locIt != locEnd; locIt++) {
    VECVECSTR locElem = locIt->getElements();

    VECVECSTR::iterator start = locElem.begin();
    VECVECSTR::iterator end = locElem.end();

    serv.setLocations(start, end, locIt->getArg());
  }
}

std::vector<ConfigServer *> const &  Config::getServers() const {
    return (servers_);
}
