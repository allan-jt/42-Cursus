/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/19 14:49:44                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/request/Request.hpp"

/************************************GENERAL***********************************/
STRING	Request::getRawRequest_() {
	char	buffer[DEFAULT_READ_BUFFER];
	int		flags = DEFAULT, bytesRead;

	bytesRead = recv(clientFd_, buffer, DEFAULT_READ_BUFFER - 1, flags);
	if (bytesRead <= EMPTY) {
		requestStatus_ = bytesRead;
		return EMPTY_STR;
	}

	buffer[bytesRead] = '\0';
	return (STRING(buffer));
}

// Returns the STRING upto the delimiter, and removes it from content
STRING	Request::tokenize_(STRING &content, STRING delimiter) {
	size_t	positionOfDelimiter;
	STRING	tokenizedContent;

	if ((positionOfDelimiter = content.find(delimiter)) == STRING::npos)
		positionOfDelimiter = content.length();
	tokenizedContent = content.substr(0, positionOfDelimiter);
	content.erase(0, tokenizedContent.length() + delimiter.length());

	return tokenizedContent;
}

std::vector<STRING>	Request::splitStringWithDelimiter(STRING str, STRING delim) {
	std::vector<STRING>	tokenizedStr;
	size_t				start = 0, index;

	while ((index = str.find(delim, start)) != STRING::npos) {
		tokenizedStr.push_back(str.substr(start, index - start + 1));
		start = index + 1;
	}
	if (start < str.length())
		tokenizedStr.push_back(str.substr(start));

	return tokenizedStr;
}

void	Request::trimStart_(STRING &str) {
	size_t start;

	for (start = 0; start < str.length() && isspace(str[start]); start++);
	str = str.erase(0, start);
}

void	Request::trimEnd_(STRING &str) {
	int	end, endPoint = str.length() - 1;

	for (end = endPoint; end >= 0 && isspace(str[end]); end--);
	if (end == endPoint)
		return;
	str = str.erase(end + 1, str.length() - end + 1);
}

void	Request::replaceCharacters(STRING &str, char remove, char insert) {
	for (size_t i = 0; i < str.length(); i++)
		if (str[i] == remove)
			str[i] = insert;
}

void	Request::makeLowerCase_(STRING &str) {
	size_t strLength = str.length();

	for (size_t i = 0; i < strLength; i++)
		str[i] = (char) tolower(str[i]);
}

size_t	Request::hexToDecimal(STRING  hexString) {
	std::stringstream 	stream(hexString);
	size_t				decimalValue;

	stream >> std::hex >> decimalValue;
	return decimalValue;
}

/**************************************LINE************************************/
bool	Request::isValidRequestLine_(STRING &requestLine) {
	int		numberOfElements = 0;
	bool	space = true;

	if (requestLine.length() > MAX_LINE_LENGTH) {
		code_.setStatusCode(BAD_REQUEST);
		return false;
	}
	
	// RFC 9112, Sec 3: single sp delimiter & three elements
	for (size_t i = 0; i < requestLine.length(); i++) {
		if (!isspace(requestLine[i])) {
			numberOfElements += space;
			space = false;
			continue;
		}
		if (requestLine[i] != ' ' || space || !i || numberOfElements == 3) {
			code_.setStatusCode(BAD_REQUEST);
			break;
		}
		space = true;
	}

	return (code_.getStatusCode() == OK);
}

bool	Request::isValidMethod_() {
	// RFC 9110, Sec 9: 501 for methods not implmented
	if (method_ == OTHER_METHOD)
		code_.setStatusCode(NOT_IMPLEMENTED);

	return (code_.getStatusCode() == OK);
}

bool	Request::isValidURI_() {
	// RFC 9112, Sec 3.2.1: URI must be in origin form
	if (URI_.empty() || URI_[0] != '/')
		code_.setStatusCode(BAD_REQUEST);
	else if (URI_.length() > MAX_URI_LENGTH)
		code_.setStatusCode(URI_TOO_LONG);
	else
		adjustDirectories_(URI_);

	return (code_.getStatusCode() == OK);
}

bool	Request::isValidProtocol_() {
	if (protocol_ != HTTP_ONE && protocol_ != HTTP_ONE_ONE)
		code_.setStatusCode(HTTP_VER_NOT_SUPPORTED);

	return (code_.getStatusCode() == OK);
}

void	Request::storeMethod_(STRING rawMethod) {
	method_ = rawMethod == "GET" 	? 	GET
			: rawMethod == "POST" 	? 	POST
			: rawMethod == "DELETE" ? 	DELETE
			: rawMethod == "HEAD" 	? 	HEAD
			: rawMethod == "PUT" 	? 	PUT
			: 							OTHER_METHOD;
}

void	Request::storeURI_(STRING rawURI) {
	URI_ = tokenize_(rawURI, "#");
	storeQueries_();
}

void	Request::storeProtocol_(STRING rawProtocol) {
	protocol_ = rawProtocol;
}

void	Request::storeQueries_() {
	size_t index = URI_.find('?');
	if (index == STRING::npos)
		return;

	STRING queries = URI_.substr(index + 1);
	queryString_ = queries;
	URI_.erase(index);
	while(!queries.empty()) {
		STRING val = tokenize_(queries, "&");
		STRING key = tokenize_(val, "=");

		if (val.find('\\') != STRING::npos
			|| val.find('/') != STRING::npos)
			adjustDirectories_(val = "/" + val);
		queries_[key] = val;
	}
}

