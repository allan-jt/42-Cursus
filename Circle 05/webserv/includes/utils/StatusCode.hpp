/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/19 14:48:40                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef STATUSCODE_HPP
#define STATUSCODE_HPP

#include "../webserv.hpp"

/* Info on status codes: https://www.rfc-editor.org/rfc/rfc9110#section-15 */

// Informational 1xx: The request was received, continuing process
#define CONTINUE				100
#define SWITCHING_PROTOCOLS		101

// Sucessful 2xx: The request was successfully received, understood, and accepted
#define OK						200
#define CREATED					201
#define ACCEPTED				202
#define NON_AUTHORITATIVE_INFO	203
#define NO_CONTENT				204
#define RESET_CONTENT			205
#define PARTIAL_CONTENT			206

// Redirection 3xx: Further action needs to be taken in order to complete the request
#define	MULTIPLE_CHOICES		300
#define	MOVED_PERMANENTLY		301
#define FOUND					302
#define	SEE_OTHER				303
#define NOT_MODIFIED			304
#define USE_PROXY				305
#define TEMPORARY_REDIRECT		307
#define PERMANENT_REDIRECT		308

// Client error 4xx: The request contains bad syntax or cannot be fulfilled
#define BAD_REQUEST				400
#define UNAUTHORIZED			401
#define FORBIDDEN				403
#define NOT_FOUND				404
#define METHOD_NOT_ALLOWED		405
#define NOT_ACCEPTABLE			406
#define PROXY_AUTH_REQUIRED		407
#define REQUEST_TIMEOUT			408
#define CONFLICT				409
#define GONE					410
#define LENGTH_REQUIRED			411
#define PRECONDITION_FAILED		412
#define CONTENT_TOO_LARGE		413
#define URI_TOO_LONG			414
#define UNSUPPORTED_MEDIA_TYPE	415
#define RANGE_NOT_SATISFIABLE	416
#define EXPECTATION_FAILED		417
#define MISDIRECTED_REQUEST		421
#define UNPROCESSABLE_CONTENT	422
#define UPGRADE_REQUIRED		426

// Server error 5xx: The server failed to fulfill an apparently valid request
#define INTERNAL_SERVER_ERROR	500
#define NOT_IMPLEMENTED			501
#define	BAD_GATEWAY				502
#define SERVICE_UNAVAILABLE		503
#define	GATEWAY_TIMEOUT			504
#define HTTP_VER_NOT_SUPPORTED	505

class StatusCode {
	private:
		std::map<int, STRING>	statusCodes_;
		int						code_;

	public:
		StatusCode();
		StatusCode(StatusCode const &rhs) {*this = rhs;};
		StatusCode &operator=(StatusCode const &rhs);

	//	Getters
		STRING	getStatusMessageAt(int code) const;
		int		getStatusCode() const {return code_;}
	
	//	Setter
		void	setStatusCode(int code);
};

#endif