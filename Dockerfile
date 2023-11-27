FROM ubuntu:22.04

WORKDIR /ws

RUN apt update \
    && apt upgrade -y\
    && apt install -y\
    cmake \
    ninja-build \
    clang \
    git \
    libudev-dev \
    libopenal-dev \
    libvorbis-dev \
    libflac-dev \
    libx11-dev \
    libxcursor-dev \
    libxrandr-dev \
    libfreetype-dev \
    libopengl-dev \
    libglx-dev \
    libgl1-mesa-dev

ENV CC=clang
ENV CXX=clang++
ENV BRANCH=master

RUN git clone https://github.com/wojciechmadry/Kulki.git \
    && cd Kulki \
    && git checkout ${BRANCH} \
    && git submodule init \
    && git submodule update \
    && mkdir -p build \
    && cd build \
    && cmake -GNinja ../ \
    && ninja

