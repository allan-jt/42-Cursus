/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/12/15 16:58:05                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef CONFIGEXCEPTIONS_HPP
#define CONFIGEXCEPTIONS_HPP

#include "../../includes/webserv.hpp"

# define InvalidConfigArg_Msg               "Error: Invalid Config argument."
# define InvalidConfigException_Msg         "Error: Invalid Config File."
# define InvalidHost_Msg                    "Error: Invalid 'Host' argument."
# define InvalidPort_Msg                    "Error: Invalid 'Port' argument."
# define InvalidServerName_Msg              "Error: Invalid 'Server Name' argument."
# define InvalidErrorPage_Msg               "Error: Invalid 'Error Page' argument."
# define InvalidClientMaxBodySize_Msg       "Error: Invalid 'Client Max Body Size' argument."
# define InvalidAllowMethods_Msg            "Error: Invalid 'Allow Methods' argument."
# define InvalidIndex_Msg                   "Error: Invalid 'Index' argument."
# define InvalidRedirection_Msg             "Error: Invalid 'Redirection' argument."
# define InvalidRoot_Msg                    "Error: Invalid 'Root' argument."
# define InvalidCgiPass_Msg                 "Error: Invalid 'CGI' argument."
# define InvalidFileUpload_Msg              "Error: Invalid 'File Upload' argument."
# define InvalidAutoIndex_Msg               "Error: Invalid 'Auto Index' argument."
# define InvalidClientBodyBufferSize_Msg    "Error: Invalid 'Client Body Buffer Size' argument."

class ConfigExceptions {

    public:
        ConfigExceptions();
        ~ConfigExceptions();

        class InvalidConfigArg: public std::exception {
            public:
                const char* what() const throw();
        };

        class InvalidConfigException: public std::exception {
            public:
                const char* what() const throw();
        };

        class InvalidHost : public std::exception {
            public:
                const char * what() const throw();
        };

        class InvalidPort : public std::exception {
            public:
                const char * what() const throw();
        };

        class InvalidServerName : public std::exception {
            public:
                const char * what() const throw();
        };

        class InvalidErrorPage : public std::exception {
            public:
                const char * what() const throw();
        };

        class InvalidClientMaxBodySize : public std::exception {
            public:
                const char * what() const throw();
        };

        class InvalidAllowMethods : public std::exception {
            public:
                const char * what() const throw();
        };

        class InvalidIndex : public std::exception {
            public:
                const char * what() const throw();
        };

        class InvalidRedirection : public std::exception {
            public:
                const char * what() const throw();
        };

        class InvalidRoot : public std::exception {
            public:
                const char * what() const throw();
        };

        class InvalidCgiPass : public std::exception {
            public:
                const char * what() const throw();
        };

        class InvalidFileUpload : public std::exception {
            public:
              const char * what() const throw();
        };

        class InvalidAutoIndex : public std::exception {
            public:
                const char * what() const throw();
        };

        class InvalidClientBodyBufferSize : public std::exception {
            public:
                const char * what() const throw();
        };

};

#endif
