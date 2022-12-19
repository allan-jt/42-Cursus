/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/26 12:36:56                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/config/Scopes.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Scopes::Scopes()
  : lineIndex_(0), lineArgIndex_(0) {
}

Scopes::Scopes(STRING filePath, VECVECSTR lines)
  : filePath_(filePath), lines_(lines), lineIndex_(0), lineArgIndex_(0) {
}

Scopes::Scopes( const Scopes & src ) {
  *this = src;  
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Scopes::~Scopes() {
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Scopes &				Scopes::operator=( Scopes const & rhs ) {
	if ( this != &rhs ) {
    filePath_ = rhs.filePath_;
		scope_ = rhs.scope_;
    scopeArg_ = rhs.scopeArg_;
    lines_ = rhs.lines_;
    lineIndex_ = rhs.lineIndex_;
    lineArgIndex_ = rhs.lineArgIndex_;
    scopes_ = rhs.scopes_;
	}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Scopes const & i )
{
	std::vector<MainScope> scopes = i.getScopes();
  for (std::vector<MainScope>::iterator scope = scopes.begin();
    scope != scopes.end(); scope++)
      std::cout << *scope << std::endl;
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void    Scopes::printPos() {
  std::cout << "lineIndex_: " << lineIndex_ << std::endl;
  std::cout << "lineArgIndex_: " << lineArgIndex_ << std::endl;

  if (!lines_.empty() && !lines_[lineIndex_].empty())
    std::cout << "lines_[" << lineIndex_ << "][" << lineArgIndex_ << "]"
      << ": |" << CURARG << "|" << std::endl;
}

void    Scopes::resetIndexes() {
  lineIndex_ = 0;
  lineArgIndex_ = 0;
}

bool    Scopes::go2NextScope(STRING str) {
  if (!lines_[lineIndex_].empty() && getCurArg() != str)
    return false;
  else if (getCurArg() == str)
    return true;

  size_t lineIndex = lineIndex_;
  size_t lineArgIndex = lineArgIndex_;

  move2Next();

  if (getCurArg() != str) {
    lineIndex_ = lineIndex;
    lineArgIndex_ = lineArgIndex;
    return false;
  }
  return true;
}

bool    Scopes::end() {
  return lineIndex_ >= lines_.size();
}

bool    Scopes::move2Next() {
  if (lineIndex_ == lines_.size())
    return false;
  else if ( !lines_[lineIndex_].size()
    || lineArgIndex_ == lines_[lineIndex_].size() - 1) {
    
    lineArgIndex_ = 0;
    lineIndex_++;
  }
  else
    lineArgIndex_++;
  if (lineIndex_ < lines_.size() && lines_[lineIndex_].empty())
    move2Next();
  
  return true;
}

bool    Scopes::isNestedScope() {
  return CURARG == scope_ && !lineArgIndex_;
}

size_t    Scopes::checkSemicolon() {
  size_t found = CURARG.find_first_of(";");

  if ((found != STRING::npos && (lineArgIndex_ != lines_[lineIndex_].size() - 1 // if found before last element
      || (lineArgIndex_ == lines_[lineIndex_].size() - 1 && CURARG[found] != *CURARG.rbegin()))) // if found in last element but not at the end
    || (found == STRING::npos && lineArgIndex_ == lines_[lineIndex_].size() - 1) // if not found in last element
    || (found != STRING::npos && !lineArgIndex_ && !found) // if found with empty element
    )
      throw Scopes::InvalidConfig();
  return found;
}

std::vector<STRING>   Scopes::storeElementsArgs() {
  std::vector<STRING> args;

  size_t line = lineIndex_;
  while (!end() && line == lineIndex_) {
    size_t found = checkSemicolon();
    if (found != STRING::npos) {
      if (found) // if it's in the last element and stick with another arg
        args.push_back(CURARG.substr(0, CURARG.length() - 1));
      break;
    }
    args.push_back(CURARG);
    move2Next();
  }
  return args;
}

VECVECSTR   Scopes::storeScopeElements() {
  VECVECSTR elements;

  while (!end()) {
    if (isNestedScope() || CURARG == "}")
      break ;
    elements.push_back(storeElementsArgs());
    move2Next();
  }
  if (!isNestedScope() && CURARG != "}")
    throw Scopes::InvalidConfig();
  return elements;
}

bool    Scopes::checkScopeStart(STRING scope, bool isScopeArgValid) {
  scopeArg_.clear();
  if (!isScopeArgValid && go2NextScope(scope + "{")) {
    move2Next();
    return true;
  }
  if (go2NextScope(scope)) {
    move2Next();
    if (!isScopeArgValid && CURARG != "{")
      return false;
    else if (isScopeArgValid) {
      if (CURARG.find_first_of("{};") != STRING::npos)
        return false;
      scopeArg_ = CURARG;
      move2Next();
      if (CURARG != "{")
        return false;
    }
  }
  else
    return false;

  move2Next();
  return true;
}

std::pair<VECVECSTR, std::vector<NestedScope> >   Scopes::getScopeElements(
  STRING mainScopeName, STRING nestedScopeName, bool isScopeArgValid) {

  std::pair<VECVECSTR, std::vector<NestedScope> > content;
  scope_ = mainScopeName;
  if (checkScopeStart(mainScopeName, isScopeArgValid)) {
    scope_ = nestedScopeName;
    content.first = storeScopeElements();
    while (isNestedScope()) {
      if (checkScopeStart(nestedScopeName, true))
        content.second.push_back(NestedScope(storeScopeElements(),
          nestedScopeName, scopeArg_));
      else
        throw Scopes::InvalidConfig();
      move2Next();
    }
    move2Next();
  }
  else
    throw Scopes::InvalidConfig();
  return content;
}

void  Scopes::storeScopes(STRING mainScopeName, STRING nestedScopeName) {
  scopeArg_ = nestedScopeName;
  resetIndexes();
  while (!end()) {
    try {
      scopes_.push_back(MainScope(
        getScopeElements(mainScopeName, nestedScopeName, false),
        std::pair<STRING, STRING>(mainScopeName, nestedScopeName)
        ));
    }
    catch(const InvalidConfig& e) {
      scopes_.clear();
      throw Scopes::InvalidConfig();
    }
  }
  if (scopes_.empty())
    throw Scopes::InvalidConfig();
}

STRING    Scopes::getCurArg() {
  if (!lines_.empty() && !lines_[lineIndex_].empty())
    return CURARG;
  return STRING();
}

const char * Scopes::InvalidConfig::what() const throw() {
  return "Invalid Scope";
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/

STRING const &    Scopes::getScope() const {
  return scope_;
}

STRING const &    Scopes::getScopeArg() const {
  return scopeArg_;
}

VECVECSTR const &   Scopes::getLines() const {
  return lines_;
}

size_t const &    Scopes::getLineIndex() const {
  return lineIndex_;
}

size_t const &    Scopes::getLineArgIndex() const {
  return lineArgIndex_;
}

std::vector<MainScope> const &    Scopes::getScopes() const {
  return scopes_;
}

void    Scopes::setScopes(STRING filePath, VECVECSTR lines) {
  filePath_ = filePath;
  lines_ = lines;
}
