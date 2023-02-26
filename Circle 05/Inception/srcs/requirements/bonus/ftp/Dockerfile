FROM debian:buster

ARG FTP_USER
ARG FTP_PASS

RUN apt update -y && \
	apt install -y vsftpd && \
    apt -y autoremove && \
    apt -y clean && \
    rm -rf /var/lib/apt/lists/*    

RUN adduser ${FTP_USER} && \
    echo "${FTP_USER}:${FTP_PASS}" | chpasswd && \
    usermod -a -G www-data ${FTP_USER}

RUN mkdir -p /var/run/vsftpd/empty

COPY ./conf/vsftpd.conf /etc/vsftpd.conf

RUN echo ${FTP_USER} > /etc/vsftpd.userlist

ENTRYPOINT ["vsftpd", "/etc/vsftpd.conf"]