FROM debian:buster

ARG WP_CLI_SRC=https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
ARG WP_CLI_DOC=wp-cli.phar
ARG WP_FILE_SRC=https://wordpress.org/latest.tar.gz
ARG WP_FILE_DOC=latest.tar.gz

# Prerequisite for latest php packages
RUN apt update -y && \
	apt install -y \
		php php-fpm php-mysqli php-redis \
		wget mariadb-client sendmail gnupg2 && \
    apt -y autoremove && \
    apt -y clean && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir -p /run/php && mkdir -p /var/www/html

COPY ./conf/www.conf /etc/php/7.3/fpm/pool.d/www.conf

# Get Wordpress CLI
RUN wget ${WP_CLI_SRC} && \
	chmod +x ${WP_CLI_DOC} && \
	mv ${WP_CLI_DOC} /usr/local/bin/wp

# Get Wordpress	
WORKDIR /var/www/html

RUN wget ${WP_FILE_SRC} && \
	tar xzvf ${WP_FILE_DOC} --strip-components=1 && \
	rm -rf ${WP_FILE_DOC}

RUN chown -R www-data:www-data . && chmod -R 775 .

# Set up WP for entrypoint
EXPOSE 9000

COPY ./tools/entrypoint.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/entrypoint.sh

ENTRYPOINT ["entrypoint.sh"]