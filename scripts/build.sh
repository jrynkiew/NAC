#!/bin/bash
if [ "$BUILD_TARGET" = "web" ]
then
    #remove existing node_modules (if any)
    rm -rf /build/project/external/web3.js/node_modules/  

    #set up nvm
    cd /build/.nvm
    . ./nvm.sh

    #build web3.js
    cd /build/project/external/web3.js
    nvm use web3js
    node -v
    npm install
    npm run build

    #set up emscripten
    cd /build/emsdk/
    . ./emsdk_env.sh

    #build imgui.js
    cd /build/project/external/imgui-js
    nvm use imguijs
    node -v
    npm install
    npm install typescript -g
    npm install @types/emscripten -g
    make
    npm run-script build
    npm run-script dist

    #prebuild emscripten libraries
    embuilder build libpng
    embuilder build sdl2
    embuilder build sdl2_image
fi

cd /build/project/
/bin/bash -c "make clean"
/bin/bash -c "make all -j`nproc`"