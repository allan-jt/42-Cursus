FROM debian:buster

ARG DOMAIN_NAME

RUN apt update -y && \
	apt install -y hugo git && \
    apt -y autoremove && \
    apt -y clean && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir -p /var/hugo/creed

WORKDIR /var/hugo/creed

RUN hugo new site . && \
	git clone https://github.com/LordMathis/hugo-theme-nix \
	themes/hugo-theme-nix

COPY ./conf/config.toml config.toml

COPY ./conf/creed.jpg /var/hugo/creed/static/

COPY ./conf/creed.jpg /var/hugo/creed/themes/hugo-theme-nix/static/

COPY ./conf/thoughts.md /var/hugo/creed/content/

RUN hugo

EXPOSE 1313

ENTRYPOINT hugo server --bind=0.0.0.0 --port=1313 \
	--appendPort=false --baseURL=https://${DOMAIN_NAME}/creed
