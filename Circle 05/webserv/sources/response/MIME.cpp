/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/10/26 10:36:12                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/response/MIME.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

MIME::MIME(STRING filePath) : filePath_(filePath) {
  size_t pos = filePath_.find_last_of(".") + 1;
  if (pos != STRING::npos) {
    extension_ = filePath_.substr(pos, filePath_.length());
    contentType_ = searchInMIMETypes();
  }
}

MIME::MIME( const MIME & src ) {
  *this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

MIME::~MIME() {
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

MIME &				MIME::operator=( MIME const & rhs ) {
	if ( this != &rhs ) {
    filePath_ = rhs.filePath_;
		extension_ = rhs.extension_;
		contentType_ = rhs.contentType_;
    contentTypeVal_ = rhs.contentTypeVal_;
	}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, MIME const & i ) {
  if (i.getContentType().empty())
    o << "contentType = " << "EMPTY";
	else
    o << "contentType = " << i.getContentType();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/


STRING    MIME::searchInMIMETypes() {
  STRING  contentTypeStr;

  try {
    FileParser parser(DEFAULT_MIME);
    std::vector<MainScope> scope = parser.getScopes("types");
    if (scope.size() != 1)
      throw Scopes::InvalidConfig();
    if (parser.findArg(scope[0].getElements(), extension_)){
      contentTypeStr = scope[0].getElements()[parser.getArgPos().first][0];
      contentTypeVal_ = scope[0].getElements()[parser.getArgPos().first][1];
    }

  } catch (const FileParser::InvalidFile& e) {
    return STRING();
  } catch (const Scopes::InvalidConfig& e) {
    return STRING();
  }

  return contentTypeStr;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

STRING const &    MIME::getContentType() const{
  return contentType_;
}

STRING const &    MIME::getContentTypeVal() const{
  return contentTypeVal_;
}

/* ************************************************************************** */
