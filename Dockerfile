FROM ubuntu:22.04

WORKDIR /ws

RUN apt update \
    && apt upgrade -y\
    && apt install -y\
    libsfml-dev \
    cmake \
    ninja-build \
    clang \
    git

ENV CC=clang
ENV CXX=clang++
ENV BRANCH=fix_resolution

RUN git clone https://github.com/wojciechmadry/Kulki.git \
    && cd Kulki \
    && git checkout ${BRANCH} \
    && git submodule init \
    && git submodule update \
    && mkdir -p build \
    && cd build \
    && cmake -GNinja ../ \
    && ninja

