/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/12/12 16:14:01                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef LIBFTCPP_HPP
# define LIBFTCPP_HPP

# include <iostream>
# include <sstream>
# include <string>
# include <fstream>
# include <sys/stat.h>
# include <cstdlib>
# include <map>
# include <vector>


namespace ft {
	std::string    	toString(int n);
	std::string    	toString(size_t n);
	std::string    	toString(long n);
	bool    			 	isValidURI(std::string uri, char permission);
	bool    			 	isDirectory(std::string path);
	std::string			getFileContent(std::string path);
	long    			 	getFileSize(std::string filename);
	std::string			getCurrentDateAndTime();
	bool    				createFile(std::string filePath, std::string body, bool overwrite);
	bool						deleteFile(std::string filePath);
  bool            test_int(const char *s, int *int_result);
  void            intializeFdData();

  template<typename T>
  bool checkVectorDuplicates(const std::vector<T>& values) {
    for (typename std::vector<T>::const_iterator it = values.begin(); it != values.end(); ++it) {
      typename std::vector<T>::const_iterator next_occurrence = std::find(it + 1, values.end(), *it);

      if (next_occurrence != values.end()) {
        return (true);
      }
    }
    return (false);
  }

  template<typename T, typename U>
  bool checkMapDuplicate(const std::map<T, U>& values, T key) {
    for (typename std::map<T, U>::const_iterator it = values.begin(); it != values.end(); ++it) {
      if (it->first == key) {
        return (true);
      }
    }
    return (false);
  }
}

#endif
/* ************************************************************************** */
