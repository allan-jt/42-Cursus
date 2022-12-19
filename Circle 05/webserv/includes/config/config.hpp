/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/19 14:47:15                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef CONFIG_HPP
# define CONFIG_HPP

#include "ConfigServer.hpp"

# define MAIN_SCOPE     "server"
# define NESTED_SCOPE   "location"

class   Config {

    private:
        std::vector<ConfigServer *>     servers_;
        int                             workers_;
        VECVECSTR                       confValues_;
        std::vector<MainScope>          scopes_;

    public:
        Config();
        Config(const char* filePath);
        Config(Config const &copy);
        ~Config();

        // Parsing using File Parser class
        void        parser(STRING filePath);
        void        parseConfig();
        void        setConfigServ(std::vector<MainScope>::iterator &it, ConfigServer &serv);
        void        setServLocation(std::vector<MainScope>::iterator &it, ConfigServer &serv);

        Config      &operator=( Config const &rhs);

        std::vector<ConfigServer *> const &  getServers() const;

};

#endif
