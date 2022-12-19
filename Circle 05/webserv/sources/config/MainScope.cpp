/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/26 12:05:07                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/config/MainScope.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

MainScope::MainScope() {
}

MainScope::MainScope(std::pair<VECVECSTR, std::vector<NestedScope> > content,
  std::pair<STRING, STRING> scopeNames)
  : elements_(content.first), nestedScopes_(content.second),
  mainScopeName_(scopeNames.first), nestedScopeName_(scopeNames.second) {
}

MainScope::MainScope( const MainScope & src ) {
  *this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

MainScope::~MainScope() {
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

MainScope &				MainScope::operator=( MainScope const & rhs ) {
	if ( this != &rhs ) {
    elements_ = rhs.elements_;
    nestedScopes_ = rhs.nestedScopes_;
    mainScopeName_ = rhs.mainScopeName_;
    nestedScopeName_ = rhs.nestedScopeName_;
	}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, MainScope const & i )
{
  o << i.getMainScopeName() << " {" << std::endl;

  // print root elements
	VECVECSTR lines = i.getElements();
  for (std::vector<std::vector<STRING> >::iterator line = lines.begin();
    line != lines.end(); line++) {
    
    o << "\t";
    for (std::vector<STRING>::iterator arg = (*line).begin(); arg != (*line).end(); arg++)
      o << "|" << *arg << "| ";
    o << std::endl;
  }

  // print Nested Scopes
  std::vector<NestedScope> nestedScopes = i.getNestedScopes();
  for (std::vector<NestedScope>::iterator nested = nestedScopes.begin();
    nested != nestedScopes.end(); nested++)
      o << *nested;

  o << "}" << std::endl;
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/



/*
** --------------------------------- ACCESSOR ---------------------------------
*/

STRING const &   MainScope::getMainScopeName() const {
  return mainScopeName_;
}

STRING const &   MainScope::getNestedScopeName() const {
  return nestedScopeName_;
}

VECVECSTR const &   MainScope::getElements() const {
  return elements_;
}

std::vector<NestedScope> const &    MainScope::getNestedScopes() const {
  return nestedScopes_;
}

void                MainScope::setElements(VECVECSTR const & elements) {
  elements_ = elements;
}

void    MainScope::setNestedScopes(std::vector<NestedScope> const & nestedScopes) {
  nestedScopes_ = nestedScopes;
}

void    MainScope::setMainScopeName(STRING const & mainScopeName) {
  mainScopeName_ = mainScopeName;
}

void    MainScope::setNestedScopeName(STRING const & nestedScopeName) {
  nestedScopeName_ = nestedScopeName;
}

/* ************************************************************************** */