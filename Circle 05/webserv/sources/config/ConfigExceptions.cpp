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

#include "../../includes/config/ConfigExceptions.hpp"

ConfigExceptions::ConfigExceptions() {
}

ConfigExceptions::~ConfigExceptions() { }

const char* ConfigExceptions::InvalidConfigArg::what() const throw() {
    return InvalidConfigArg_Msg;
}

const char* ConfigExceptions::InvalidConfigException::what() const throw() {
    return InvalidConfigException_Msg;
}

const char* ConfigExceptions::InvalidHost::what() const throw() {
    return InvalidHost_Msg;
}

const char* ConfigExceptions::InvalidPort::what() const throw() {
    return InvalidPort_Msg;
}

const char* ConfigExceptions::InvalidServerName::what() const throw() {
    return InvalidServerName_Msg;
}

const char* ConfigExceptions::InvalidErrorPage::what() const throw() {
    return InvalidErrorPage_Msg;
}

const char* ConfigExceptions::InvalidClientMaxBodySize::what() const throw() {
    return InvalidClientMaxBodySize_Msg;
}

const char* ConfigExceptions::InvalidAllowMethods::what() const throw() {
    return InvalidAllowMethods_Msg;
}

const char* ConfigExceptions::InvalidIndex::what() const throw() {
    return InvalidIndex_Msg;
}

const char* ConfigExceptions::InvalidRedirection::what() const throw() {
    return InvalidRedirection_Msg;
}

const char* ConfigExceptions::InvalidRoot::what() const throw() {
    return InvalidRoot_Msg;
}

const char* ConfigExceptions::InvalidCgiPass::what() const throw() {
    return InvalidCgiPass_Msg;
}

const char* ConfigExceptions::InvalidFileUpload::what() const throw() {
    return InvalidFileUpload_Msg;
}

const char* ConfigExceptions::InvalidAutoIndex::what() const throw() {
    return InvalidAutoIndex_Msg;
}

const char* ConfigExceptions::InvalidClientBodyBufferSize::what() const throw() {
    return InvalidClientBodyBufferSize_Msg;
}
