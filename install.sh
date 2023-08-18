#!/bin/bash

# Initialize Environment
. ./build/.env/env.sh

# Display Banner
banner

/bin/bash -c "make -j`nproc`"