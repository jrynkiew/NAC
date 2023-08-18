#!/bin/bash

export jrpc_beta_v2=$PWD
export http_code=0

function banner {
echo "     ____._____________________________  
    |    |\______   \______   \_   ___ \ 
    |    | |       _/|     ___/    \  \/ 
/\__|    | |    |   \|    |   \     \____
\________| |____|_  /|____|    \______  /
                  \/                  \/ "
}

export COMMAND="sleep infinity"

if [ "$BUILD_TARGET" = "web" ]
then
    export PWD_WEB=$PWD
    cd /build/emsdk/
    . ./emsdk_env.sh
    cd $PWD_WEB
fi