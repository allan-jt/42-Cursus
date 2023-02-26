FROM debian:buster

ARG ADMINER_SRC=https://github.com/vrana/adminer/releases/download/v4.8.1/adminer-4.8.1.php

RUN apt update -y && \
	apt install -y php php-fpm php-mysqli wget && \
    apt -y autoremove && \
    apt -y clean && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir -p /run/php && mkdir -p /var/www/html

COPY ./conf/www.conf /etc/php/7.3/fpm/pool.d/www.conf

RUN wget ${ADMINER_SRC} -O /var/www/html/adminer.php

RUN chown -R www-data:www-data /var/www/html && \
	chmod -R 775 /var/www/html

WORKDIR /var/www/html

EXPOSE 8080

ENTRYPOINT ["/usr/sbin/php-fpm7.3", "-R", "-F"]