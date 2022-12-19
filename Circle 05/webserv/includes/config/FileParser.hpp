/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/25 10:38:35                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef FILEPARSER_HPP
# define FILEPARSER_HPP

# include <iostream>
# include <string>
# include "../webserv.hpp"
# include "ConfigExceptions.hpp"
# include "Scopes.hpp"

# define INVALID_FILE "Invalid File"

/*
** * File Parser is a class that parses a file and store all content in VECVECSTR.
** * It also uses Scopes class to parse the VECVECSTR elements, handle errors and 
** * return content a structured format related to conf file.
*/
class FileParser
{
	private:
    Scopes                    scopesObj_;
    std::ifstream             file_;
    VECVECSTR                 lines_;
    std::pair<size_t, size_t> argPos_;
    STRING                    filePath_;

    void                              storeFileContent();
    std::vector<STRING>               storeLineArgs(STRING line);
	
  public:

		FileParser(STRING fileName);
		FileParser( FileParser const & src );
		~FileParser();

    class InvalidFile : public std::exception {
      public:
        virtual const char * what() const throw();
    };

		FileParser &		operator=( FileParser const & rhs );

    // Getters
    VECVECSTR const &                 getLines() const;
    std::pair<size_t, size_t> const & getArgPos() const; // return the position <line, arg> after searching with findArg()

    // methods
    void                              printVec(VECVECSTR lines); // print elements of any VECVECSTR
    void                              printScopes(); // print all the scopes' elements with their nested scopes if exist
    std::vector<MainScope>            getScopes(STRING scopeName, STRING nestedScopeName = STRING()); // get a vector of scopes
    bool                              findArg(VECVECSTR lines, STRING str); // search for any element in the file and return true if exist.
                                                                            //You can use getArgPOS() to get the exact position of element in the file

};

std::ostream &			operator<<( std::ostream & o, FileParser const & i ); // print all elements in file

#endif /* ****************************************************** FILEPARSER_H */