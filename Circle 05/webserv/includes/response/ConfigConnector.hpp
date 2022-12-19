/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/16 11:44:41                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef CONFIGCONNECTOR_HPP
# define CONFIGCONNECTOR_HPP

# include <iostream>
# include <string>
# include "../webserv.hpp"
# include "../config/ConfigServer.hpp"
# include "../config/Location.hpp"
# include "ResponseUtils.hpp"

class ConfigConnector
{

	private:
    typedef std::map<STRING, Location>     LocationMap;

    STRING          uri_;
    STRING          orgUri_;
    STRING          filePath_;
    ResponseUtils   utils_;
    Location        configData_;
    ConfigServer    configServer_;

	public:
		ConfigConnector(STRING uri, ConfigServer configServer);
		ConfigConnector( ConfigConnector const & src );
		~ConfigConnector();

		ConfigConnector &		operator=( ConfigConnector const & rhs );

    STRING const &    getUri() const;
    STRING const &    getFilePath() const;
    Location const &  getConfigData() const;

    STRING            setConfigIndex(STRING filePath, std::vector<STRING> vec);
    void              compareURIWithLocations(STRING uri, bool & found);
    void              storeLocationParameters(LocationMap::iterator & it);
    void              checkURIWithConfig();


};

#endif /* *************************************************** CONFIGCONNECTOR_HPP */