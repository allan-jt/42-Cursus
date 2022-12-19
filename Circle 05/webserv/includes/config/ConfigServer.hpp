/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/19 14:47:21                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef CONFIGSERVER_HPP
# define CONFIGSERVER_HPP

#include "../webserv.hpp"
#include "Location.hpp"
#include "ConfigExceptions.hpp"
#include "FileParser.hpp"

// Root Directives
# define DIR_LISTEN         "listen"
# define DIR_PORT           "port"
# define DIR_ERROR_PAGE     "error_page"
# define DIR_SERVER_NAME    "server_name"
# define DIR_CGI            "cgi"

// Location Directives
# define DIR_METHODS                "methods"
# define DIR_INDEX                  "index"
# define DIR_CLIENT_MAX_BODY_SIZE   "client_max_body_size"
# define DIR_AUTOINDEX              "autoindex"
# define DIR_CGI_PASS               "cgi_pass"
# define DIR_FILE_UPLOAD            "file_upload"
# define DIR_REDIRECTION            "redirection"
# define DIR_ROOT                   "root"

class ConfigServer {

    private:
        typedef std::map<STRING, Location>          LocationMap;

        STRING                                      host_;
        std::vector<int>                            port_;
        STRING                                      serverName_;
        std::map<size_t, STRING>                    errorPage_;
        size_t                                      clientMaxBodySize_;
        std::map<STRING, STRING>                    cgi_;
        LocationMap                                 locations_;
        ConfigExceptions                            exceptions_;

        std::map<STRING, void (ConfigServer::*)
            (std::vector<STRING>::iterator &)>      rootDirectives_;
        std::map<STRING, void (Location::*)
            (std::vector<STRING>::iterator &)>      locationDirectives_;
        std::map<STRING, void(Location::*)
            (std::vector<STRING>::iterator &,
            std::vector<STRING>::iterator)>         locationDirectivesVars_;

    public:
        ConfigServer();
        ConfigServer(ConfigServer const &copy);
        ConfigServer    &operator=( ConfigServer const &rhs);
        ~ConfigServer();

        void                                parseConfig(VECVECSTR::iterator &it,
                                                VECVECSTR::iterator &end);
        bool                                is_number(const std::string& s);
        void                                setupRootDirectives();
        void                                setupLocationDirectives();

        // Getters
        STRING const &                      getHost() const;
        std::vector<int> const &            getPort() const;
        STRING const &                      getServerName() const;
        std::map<size_t, STRING> const &    getErrorPage() const;
        size_t const &                      getClientMaxBodySize() const;
        std::map<STRING, STRING> const &    getCGI() const;
        LocationMap &                       getLocations();

        // Setters
        void                                setHost(std::vector<STRING>::iterator &it);
        void                                setPort(std::vector<STRING>::iterator &it);
        void                                setServerName(std::vector<STRING>::iterator &it);
        void                                setErrorPage(std::vector<STRING>::iterator &it);
        void                                setClientMaxBodySize(std::vector<STRING>::iterator &it);
        void                                setCGI(std::vector<STRING>::iterator &it);
        void                                setLocations(VECVECSTR::iterator &it,
                                                VECVECSTR::iterator &end, STRING dirlocation);


};

#endif
