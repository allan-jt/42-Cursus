FROM debian:buster

RUN apt update -y && \
    apt install -y wget && \
    apt -y autoremove && \
    apt -y clean && \
    rm -rf /var/lib/apt/lists/*

RUN wget https://github.com/google/cadvisor/releases/download/v0.41.0/cadvisor -o /usr/bin/cadvisor && \
    chmod +x ./cadvisor

EXPOSE 8081

ENTRYPOINT ["./cadvisor", "-listen_ip=0.0.0.0", "-port=8081", \
    "-url_base_prefix=/cadvisor"]