void	Request::adjustDirectories_(STRING &str) {
	std::vector<STRING>	tokenizedStr;
	STRING				curDir = "./";
	STRING				prevDir = "../";
	STRING				singleDir = "/";

	replaceCharacters(str, '\\', singleDir[0]);
	tokenizedStr = splitStringWithDelimiter(str, singleDir);

	for (size_t i = 1; i < tokenizedStr.size(); i++) {
		if (tokenizedStr[i] == curDir || tokenizedStr[i] == singleDir) {
			tokenizedStr.erase(tokenizedStr.begin() + i--);
		} else if (i > 1 && tokenizedStr[i] == prevDir) {
			tokenizedStr.erase(tokenizedStr.begin() + i - 1,
				tokenizedStr.begin() + i + 1);
			i -= 2;
		}
	}

	str.clear();
	for(size_t i = 0; i < tokenizedStr.size(); i++)
		str += tokenizedStr[i];
	if (tokenizedStr[0] != singleDir)
		code_.setStatusCode(BAD_REQUEST);
}

/*************************************HEADER***********************************/
bool	Request::isValidRequestHeader_(STRING &key, STRING &value) {
	trimStart_(key);
	trimStart_(value);
	trimEnd_(value);
	if (key.empty() || value.empty() || isspace(key[key.length() - 1]))
		code_.setStatusCode(BAD_REQUEST);

	return (code_.getStatusCode() == OK);
}

bool	Request::storeHost_() {
	STRING host = getHeaderAt(HOST);
	if (host.empty()) {
		code_.setStatusCode(BAD_REQUEST);
		return false;
	}

	hostName_ = host.find(COLON) != STRING::npos ?
		tokenize_(host, COLON) : host;
	port_ = atoi(host.c_str());
	return true;
}

/**************************************BODY************************************/
bool	Request::isBodyNeeded_() {
	return (!getHeaderAt(TRANSFR_ENCODE).empty()
		|| !getHeaderAt(CONTENT_LENGTH).empty());
}

bool	Request::isBodyChunked_() {
	return (getHeaderAt(TRANSFR_ENCODE).find("chunked") != STRING::npos);
}

bool	Request::isValidRequestBody_() {
	if (code_.getStatusCode() != OK)
		return false;
	if (body_.size() > MAX_CONTENT_LENGTH) {
		code_.setStatusCode(CONTENT_TOO_LARGE);
		return false;
	}

	isBodyChunked_() ? validateChunkBody_() : validateNonChunkBody_();
	return (code_.getStatusCode() == OK);
}

void	Request::validateNonChunkBody_() {
	STRING contentLength = getHeaderAt(CONTENT_LENGTH);
	long int maxContentLength = atol(contentLength.c_str());
	long int bodyLength = body_.length();
	
	if (bodyLength > maxContentLength) {
		code_.setStatusCode(BAD_REQUEST);
	} else if (bodyLength == maxContentLength)
		bodyStatus_ = COMPLETE;
}

void	Request::validateChunkBody_() {
	if (chunkStatus_ == INCOMPLETE
		|| buffer_.find(CRLF) == STRING::npos)
		return;

	if (buffer_ != CRLF) {
		code_.setStatusCode(BAD_REQUEST);
		bodyStatus_ = PARSING_ERROR;
	} else
		bodyStatus_ = COMPLETE;
}

void	Request::dechunkBody_() {
	while (!buffer_.empty() && chunkStatus_ == INCOMPLETE) {
		if (chunkBytesToRead_ != EMPTY && chunkCRLFRemoved_) {
			appendChunkToBody_();
			continue;
		} else if (buffer_.find(CRLF) == STRING::npos
			|| !removeCRLFinChunk_())
			break;

		STRING line = tokenize_(buffer_, CRLF);
		STRING hexValue = tokenize_(line, ";");
		if (!line.empty() || hexValue.empty()) {
			code_.setStatusCode(BAD_REQUEST);
			break;
		}
		if ((chunkBytesToRead_ = hexToDecimal(hexValue)) == EMPTY)
			chunkStatus_ = COMPLETE;
	}
}

bool	Request::removeCRLFinChunk_() {
	size_t	sizeOfCRLF = 2;
	if (chunkCRLFRemoved_)
		return true;
	if (buffer_.length() < sizeOfCRLF)
		return false;

	if (buffer_.find(CRLF) == 0) {
		buffer_.erase(0, sizeOfCRLF);
		chunkCRLFRemoved_ = true;
		return buffer_.find(CRLF) != STRING::npos;
	}
//	Recieved something other than CRLF
	chunkStatus_ = COMPLETE;
	code_.setStatusCode(BAD_REQUEST);
	return false;
}

void	Request::appendChunkToBody_() {
	size_t 	bufferLength = buffer_.length();

	if (bufferLength < chunkBytesToRead_) {
		appendBufferToBody_();
		chunkBytesToRead_ -= bufferLength;
		return;
	}

	body_ += buffer_.substr(0, chunkBytesToRead_);
	buffer_.erase(0, chunkBytesToRead_);
	chunkBytesToRead_ = EMPTY;
	chunkCRLFRemoved_ = false;
}

void	Request::appendBufferToBody_() {
	body_ += buffer_;
	buffer_.clear();
}