/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/10 13:46:31                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef LOCATION_HPP
# define LOCATION_HPP

#include "../../includes/webserv.hpp"
#include "../../includes/config/ConfigExceptions.hpp"
#include "../../includes/utils/Libft.hpp"

class Location {
    private:
        std::vector<STRING>                         allowMethods_;
        std::vector<STRING>                         index_; // default file if request is directory; if empty, directory listing is on
        STRING                                      indexString_;
        std::pair<size_t, STRING>                   redirection_;
        STRING                                      root_;
        STRING                                      cgiPass_; // location to CGI executable
        bool                                        fileUpload_;
        bool                                        autoIndex_;
        size_t                                      clientBodyBufferSize_;
        std::map<size_t, STRING>                    errorPage_;
        size_t                                      clientMaxBodySize_;

    public:
        Location();
        Location(Location const & loc);
        Location    & operator=( Location const & rhs);
        ~Location();

        void    setAllowMethods(std::vector<STRING>::iterator &it, std::vector<STRING>::iterator end);
        void    setIndex(std::vector<STRING>::iterator &it, std::vector<STRING>::iterator end);
        void    setRedirection(std::vector<STRING>::iterator &it);
        void    setRoot(std::vector<STRING>::iterator &it);
        void    setCgiPass(std::vector<STRING>::iterator &it);
        void    setFileUpload(std::vector<STRING>::iterator &it);
        void    setAutoIndex(std::vector<STRING>::iterator &it);
        void    setClientBodyBufferSize(std::vector<STRING>::iterator &it);
        void    setDefault(std::map<size_t, STRING> errorPage, size_t clientMaxBody);
        bool    is_number(const std::string& s);

        // Response data
        void    setIndexString(STRING);

        std::vector<STRING> const &         getAllowMethods() const;
        std::vector<STRING> const &         getIndex() const;
        STRING const &                      getIndexString() const;
        std::pair<size_t, STRING> const &   getRedirections() const;
        STRING const &                      getRoot() const;
        STRING const &                      getCGIPass() const;
        bool const &                        getFileUpload() const;
        bool const &                        getAutoIndex() const;
        std::map<size_t, STRING> const &    getErrorPage() const;
        size_t const &                      getClientMaxBodySize() const;

};

#endif
