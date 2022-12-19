/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/26 12:04:49                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/config/NestedScope.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

NestedScope::NestedScope() {
}

NestedScope::NestedScope(VECVECSTR lines, STRING nestedScopeName, STRING arg)
	: elements_(lines), nestedScopeName_(nestedScopeName), arg_(arg) {
}

NestedScope::NestedScope( const NestedScope & src ) {
	*this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

NestedScope::~NestedScope() {
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

NestedScope &				NestedScope::operator=( NestedScope const & rhs )
{
	if ( this != &rhs ) {
		elements_ = rhs.elements_;
		nestedScopeName_ = rhs.nestedScopeName_;
		arg_ = rhs.arg_;
	}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, NestedScope const & i )
{
	o << "\t" << i.getNestedScopeName() << " " << i.getArg() << " {" << std::endl;

	VECVECSTR lines = i.getElements();
  for (std::vector<std::vector<STRING> >::iterator line = lines.begin();
    line != lines.end(); line++) {
    
    o << "\t\t";
    for (std::vector<STRING>::iterator arg = (*line).begin(); arg != (*line).end(); arg++)
      o << "|" << *arg << "| ";
    o << std::endl;
  }
	o << "\t}" << std::endl;
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/


/*
** --------------------------------- ACCESSOR ---------------------------------
*/

VECVECSTR const &		NestedScope::getElements() const {
  return elements_;
}

STRING const &		NestedScope::getNestedScopeName() const {
  return nestedScopeName_;
}

STRING const &		NestedScope::getArg() const {
  return arg_;
}

void		NestedScope::setElements(VECVECSTR const & elements) {
  elements_ = elements;
}

void		NestedScope::setNestedScopeName(STRING const & nestedScopeName) {
  nestedScopeName_ = nestedScopeName;
}

void		NestedScope::setArg(STRING const & arg) {
  arg_ = arg;
}


/* ************************************************************************** */