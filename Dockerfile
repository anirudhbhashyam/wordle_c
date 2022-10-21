FROM gcc:latest

WORKDIR /app

COPY . /app

RUN ./pack.sh build

CMD ["./build/app"]