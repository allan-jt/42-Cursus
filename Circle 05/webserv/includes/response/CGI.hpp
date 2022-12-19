/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/19 14:47:54                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef CGI_HPP
#define CGI_HPP

#include "../webserv.hpp"
#include <sstream>
#include <sys/wait.h>
#include "../../includes/request/Request.hpp"
#include "../../includes/response/MIME.hpp"
#include "../../includes/config/ConfigServer.hpp"

# define CGI_PATH "/cgi-bin/"

# define CONTENT_TYPE_CGI       "CONTENT_TYPE"
# define CONTENT_LENGTH_CGI     "CONTENT_LENGTH"
# define PATH_INFO_CGI          "PATH_INFO"
# define PATH_TRANSLATED_CGI    "PATH_TRANSLATED"
# define REMOTE_ADDR_CGI        "REMOTE_ADDR"
# define REQUEST_METHOD_CGI     "REQUEST_METHOD"
# define REQUEST_URI_CGI        "REQUEST_URI"
# define SCRIPT_NAME_CGI        "SCRIPT_NAME"
# define SERVER_NAME_CGI        "SERVER_NAME"
# define SERVER_PROTOCOL_CGI    "SERVER_PROTOCOL"
# define SERVER_PORT_CGI        "SERVER_PORT"
# define SERVER_SOFTWARE_CGI    "SERVER_SOFTWARE"
# define GATEWAY_INTERFACE_CGI  "GATEWAY_INTERFACE"
# define QUERY_STRING_CGI       "QUERY_STRING"
# define HTTP__CGI              "HTTP_"

class CGI {
    private:
        STRING                          fileContent_;
        STRING                          extention_;
        std::map<STRING, STRING>        env_;
        std::map<STRING, STRING>        cgiMap_;
        char                            **charEnv_;
        char                            *pathArgs_[3];
        STRING                          cgiPath_;
        STRING                          uri_;
        Request                         req_;
        int                             fdIn_[2];
        STRING                          body_;
        std::fstream                    openCgiFile_;
        FILE                            *fOut_;
        int                             fdOut_;
        pid_t                           pid_;
        int                             statusCode_;

        void        setEnvVariables(Request req);
        void        setCharEnv();
        void        setPathArgs();
        void        setFileContent();

        STRING      getFileType(STRING const &file);
        STRING      getFileContent();
        char**      getCharEnv();
        STRING      getCGIExe();
        void        removeExtraSlash(STRING &path);

    public:
        CGI();
        CGI(Request req, std::map<STRING, STRING> cgiMap,
            const STRING CgiPath, STRING extention);
        CGI(CGI const &copy);
        ~CGI();

        CGI             &operator=( CGI const &rhs);

        int             getReadFd();
        int             getWriteFd();

		    void			      setDefault(Request req, std::map<STRING, STRING> cgiMap,
                            const STRING CgiPath, STRING extention);
        int             initCGI();
        int             executeCGI();

        int             childProcess();
        int             parentProcess();
        STRING          readBody();

        STRING const &  getBody() const;
};

#endif
