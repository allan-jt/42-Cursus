FILE			= ./srcs/docker-compose.yml
DOCKER_CMD		= docker compose -f ${FILE}

NGINX_CNTNR		= nginx
MARIA_CNTNR		= mariadb
WRDPR_CNTNR		= wordpress
REDIS_CNTNR		= redis
FTPSR_CNTNR		= ftp-server
ADMNR_CNTNR		= adminer
WEBST_CNTNR		= website
ADVSR_CNTNR		= cadvisor

NGINX_IMAGE		= nginx:custom
MARIA_IMAGE		= mariadb:custom
WRDPR_IMAGE		= wordpress:custom
REDIS_IMAGE		= redis:custom
FTPSR_IMAGE		= ftp-server:custom
ADMNR_IMAGE		= adminer:custom
WEBST_IMAGE		= website:custom
ADVSR_IMAGE		= cadvisor:custom

NETWORK			= custom
WP_VOLUME 		= wordpress_data
DB_VOLUME 		= mariadb_data

VOLUME_DIR 		= /home/athekkep/data
WP_VOLUME_DIR	= ${VOLUME_DIR}/wordpress
DB_VOLUME_DIR	= ${VOLUME_DIR}/database

all: build up

build:
	${DOCKER_CMD} build

up:
	${DOCKER_CMD} up

down:
	${DOCKER_CMD} down

create_volumes:
	sudo mkdir -p ${WP_VOLUME_DIR} ${DB_VOLUME_DIR}

goin_nginx:
	docker exec -it ${NGINX_CNTNR} /bin/bash

goin_mariadb:
	docker exec -it ${MARIA_CNTNR} /bin/bash

goin_wordpress:
	docker exec -it ${WRDPR_CNTNR} /bin/bash

goin_redis:
	docker exec -it ${REDIS_CNTNR} /bin/bash

goin_ftp:
	docker exec -it ${FTPSR_CNTNR} /bin/bash

goin_adminer:
	docker exec -it ${ADMNR_CNTNR} /bin/bash

goin_website:
	docker exec -it ${WEBST_CNTNR} /bin/bash

goin_cadvisor:
	docker exec -it ${ADVSR_CNTNR} /bin/bash

clean:
	docker rm -f ${NGINX_CNTNR} ${MARIA_CNTNR} ${WRDPR_CNTNR} ${REDIS_CNTNR} ${FTPSR_CNTNR} ${ADMNR_CNTNR} ${WEBST_CNTNR} ${ADVSR_CNTNR}
	docker rmi -f ${NGINX_IMAGE} ${MARIA_IMAGE} ${WRDPR_IMAGE} ${REDIS_IMAGE} ${FTPSR_IMAGE} ${ADMNR_IMAGE} ${WEBST_IMAGE} ${ADVSR_IMAGE}
	sudo rm -rf ${WP_VOLUME_DIR}/* ${DB_VOLUME_DIR}/*
	docker volume rm -f ${WP_VOLUME} ${DB_VOLUME}
	if docker network inspect ${NETWORK} > /dev/null; then \
        docker network rm ${NETWORK}; \
    fi

re: clean all