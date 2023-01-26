FROM ubuntu:23.04

WORKDIR /build

ARG CMAKE_VERSION=3.24.1
ARG GLFW_VERSION=3.3.8
ARG SDL_VERSION=2.26.2

ARG CROSS_PATH=/usr
ARG PKG_CONFIG_PATH=/usr/local/x86_64-w64-mingw32/lib/pkgconfig

SHELL [ "/bin/bash", "-c" ]

RUN set -ex \
    \
    && apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get upgrade --no-install-recommends -y \
    && DEBIAN_FRONTEND=noninteractive apt-get install --no-install-recommends -y \
        ca-certificates \
        libssl-dev \
        libglu1-mesa-dev \
        xorg-dev \
        wget \
        git \
        vim \
        curl \
        mingw-w64-i686-dev \
        mingw-w64-x86-64-dev \
        gcc-mingw-w64-i686 \
        gcc-mingw-w64-x86-64 \
        g++-mingw-w64-i686 \
        g++-mingw-w64-x86-64 \
        binutils-mingw-w64-i686 \
        binutils-mingw-w64-x86-64 \
        autotools-dev \
        build-essential \
        libtool \
        automake \
        pkg-config \
        python3 \
        default-jre \
    \
    && wget -q https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}.tar.gz -O - | tar -xz \
    && wget -q https://github.com/glfw/glfw/archive/refs/tags/${GLFW_VERSION}.tar.gz -O - | tar -xz \
    && wget -q https://github.com/libsdl-org/SDL/releases/download/release-${SDL_VERSION}/SDL2-devel-${SDL_VERSION}-mingw.tar.gz -O - | tar -xz \
    && wget -q https://gist.githubusercontent.com/jrynkiew/96b41216bd6078590aedd1ab8f0ae66b/raw/mingw-w64-x86_64.cmake -O /opt/mingw-w64-x86_64.cmake \
    && wget -q https://gist.githubusercontent.com/jrynkiew/96b41216bd6078590aedd1ab8f0ae66b/raw/mingw-i686-w64.cmake -O /opt/mingw-i686-w64.cmake \
    \
    && cd cmake-${CMAKE_VERSION} \
    && ./configure \
        --prefix=/usr/local \
        --parallel=`nproc` \
    && make -j`nproc` \
    && make install \
    && cd .. \
    \
    && git clone https://github.com/emscripten-core/emsdk.git emsdk \
    && cd emsdk \
    && ./emsdk install latest \
    && ./emsdk activate latest \
    && cd .. \
    \
    && cd glfw-${GLFW_VERSION} \
    && cmake -S . -B build -D CMAKE_INSTALL_PREFIX=/usr/x86_64-w64-mingw32/ -D CMAKE_TOOLCHAIN_FILE=/opt/mingw-w64-x86_64.cmake \
    && cd build \
    && make -j`nproc` \
    && make install \
    && cd ../ \
    && rm -r build \
    && cmake -S . -B build -D CMAKE_INSTALL_PREFIX=/usr/i686-w64-mingw32/ -D CMAKE_TOOLCHAIN_FILE=/opt/mingw-i686-w64.cmake \
    && cd build \
    && make -j`nproc` \
    && make install \
    && cd ../.. \
    \
    && ln -s /usr/x86_64-w64-mingw32/ /usr/local/x86_64-w64-mingw32 \
    && ln -s /usr/i686-w64-mingw32 /usr/local/i686-w64-mingw32 \
    && cd SDL2-${SDL_VERSION} \
    && make cross
