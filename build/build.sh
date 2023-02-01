#!/bin/bash
if [ "$BUILD_TARGET" = "web" ]
then
    cd /build/emsdk/
    . ./emsdk_env.sh
fi

cd /src
make