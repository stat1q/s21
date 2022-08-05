FROM nginx
COPY ./minisrv.c /msrv/minisrv.c
COPY ./build_minisrv.sh /msrv/build_minisrv.sh
COPY ./nginx.conf /etc/nginx/nginx.conf

RUN apt-get update ; \
    apt-get install -y gcc \
    make \
    spawn-fcgi \
    libfcgi-dev ; \
    apt-get clean ; \
    rm -rf /var/lib/apt/lists/*

WORKDIR /msrv/
ENTRYPOINT ["sh", "./build_minisrv.sh"]
