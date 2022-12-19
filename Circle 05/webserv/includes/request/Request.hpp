/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/19 14:47:36                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "../utils/StatusCode.hpp"
#include "../utils/Timer.hpp"

// STATUS
#define FINISHED		2
#define COMPLETE		1
#define	INCOMPLETE		0
#define READ_ERROR		-1
#define PARSING_ERROR	-2

// HEADER KEYS
#define CONTENT_LENGTH	"content-length"
#define TRANSFR_ENCODE	"transfer-encoding"
#define HOST			"host"
#define CONNECTION		"connection"

// HEADER VALUES
#define CLOSE	"closed"

// LIMITS
#define MAX_URI_LENGTH		2047 	// https://stackoverflow.com/questions/417142/what-is-the-maximum-length-of-a-url-in-different-browsers
#define MAX_LINE_LENGTH		8000	// RFC 9112 Sec 3
#define MAX_CONTENT_LENGTH	1000000000

class	Request {
	private:
		int			clientFd_;
		sockaddr	clientAddr_;
		socklen_t	clientAddrLength_;
		size_t		method_;
		STRING		URI_;
    	STRING 		protocol_;
    	STRING		hostName_;
		int			port_;
		STRING		queryString_;
		STRING		body_;
		std::map<STRING, STRING>	headers_;
		std::map<STRING, STRING>	queries_;

	//	General methods/attributes
		Timer		timing_;
		StatusCode	code_;
		int			requestStatus_;
		STRING		buffer_;
		STRING		getRawRequest_();
		STRING		tokenize_(STRING &content, STRING delimiter);
		void		trimStart_(STRING &str);
		void		trimEnd_(STRING &str);
		void		replaceCharacters(STRING &str, char remove, char insert);
		void		makeLowerCase_(STRING &str);
		size_t		hexToDecimal(STRING hexString);
		std::vector<STRING>	splitStringWithDelimiter(STRING str, STRING delimiter);

	//	Request line methods/attributes
		int		lineStatus_;
		int		parseRequestLine_();
		bool	isValidRequestLine_(STRING &requestLine);
		bool	isValidMethod_();
		bool	isValidURI_();
		bool	isValidProtocol_();
		void	storeMethod_(STRING rawMethod);
		void	storeURI_(STRING rawURI);
		void	storeProtocol_(STRING rawProtocol);
		void	storeQueries_();
		void	adjustDirectories_(STRING &str);

	//	Request header methods/attributes
		int		headerStatus_;
		int		parseRequestHeaders_();
		bool	isValidRequestHeader_(STRING &key, STRING &value);
		bool	storeHost_();

	//	Request body methods/attributes
		int		bodyStatus_;
		size_t	chunkBytesToRead_;
		bool	chunkStatus_;
		bool	chunkCRLFRemoved_;
		int		parseRequestBody_();
		bool	isBodyNeeded_();
		bool	isBodyChunked_();
		bool	isValidRequestBody_();
		void	validateNonChunkBody_();
		void	validateChunkBody_();
		void	dechunkBody_();
		bool	removeCRLFinChunk_();
		void	appendChunkToBody_();
		void	appendBufferToBody_();

	public:
	//	Main function
		int		recieve();
		void	startTime();
		void	stopTime();
		bool	checkTimeOut();

	//	Getters
		int			const &getClientFd() const;
		sockaddr	const &getClientAddr() const;
		socklen_t	const &getClientAddrLenth() const;
		STRING		getClientIP() const;
		size_t		const &getMethod() const;
		STRING		getStringMethod() const;
		STRING		const &getURI() const;
		STRING		const &getProtocol() const;
		STRING 		const &getHostName() const;
		int			const &getPort() const;
		STRING		getHeaderAt(STRING key);
		STRING		const &getQueryString() const;
		STRING		const &getBody() const;
		std::map<STRING, STRING>	const &getAllHeaders() const;
		std::map<STRING, STRING>	const &getQueries() const;

		double 		getTime();
		StatusCode 	const &getStatusClass() const;
		int 		const &getRequestStatus() const;
		STRING		const &getBuffer() const;
		int			const &getLineStatus() const;
		int			const &getHeaderStatus() const;
		size_t		const &getChunkBytesToRead() const;

	//	Canonical & other constructors
		Request();
		Request(int clientFd);
		Request(Request const &copy);
		~Request();
		Request &operator=(Request const &rhs);
};

#endif
