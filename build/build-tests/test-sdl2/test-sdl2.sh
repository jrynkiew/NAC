#!/bin/bash

# Test SDL2 
mkdir -p /build/tests/test-sdl2 && cd "$_"
git clone https://github.com/jrynkiew/basic-cpp-sdl-project.git basic-cpp-sdl-project

# x64 Windows
cd /build/tests/test-sdl2/basic-cpp-sdl-project/
cmake -S . -B build -D CMAKE_TOOLCHAIN_FILE=/opt/mingw-w64-x86_64.cmake
cd build
make -j8
mkdir -p /build/tests/test-sdl2/x64
cp basic-cpp-sdl-project.exe /build/tests/test-sdl2/x64/basic-cpp-sdl-project-x64.exe
cd ..
rm -r build
cp /usr/x86_64-w64-mingw32/bin/SDL2.dll /build/tests/test-sdl2/x64/SDL2.dll

# x86 Windows
cd /build/tests/test-sdl2/basic-cpp-sdl-project/
cmake -S . -B build -D CMAKE_TOOLCHAIN_FILE=/opt/mingw-i686-w64.cmake
cd build
make -j8
mkdir -p /build/tests/test-sdl2/x86
cp basic-cpp-sdl-project.exe /build/tests/test-sdl2/x86/basic-cpp-sdl-project-x86.exe
cp /usr/i686-w64-mingw32/bin/SDL2.dll /build/tests/test-sdl2/x86/SDL2.dll

# Clear directory after tests
cd /build/tests
rm -r /build/tests/test-sdl2/basic-cpp-sdl-project

echo "Finished! Please check the debug files!"

