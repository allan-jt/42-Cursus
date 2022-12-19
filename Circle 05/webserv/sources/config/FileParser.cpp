/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/25 10:38:15                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/config/FileParser.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FileParser::FileParser(STRING fileName) : filePath_(fileName) {
  file_.open(fileName.c_str());
  if (!file_.is_open())
    throw FileParser::InvalidFile();

  // check file size if greater than 1000
  struct stat stat_buf;
  int rc = stat(fileName.c_str(), &stat_buf);
  if (rc || (!rc && stat_buf.st_size > 1000000))
    throw FileParser::InvalidFile();

  storeFileContent();
}

FileParser::FileParser( const FileParser & src ) {
  *this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

FileParser::~FileParser() {
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

FileParser &				FileParser::operator=( FileParser const & rhs )
{
	if ( this != &rhs ) {
		lines_ = rhs.lines_;
    scopesObj_ = rhs.scopesObj_;
    argPos_ = rhs.argPos_;
    filePath_ = rhs.filePath_;
	}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, FileParser const & i )
{
  FileParser tmp = i;
  tmp.printVec(i.getLines()); // it will only print on std::cout
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/
void    FileParser::printVec(VECVECSTR lines) {
  VECVECSTR linesCopy = lines;
  for (std::vector<std::vector<STRING> >::iterator line = linesCopy.begin();
    line != linesCopy.end(); line++) {

    std::cout << "line-> ";
    for (std::vector<STRING>::iterator arg = (*line).begin(); arg != (*line).end(); arg++)
      std::cout << "|" << *arg << "| ";
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void    FileParser::printScopes() {
  std::cout << scopesObj_;
}

void    FileParser::storeFileContent() {
  STRING line;
  while (getline(file_, line))
    lines_.push_back(storeLineArgs(line));
}

std::vector<STRING>   FileParser::storeLineArgs(STRING line) {
  STRING  arg;
  std::vector<STRING> lineArgs;
  std::stringstream args(line);

  while (args >> arg)
    lineArgs.push_back(arg);

  return lineArgs;
}

std::vector<MainScope>   FileParser::getScopes(STRING scopeName, STRING nestedScopeName) {
  scopesObj_.setScopes(filePath_, lines_);
  scopesObj_.storeScopes(scopeName, nestedScopeName);
  return scopesObj_.getScopes();
}

bool    FileParser::findArg(VECVECSTR lines, STRING str) {
  size_t lineIndex = 0;
  for (std::vector<std::vector<STRING> >::iterator line = lines.begin();
    line != lines.end(); line++, lineIndex++) {

    size_t argIndex = 0;
    for (std::vector<STRING>::iterator arg = (*line).begin();
      arg != (*line).end(); arg++, argIndex++) {
      
      if (*arg == str) {
        argPos_ = std::pair<size_t, size_t>(lineIndex, argIndex);
        return true;
      }
    }
  }
  return false;
}

const char * FileParser::InvalidFile::what() const throw() {
  return INVALID_FILE;
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::pair<size_t, size_t> const &   FileParser::getArgPos() const {
  return argPos_;
}

VECVECSTR const &   FileParser::getLines() const {
  return lines_;
}



/* ************************************************************************** */