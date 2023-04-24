#!/bin/bash
if [ "$BUILD_TARGET" = "web" ]
then
    #remove existing node_modules (if any)
    rm -rf /build/project/external/web3.js/node_modules/  

    #set up nvm
    cd /build/.nvm
    . ./nvm.sh

    # #build web3.js
    # cd /build/project/external/web3.js
    # node -v
    # npm install
    # npm run build

    #set up emscripten
    cd /build/emsdk/
    . ./emsdk_env.sh

    #prebuild emscripten libraries
    embuilder build libpng
    embuilder build sdl2
    embuilder build sdl2_image
fi

cd /build/project/
/bin/bash -c "make clean"
/bin/bash -c "make all -j`nproc`"