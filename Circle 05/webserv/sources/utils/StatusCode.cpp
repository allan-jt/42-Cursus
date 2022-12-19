/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/19 14:50:44                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/utils/StatusCode.hpp"

StatusCode::StatusCode() : code_(OK) {
//	Informational 1xx
	statusCodes_[CONTINUE] = "Continue";
	statusCodes_[SWITCHING_PROTOCOLS] = "Switching Protocols";

//	Successful 2xx
	statusCodes_[OK] = "OK";
	statusCodes_[CREATED] = "Created";
	statusCodes_[ACCEPTED] = "Accepted";
	statusCodes_[NON_AUTHORITATIVE_INFO] = "Non-Authoritative Information";
	statusCodes_[NO_CONTENT] = "No Content";
	statusCodes_[RESET_CONTENT] = "Reset Content";
	statusCodes_[PARTIAL_CONTENT] = "Partial Content";

//	Redirection 3xx
	statusCodes_[MULTIPLE_CHOICES] = "Multiple Choices";
	statusCodes_[MOVED_PERMANENTLY] = "Moved Permanently";
	statusCodes_[FOUND] = "Found";
	statusCodes_[SEE_OTHER] = "See Other";
	statusCodes_[NOT_MODIFIED] = "Not Modified";
	statusCodes_[USE_PROXY] = "Use Proxy";
	statusCodes_[TEMPORARY_REDIRECT] = "Temporary Redirect";
	statusCodes_[PERMANENT_REDIRECT] = "Permanent Redirect";

//	Client Error 4xx
	statusCodes_[BAD_REQUEST] = "Bad Request";
	statusCodes_[UNAUTHORIZED] = "Unauthorized";
	statusCodes_[FORBIDDEN] = "Forbidden";
	statusCodes_[NOT_FOUND] = "Not Found";
	statusCodes_[METHOD_NOT_ALLOWED] = "Method Not Allowed";
	statusCodes_[NOT_ACCEPTABLE] = "Not Acceptable";
	statusCodes_[PROXY_AUTH_REQUIRED] = "Proxy Authentication Required";
	statusCodes_[REQUEST_TIMEOUT] = "Request Timeout";
	statusCodes_[CONFLICT] = "Conflict";
	statusCodes_[GONE] = "Gone";
	statusCodes_[LENGTH_REQUIRED] = "Length Required";
	statusCodes_[PRECONDITION_FAILED] = "Precondition Failed";
	statusCodes_[CONTENT_TOO_LARGE] = "Payload too large";
	statusCodes_[URI_TOO_LONG] = "URI Too Long";
	statusCodes_[UNSUPPORTED_MEDIA_TYPE] = "Unsupported Media Type";
	statusCodes_[RANGE_NOT_SATISFIABLE] = "Range Not Satisfiable";
	statusCodes_[EXPECTATION_FAILED] = "Expectation failed";
	statusCodes_[MISDIRECTED_REQUEST] = "Misredirected Request";
	statusCodes_[UNPROCESSABLE_CONTENT] = "Unprocessable Content";
	statusCodes_[UPGRADE_REQUIRED] = "Upgrade Required";

//	Server Error 5xx
	statusCodes_[INTERNAL_SERVER_ERROR] = "Internal Server Error";
	statusCodes_[NOT_IMPLEMENTED] = "Not Implemented";
	statusCodes_[BAD_GATEWAY] = "Bad Gateway";
	statusCodes_[SERVICE_UNAVAILABLE] = "Service Unavailable";
	statusCodes_[GATEWAY_TIMEOUT] = "Gateway Timeout";
	statusCodes_[HTTP_VER_NOT_SUPPORTED] = "HTTP Version Not Supported";
}

StatusCode &StatusCode::operator=(StatusCode const &rhs) {
	if (this != &rhs) {
		statusCodes_ = rhs.statusCodes_;
		code_ = rhs.code_;
	}
	return *this;
}

void	StatusCode::setStatusCode(int code) {
	if (!((code >= 200 && code <= 206) || (code >= 300 && code <= 308 && code != 306) 
		|| (code >= 500 && code <= 505) || (code >= 400 && code <= 417 && code != 402) 
		|| code == 100 || code == 101 || code == 421 || code == 422 || code == 426))
		throw std::out_of_range("Invalid status code");
	code_ = code;
}

STRING	StatusCode::getStatusMessageAt(int code) const {
	try {
		return statusCodes_.at(code);
	} catch (std::exception &s) {
		return "";
	}
}