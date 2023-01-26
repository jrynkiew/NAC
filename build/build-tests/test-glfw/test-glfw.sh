#!/bin/sh

# x64 Windows
cd /build/glfw-${GLFW_VERSION}
rm -r ./build
cmake -S . -B build -D CMAKE_INSTALL_PREFIX=/usr/x86_64-w64-mingw32/ -D CMAKE_TOOLCHAIN_FILE=/opt/mingw-w64-x86_64.cmake
cd build
make -j`nproc`
mkdir -p /build/tests/test-glfw/x64
cp ./tests/*.exe /build/tests/test-glfw/x64/
cd ..
rm -r build

# x86 Windows
cmake -S . -B build -D CMAKE_INSTALL_PREFIX=/usr/i686-w64-mingw32/ -D CMAKE_TOOLCHAIN_FILE=/opt/mingw-i686-w64.cmake
cd build
make -j`nproc`
mkdir -p /build/tests/test-glfw/x86
cp ./tests/*.exe /build/tests/test-glfw/x86/
cd ..
rm -r build