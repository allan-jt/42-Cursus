/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/12/12 16:14:06                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/utils/Libft.hpp"

namespace ft {
	std::string    toString(int n) {
		std::stringstream ss;
		ss << n;
		return ss.str();
	}

	std::string    toString(size_t n) {
		std::stringstream ss;
		ss << n;
		return ss.str();
	}

	std::string    toString(long n) {
		std::stringstream ss;
		ss << n;
		return ss.str();
	}

	bool    isValidURI(std::string path, char permission) {
		struct stat s;
		if (!stat(path.c_str(),&s))
			return true;
		return ((permission == 'r' && s.st_mode & S_IRUSR)
				|| (permission == 'w' && s.st_mode & S_IWUSR)
				|| (permission == 'x' && s.st_mode & S_IXUSR));
	}

	bool    isDirectory(std::string path) {
		struct stat s;
		if (stat(path.c_str(),&s) == 0)
			if ( s.st_mode & S_IFDIR )
				return true;
		return false;
	}

	std::string    getFileContent(std::string path) {
		std::ifstream file;
		file.open(path.c_str());
		if (!file.is_open())
			return std::string();
		std::ostringstream sstream;
		sstream << file.rdbuf();
		file.close();
		return sstream.str();
	}

	long    getFileSize(std::string filename) {
		struct stat stat_buf;
		int rc = stat(filename.c_str(), &stat_buf);
		return rc == 0 ? stat_buf.st_size : -1;
	}

	std::string    getCurrentDateAndTime()  {
		time_t timetoday;
		time(&timetoday);
		std::string tmp(asctime(localtime(&timetoday)));
		return std::string(tmp.substr(0, tmp.length()-1));
	}

	bool    createFile(std::string filePath, std::string body, bool overwrite) {
		std::ofstream file;
		bool created = false;

		if (!ft::isValidURI(filePath, 0)) {
			file.open(filePath.c_str());
			created = true;
		}
		else if (!overwrite)
			file.open(filePath.c_str(), std::ios::app);
		else if (overwrite)
			file.open(filePath.c_str(), std::ios::trunc);

		file << body;
		file.close();
		return created;
	}

	bool    deleteFile(std::string filePath) {
		return std::remove(filePath.c_str()) == 0;
	}

  bool test_int(const char *s, int *int_result) {
    char *endptr;
    errno = 0;
    long n = strtol(s, &endptr, 0);
    if (errno == ERANGE) {
      return false;
    }

    #if LONG_MIN < INT_MIN || LONG_MAX > INT_MAX
    if (n < INT_MIN || n > INT_MAX) {
        return false;
    }
    #endif

    if (s == endptr) {
      return false;
    }

    while (isspace((unsigned char) *endptr)) {
      endptr++;
    }

    if (*endptr != '\0') {
      return false;
    }

    *int_result = (int) n;
    return true;
  }

}

/* ************************************************************************** */
