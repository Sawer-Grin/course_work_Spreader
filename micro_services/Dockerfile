FROM gcc:latest as build

WORKDIR /gtest_build

RUN apt-get update  && \
    apt-get install -y \
        build-essential \
        libboost-dev \
        libboost-thread-dev \
        libboost-chrono-dev \
        libboost-program-options-dev \
        libpq-dev \
        zlib1g-dev \
        libpqxx-dev \
        libpqxx-6.4 \
        cmake make \
        postgresql

ADD micro_services/src /app/src

RUN mkdir -p /usr/include/zipper
COPY micro_services/sub_libraries/lib/* /usr/lib/
COPY micro_services/sub_libraries/include/zipper /usr/include/zipper

WORKDIR /app/build
RUN cmake ../src && cmake --build .

FROM ubuntu:latest
RUN groupadd -r sample && useradd -r -g sample sample
USER root

RUN apt-get update && apt-get install -y \
        libpqxx-dev \
        libboost-thread-dev \
        libpqxx-6.4 \
        gcc \
        libstdc++6 \
        libboost-chrono-dev \
        zlib1g-dev \
        zlib1g

RUN apt-get install -y python3

COPY micro_services/sub_libraries/lib/* /usr/lib/x86_64-linux-gnu/

USER sample

WORKDIR /app
COPY --from=build /app/build/micro_service .

RUN mkdir -p uploads/
RUN mkdir -p temp/
COPY micro_services/secrets/* .
# RUN chmod +x ./prepare_script.sh

CMD ["./prepare_script.sh"]
# ENTRYPOINT ["tail", "-f", "/dev/null"]
