/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/26 12:00:56                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef MAINSCOPE_HPP
# define MAINSCOPE_HPP

# include <iostream>
# include <string>
# include "../webserv.hpp"
# include "NestedScope.hpp"

class MainScope
{

	private:
		VECVECSTR                   elements_;
		std::vector<NestedScope>    nestedScopes_;
		STRING											mainScopeName_;
		STRING											nestedScopeName_;

	public:
		MainScope();
		MainScope(std::pair<VECVECSTR, std::vector<NestedScope> > content,
			std::pair<STRING, STRING> scopeNames);
		MainScope( MainScope const & src );
		~MainScope();

		MainScope &		operator=( MainScope const & rhs );

		// Getters
    STRING const &		   								getMainScopeName() const;
    STRING const &		   								getNestedScopeName() const;
    VECVECSTR const &   								getElements() const;
    std::vector<NestedScope> const &    getNestedScopes() const;

		// setters
    void                setElements(VECVECSTR const & elements);
    void                setNestedScopes(std::vector<NestedScope> const & nestedScopes);
    void                setMainScopeName(STRING const & mainScopeName);
    void                setNestedScopeName(STRING const & nestedScopeName);

};

std::ostream &			operator<<( std::ostream & o, MainScope const & i );

#endif /* ******************************************************* MAINSCOPE_H */