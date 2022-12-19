/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/26 12:00:50                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef NESTEDSCOPE_HPP
# define NESTEDSCOPE_HPP

# include <iostream>
# include <string>
# include "../webserv.hpp"

class NestedScope
{

	private:
    VECVECSTR                   elements_;
		STRING											nestedScopeName_;
		STRING											arg_;

	public:

		NestedScope();
		NestedScope(VECVECSTR lines, STRING nestedScopeName, STRING arg);
		NestedScope( NestedScope const & src );
		~NestedScope();

		NestedScope &		operator=( NestedScope const & rhs );

    STRING const &		  getNestedScopeName() const;
    STRING const &		  getArg() const;
    VECVECSTR const &   getElements() const;

		void                setNestedScopeName(STRING const & nestedScopeName);
		void                setArg(STRING const & arg);
		void                setElements(VECVECSTR const & elements);

};

std::ostream &			operator<<( std::ostream & o, NestedScope const & i );

#endif /* ***************************************************** NESTEDSCOPE_H */