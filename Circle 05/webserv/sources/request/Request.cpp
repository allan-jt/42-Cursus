/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/19 14:49:37                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/request/Request.hpp"

/************************CANONICAL & OTHER CONSTRINGUCTORS************************/
Request::Request() {}

Request::Request(int clientFd) : clientFd_(clientFd), method_(OTHER_METHOD),
	URI_(EMPTY_STR), requestStatus_(INCOMPLETE), lineStatus_(INCOMPLETE),
	headerStatus_(INCOMPLETE), bodyStatus_(INCOMPLETE), chunkBytesToRead_(DEFAULT), 
	chunkStatus_(false), chunkCRLFRemoved_(true) {

	timing_.start();
	memset(&clientAddr_, DEFAULT, sizeof(clientAddr_));
	clientAddrLength_ = sizeof(clientAddr_);
	getsockname(clientFd_, &clientAddr_, &clientAddrLength_);
};

Request::Request(Request const &copy) {*this = copy;}

Request::~Request() {}

Request &Request::operator=(Request const &rhs) {
	if (this != &rhs) {
		clientFd_ = rhs.clientFd_;
		clientAddr_ = rhs.clientAddr_;
		clientAddrLength_ = rhs.clientAddrLength_;
		method_ = rhs.method_;
		URI_ = rhs.URI_;
		protocol_ = rhs.protocol_;
		hostName_ = rhs.hostName_;
		port_ = rhs.port_;
		headers_ = rhs.headers_;
		queries_ = rhs.queries_;
		body_ = rhs.body_;

		timing_ = rhs.timing_;
		code_ = rhs.code_;
		requestStatus_ = rhs.requestStatus_;
		buffer_ = rhs.buffer_;
		lineStatus_ = rhs.lineStatus_;
		headerStatus_ = rhs.headerStatus_;
		bodyStatus_ = rhs.bodyStatus_;
		chunkBytesToRead_ = rhs.chunkBytesToRead_;
	}
	return *this;
}

/*********************************MAIN FUNCTIONS********************************/
int	Request::recieve() {
	STRING content = getRawRequest_();

	if (content.empty()) {
		if (requestStatus_ == READ_ERROR)
			code_.setStatusCode(INTERNAL_SERVER_ERROR);
		if (requestStatus_ == EMPTY)
			requestStatus_ = FINISHED;
		stopTime();
		return requestStatus_;
	}

	buffer_ += content;
	if (parseRequestLine_() == COMPLETE
		&& parseRequestHeaders_() == COMPLETE
		&& parseRequestBody_() == COMPLETE)
		requestStatus_ = COMPLETE;
	if (requestStatus_ != INCOMPLETE)
		stopTime();

	return requestStatus_;
}

void	Request::startTime() {timing_.start();}

void	Request::stopTime() {timing_.stop();}

bool	Request::checkTimeOut() {
	if (getTime() <= DEFAULT_TIMEOUT)
		return false;
	code_.setStatusCode(REQUEST_TIMEOUT);
	requestStatus_ = PARSING_ERROR;
	return true;
}

int	Request::parseRequestLine_() {
	if (lineStatus_ == COMPLETE)
		return COMPLETE;
	if (buffer_.find(CRLF) == STRING::npos)
		return INCOMPLETE;

	STRING requestLine;
//	CRLF might precede request line (RFC 9112, Sec 2.2.)
	while (requestLine.empty()) {
		if (buffer_.empty())
			return INCOMPLETE;
		requestLine = tokenize_(buffer_, CRLF);
	}	
	if (!isValidRequestLine_(requestLine))
		return (requestStatus_ = PARSING_ERROR);
	
	storeMethod_(tokenize_(requestLine, SPACE));
	storeURI_(tokenize_(requestLine, SPACE));
	storeProtocol_(tokenize_(requestLine, SPACE));
	if (!isValidMethod_() || !isValidURI_() || !isValidProtocol_())
		return (requestStatus_ = PARSING_ERROR);

	return (lineStatus_ = COMPLETE);
}

int	Request::parseRequestHeaders_() {
	if (headerStatus_ == COMPLETE)
		return COMPLETE;
	size_t findStatus = buffer_.find(CRLF);
	if (findStatus == STRING::npos)
		return INCOMPLETE;

	while (findStatus != STRING::npos && findStatus > 0) {
		STRING headerLine = tokenize_(buffer_, CRLF);
		STRING key = tokenize_(headerLine, COLON);
		STRING value = headerLine;
		
		makeLowerCase_(key);
		if (!isValidRequestHeader_(key, value))
			return (requestStatus_ = PARSING_ERROR);
		headers_[key] = value;
		findStatus = buffer_.find(CRLF);
	}

	if (buffer_.find(CRLF) == 0) {
		headerStatus_ = COMPLETE;
		buffer_.erase(0, 2);
		if (!storeHost_())
			return (requestStatus_ = PARSING_ERROR);
	}

	return headerStatus_;
}

int	Request::parseRequestBody_() {
	if (bodyStatus_ == COMPLETE)
		return COMPLETE;

	if (!isBodyNeeded_()) {
		if (buffer_.empty())
			return (bodyStatus_ = COMPLETE);
		code_.setStatusCode(LENGTH_REQUIRED);
		return (requestStatus_ = PARSING_ERROR);
	}

	isBodyChunked_() ? dechunkBody_() : appendBufferToBody_();
	if (!isValidRequestBody_())
		return (requestStatus_ = PARSING_ERROR);

	return (bodyStatus_);
}

/************************************GETTERS***********************************/
int			const &Request::getClientFd() const {return clientFd_;}
sockaddr	const &Request::getClientAddr() const {return clientAddr_;}
socklen_t	const &Request::getClientAddrLenth() const {return clientAddrLength_;}
size_t		const &Request::getMethod() const {return method_;}
STRING		const &Request::getURI() const {return URI_;}
STRING		const &Request::getProtocol() const {return protocol_;}
STRING 		const &Request::getHostName() const {return hostName_;}
int			const &Request::getPort() const {return port_;}
STRING		const &Request::getQueryString() const {return queryString_;}
STRING		const &Request::getBody() const {return body_;}
std::map<STRING, STRING> const &Request::getAllHeaders() const {return headers_;}
std::map<STRING, STRING> const &Request::getQueries() const {return queries_;}

double 		Request::getTime() {return timing_.getCurTime();}
StatusCode 	const &Request::getStatusClass() const {return code_;}
int 		const &Request::getRequestStatus() const {return requestStatus_;}
STRING		const &Request::getBuffer() const {return buffer_;}
int			const &Request::getLineStatus() const {return lineStatus_;}
int			const &Request::getHeaderStatus() const {return headerStatus_;}
size_t		const &Request::getChunkBytesToRead() const {return chunkBytesToRead_;}

STRING	Request::getClientIP() const {
	STRING				IP;
	std::stringstream 	num;

	num << int(clientAddr_.sa_data[2] & 0xff);
	IP = num.str();
    for(int i = 3; i < 6; i++) {
		num.str(STRING());
		num << int(clientAddr_.sa_data[i] & 0xff);
		IP += "." + num.str();
	}

	return IP;
}

STRING	Request::getStringMethod() const {
	return (method_ == GET ? "GET" :
			method_ == HEAD ? "HEAD" :
			method_ == POST ? "POST" :
			method_ == PUT ? "PUT" :
			method_ == DELETE ? "DELETE" : "OTHER");
}

STRING	Request::getHeaderAt(STRING key) {
	makeLowerCase_(key);
	std::map<STRING, STRING>::iterator value = headers_.find(key);
	return (value == headers_.end() ? EMPTY_STR : value->second);
}