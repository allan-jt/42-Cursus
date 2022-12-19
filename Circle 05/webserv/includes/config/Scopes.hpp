/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnasldlksdfjl;kjas;dflkjasdflkjsadfhekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/26 12:36:34                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef SCOPES_HPP
# define SCOPES_HPP

# include <iostream>
# include <string>
# include "../webserv.hpp"
# include "MainScope.hpp"

# define CURARG lines_[lineIndex_][lineArgIndex_]

class Scopes
{

	private:
    STRING                  filePath_;
    STRING                  scope_;
    STRING                  scopeArg_;
    VECVECSTR               lines_;
    size_t                  lineIndex_;
    size_t                  lineArgIndex_;
    std::vector<MainScope>  scopes_;

    std::pair<VECVECSTR,
      std::vector<NestedScope> >   getScopeElements(STRING mainScopeName,
                                      STRING nestedScopeName, bool scopeArg);
    bool                           end();
    VECVECSTR                      storeScopeElements();
    std::vector<STRING>            storeElementsArgs();
    bool                           checkScopeStart(STRING scope, bool scopeArg);
    size_t                         checkSemicolon();
    void                           resetIndexes();
    bool                           move2Next();
    bool                           go2NextScope(STRING scope);
    bool                           isNestedScope();
    void                           printPos();
    STRING                         getCurArg();

	public:

		Scopes();
		Scopes(STRING filePath, VECVECSTR lines);
		Scopes( Scopes const & src );
		~Scopes();

    class InvalidConfig : public std::exception {
      public:
        virtual const char * what() const throw();
    };

		Scopes &		operator=( Scopes const & rhs );

    void  storeScopes(STRING mainScopeName, STRING nestedScopeName = STRING());

    // Getters
    STRING const &                    getScope() const;
    STRING const &                    getScopeArg() const;
    VECVECSTR const &                 getLines() const;
    size_t const &                    getLineIndex() const;
    size_t const &                    getLineArgIndex() const;
    std::vector<MainScope> const &    getScopes() const;
    void                              setScopes(STRING filePath, VECVECSTR lines);


};

std::ostream &			operator<<( std::ostream & o, Scopes const & i );
#endif /* ********************************************************** SCOPES_H */