FROM debian:buster

ARG SLEEP_TIME
ARG MYSQL_NAME
ARG MYSQL_USER
ARG MYSQL_PASSWORD
ARG MYSQL_ROOT_PASSWORD

RUN apt update -y && \
	apt install procps mariadb-server -y && \
    apt -y autoremove && \
    apt -y clean && \
    rm -rf /var/lib/apt/lists/*

# Adjust the mysql configuration to listen to 0.0.0.0:3306
COPY ./conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf
RUN chmod o-w /etc/mysql/mariadb.conf.d/50-server.cnf

# Run mysql and create database along with users
RUN service mysql start && sleep ${SLEEP_TIME} && \
	mysql -e "CREATE DATABASE IF NOT EXISTS ${MYSQL_NAME}; \
	CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}'; \
	GRANT ALL PRIVILEGES ON ${MYSQL_NAME}.* TO '${MYSQL_USER}'@'%'; \
	UPDATE mysql.user SET host='%' WHERE user='root'; \
	ALTER USER 'root'@'%' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}'; \
	FLUSH PRIVILEGES;"

EXPOSE 3306

ENTRYPOINT [ "mysqld_safe" ]