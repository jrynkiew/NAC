#!/bin/bash
if [ "$BUILD_TARGET" = "web" ]
then
    cd /build/emsdk/
    . ./emsdk_env.sh
fi

cd /build/project/
/bin/bash -c "make clean"
/bin/bash -c "make all -j`nproc`"

# if [ "$BUILD_TARGET" = "web" ]
# then
# sed -i 's|index.js|/index.js|' /build/project/generated/web/index.html
# fi