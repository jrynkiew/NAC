#!/bin/bash
if [ "$WEB_BUILDER" = 1 ]
then
    cd /build/emsdk/
    . ./emsdk_env.sh
fi

sh ./generate-token.sh
sh ./start-agent.sh

cd /src
make