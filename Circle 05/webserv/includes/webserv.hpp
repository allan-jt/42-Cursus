/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/19 14:48:54                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

// Colors
# define GREEN    "\033[38;5;46m"
# define WHITE    "\033[1;37m"
# define BLUE     "\033[1;36m"
# define YELLOW   "\033[1;33m"
# define RED      "\033[1;31m"
# define PURPLE   "\033[1;35m"
# define RESET    "\033[m"

// Methods
#define	OTHER_METHOD    0
#define HEAD            1
#define GET             2
#define POST            3
#define PUT             4
#define DELETE          5

// Log
# if LOG
  #define LOG 1
# else
  #define LOG 0
# endif

// Socket buffers (R: sysctl net.ipv4.tcp_rmem | W: sysctl net.ipv4.tcp_wmem)
#define MAX_READ_BUFFER         6291456
#define DEFAULT_READ_BUFFER     131072
#define	MIN_READ_BUFFER         4096
#define	MAX_WRITE_BUFFER        4194304
#define DEFAULT_WRITE_BUFFER    16384
#define MIN_WRITE_BUFFER        4096

// Defaults
#define EMPTY                 0
#define DEFAULT               0
#define DEFAULT_PORT          8080
#define	DEFAULT_IP            "0.0.0.0"
#define DEFAULT_CONFIG        "config_files/default.conf"
#define DEFAULT_MIME          "config_files/mime.types"
#define DEFAULT_TIMEOUT       60
#define DEFAULTROOT           "www/"
#define DEFAULTINDEX          "index.html"
#define DEFAULTPAGES          "pages/"
#define DEFAULT_ERROR_PAGE    "error.html"
#define DEFAULT_LOG_DIR       "logs/"
#define DEFAULT_LOG_FILE      "HostToast.log"
#define DEFAULT_DIRLIST_FILE  "directoryListing.html"

// Delimiters in request/response
#define CRLF        "\r\n"
#define EMPTY_STR   ""
#define SPACE       " "
#define NEWLINE     "\n"
#define KEYVAL      ": " 		// seperates key from value ("Connection: keep-alive")
#define COLON       ":"
#define SEPERATOR   "\r\n\r\n"	// separates headers from body

// Miscellaneous
#define HTTP_ONE        "HTTP/1.0"
#define HTTP_ONE_ONE    "HTTP/1.1"
#define HOST_TOAST      "HostToast/1.0"
#define VALID_CGI       "CGI/1.1"
#define STRING          std::string
#define MESSAGE_LENGTH  66

//	General C++ headers
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <iterator>
#include <stdexcept>
#include <ctime>
#include <algorithm>

//	General C headers
#include <unistd.h>
#include <csignal>
#include <stdio.h>
#include <unistd.h>

//	Webserv headers
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <poll.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <dirent.h>

// custom
#include "utils/Libft.hpp"


// Types
typedef std::vector<std::vector<STRING> >    VECVECSTR;

#endif
