FROM debian:buster

ARG DOMAIN_NAME

RUN apt update -y && \
	apt install -y nginx openssl && \
    apt -y autoremove && \
    apt -y clean && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir /etc/nginx/ssl && \
	openssl req -x509 -newkey rsa:2048 -days 365 -nodes \
		-keyout /etc/nginx/ssl/certificate.key \
		-out /etc/nginx/ssl/certificate.crt \
		-subj "/C=AE/ST=AbuDhabi/O=Allan/CN=localhost"

COPY ./conf/default.conf /etc/nginx/sites-enabled/default

RUN mv /etc/nginx/fastcgi_params /etc/nginx/default_fastcgi_params

COPY ./conf/fastcgi_params /etc/nginx/fastcgi_params

EXPOSE 443

ENTRYPOINT ["nginx", "-g", "daemon off;"]