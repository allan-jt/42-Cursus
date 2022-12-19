/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/10/02 11:29:10                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */


#include "../../includes/response/DirectoryListing.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

DirectoryListing::DirectoryListing(STRING path, STRING pagesPath)
  : path_(path), pagesPath_(pagesPath),
  htmlFile_( pagesPath_ + "directoryListing.html"), elementsPos_(0) {
  
  path_.insert(0, "./");
  storeDirectoryFilesNames();
}

DirectoryListing::DirectoryListing( const DirectoryListing & src ) {
  *this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

DirectoryListing::~DirectoryListing() {
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

DirectoryListing &    DirectoryListing::operator=( DirectoryListing const & rhs ) {
	if ( this != &rhs ) {
		path_ = rhs.path_;
		body_ = rhs.body_;
	}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, DirectoryListing const & i ) {
	o << "Value = " << i.getPath();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

void    DirectoryListing::storeDirectoryFilesNames() {
  DIR *dir; struct dirent *diread;
  std::vector<STRING> files;

  if ((dir = opendir(path_.c_str())) != NULL) {
    while ((diread = readdir(dir)) != NULL) {
      if (STRING(diread->d_name) != ".")
        files.push_back(diread->d_name);
    }
    closedir (dir);
  }
  else {
    perror ("opendir");
    return ;
  }
  storeHtmlBody(files);
  body_ = html_;
}

void    DirectoryListing::storeHtmlBody(std::vector<STRING> vec) {
  if (!ft::isValidURI(htmlFile_, 'r'))
    return ;
  html_ = ft::getFileContent(htmlFile_);
  if (html_.empty())
    return ;
  STRING  keyStr("class=\"container\">\n");
  elementsPos_ = html_.find(keyStr);
  if (elementsPos_ == STRING::npos)
    return ;
  elementsPos_ += keyStr.length();

  for (std::vector<STRING>::reverse_iterator file = vec.rbegin(); file != vec.rend(); file++)
    html_.insert(elementsPos_, storeHtmlElement(file));
}

STRING    DirectoryListing::storeHtmlElement(std::vector<STRING>::reverse_iterator & file) {
  STRING  element;
  element += "\n\t\t<a class=\"element\" href=\"";
  element += *file;
  if (ft::isDirectory(path_ + *file))
    element += "/";
  element += "\">";
  element += *file;
  element += "<span>";
  if (ft::isDirectory(path_ + *file))
    element += "-";
  else {
    long size = ft::getFileSize(path_ + *file);
    element += size >= 0 ? ft::toString(size) : "!";
    element += "B";
  }
  element += "</span>";
  element += "</a>\n";
  return element;
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/

STRING const &    DirectoryListing::getPath() const {
  return path_;
}

STRING const &    DirectoryListing::getbody() const {
  return body_;
}

/* ************************************************************************** */