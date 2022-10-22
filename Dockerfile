FROM gcc:latest

COPY . /usr/app

WORKDIR /usr/app

RUN ./pack.sh build

CMD [ "./app" ]