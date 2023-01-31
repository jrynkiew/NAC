#!/bin/bash
if [ "$WEB_BUILDER" = 1 ]
then
    cd /build/emsdk/
    . ./emsdk_env.sh
fi

cd /src
make