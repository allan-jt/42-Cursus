/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     patel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/10/15 19:01:27                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/response/ResponseUtils.hpp"

ResponseUtils::ResponseUtils(){
}

ResponseUtils::~ResponseUtils(){
}

bool    ResponseUtils::isValidDirectoryListing(STRING filePath,
  STRING index, bool autoIndex) {

  return (index.empty() && ft::isDirectory(filePath)
    && *filePath.rbegin() == '/' && ft::isValidURI(filePath + index, 0)
    && autoIndex);
}

bool    ResponseUtils::isNotValidMethod(STRING method,
  std::vector<STRING> allowMethods_) {

  if (allowMethods_.empty() && method == "GET")
    return false;
  for (std::vector<STRING>::iterator it = allowMethods_.begin();
    it != allowMethods_.end(); it++)
      if (method == *it)
        return false;
  return true;
}

STRING    ResponseUtils::getClientIpAddrv4(sockaddr *addr)  {
  STRING IP;
  IP = ft::toString(int(addr->sa_data[2] & 0xff));
  for(int i = 3; i < 6; i++)
      IP += "." + ft::toString(int(addr->sa_data[i] & 0xff));
  return IP;
}

void    ResponseUtils::logOutput(sockaddr *addr, STRING method, STRING uri) {
  Timer time;
  std::cout << PURPLE << "[" << BLUE << time.getCurTimeString() << PURPLE << "]"
    << WHITE << " -> " << YELLOW << "Request" << WHITE "  > Client"
    << PURPLE << "[" << BLUE << getClientIpAddrv4(addr) << PURPLE << "]" << WHITE << ": "
    << YELLOW << method;
    if (method.length() == 3 )
      std::cout << SPACE;
    std::cout << WHITE << " | ";
    for (size_t i = 0; i < uri.length(); i++ ) {
      if (uri[i] == '/')
        std::cout << BLUE;
      else
        std::cout << PURPLE;
      std::cout << uri[i];
    }
    std::cout << RESET << std::endl;
  return ;
}

void    ResponseUtils::log(sockaddr *addr, STRING method, STRING uri) {
  std::fstream file;
  STRING logFile(DEFAULT_LOG_DIR);
  logFile += DEFAULT_LOG_FILE; 
  file.open(logFile.c_str(), std::ios_base::app);
  if (file.is_open()) {
    Timer time;
    file << "[" << time.getCurTimeString() << "] -> Request  > Client["
      << getClientIpAddrv4(addr) << "]: ";
    if (method.length() == 3)
      file << SPACE;
    file << method << " | " << uri << std::endl;
    file.close();
  }
}

void    ResponseUtils::logOutput(sockaddr *addr, size_t status, STRING filePath) {
  Timer time;
  std::cout << PURPLE << "[" << BLUE << time.getCurTimeString() << PURPLE << "]"
    << WHITE << " -> " << YELLOW << "Response" << WHITE " > Client"
    << PURPLE << "[" << BLUE << getClientIpAddrv4(addr) << PURPLE << "]" << WHITE << ": ";
  if (status >= 200 && status < 300)
    std::cout << GREEN;
  else
    std::cout << RED;
  std::cout << status << WHITE << "  | ";
  for (size_t i = 0; i < filePath.length(); i++ ) {
      if (filePath[i] == '/')
        std::cout << BLUE;
      else
        std::cout << PURPLE;
      std::cout << filePath[i];
    }
  std::cout << RESET << std::endl << std::endl;
  return ;
}

void    ResponseUtils::log(sockaddr *addr, size_t status, STRING filePath) {
  std::fstream file;
  file.open("logs/HostToast.log", std::ios_base::app);
  if (file.is_open()) {
    Timer time;
    file << "[" << time.getCurTimeString() << "] -> Response > Client["
      << getClientIpAddrv4(addr) << "]: " << status << "  | "
      << filePath << std::endl << std::endl;
    file.close();
  }
}

bool    ResponseUtils::isCGI(STRING uri, STRING filePath, std::map<STRING, STRING> cgi_map) {
  MIME mime(uri);

  if (filePath.find(mime.getContentTypeVal()) == STRING::npos)
    return false;

  for (std::map<STRING, STRING>::iterator it = cgi_map.begin() ;
    it != cgi_map.end(); it++) {
      if (it->first == mime.getContentTypeVal())
          return true;
  }
  return false;
}

std::pair<STRING, STRING>    ResponseUtils::parseCGIBody(STRING filePath) {
  std::pair<STRING, STRING> content;
  STRING lineBreak = SEPERATOR;
  size_t found = filePath.find(lineBreak);
  if (found != STRING::npos) {
    content.first = filePath.substr(0, found);
    content.second = filePath.substr(found + lineBreak.length(),
      filePath.length() - (found + lineBreak.length()));
  }

  return content;
}

STRING    ResponseUtils::addForwardSlash(STRING dir) {
  return ft::isDirectory(dir) && *dir.rbegin() != '/' ? "/" : STRING();
}

void    ResponseUtils::trimMultipleForwardSlashes(STRING & path) {
  for (STRING::iterator it = path.begin(); it != path.end(); it++)
    if (it != (path.end() - 1) && *it == '/' && *(it + 1) == '/')
      path.erase(it);
}

/* ************************************************************************** */
