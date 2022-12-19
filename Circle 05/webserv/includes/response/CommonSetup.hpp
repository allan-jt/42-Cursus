/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/16 14:18:41                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef COMMONSETUP_HPP
# define COMMONSETUP_HPP

# include <iostream>
# include <string>
# include "../webserv.hpp"
# include "Container.hpp"
# include "ResponseHeader.hpp"

class CommonSetup
{

	private:
    Container   container_;

	public:

		CommonSetup(Container container);
		CommonSetup( CommonSetup const & src );
		~CommonSetup();

		CommonSetup &		operator=( CommonSetup const & rhs );

    void                setHeader();
    void                storeHeader();
    void                readFile();
    void                setStatus();
    void                storeFullString();
    void                trimBody(size_t method);
    
    Container const &   getContainer() const;

};

#endif /* ***************************************************** COMMONSETUP_H */