#!/bin/bash
if [ "$BUILD_TARGET" = "web" ]
then
    cd /build/emsdk/
    . ./emsdk_env.sh
fi

cd /build/project/
/bin/bash -c "make clean"
/bin/bash -c "make -j`nproc`"