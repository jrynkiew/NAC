#!/bin/bash

# Environment variables
export red=`tput setaf 1`
export purple=`tput setaf 93`
export blue=`tput setaf 21`
export green=`tput setaf 2`
export gold=`tput setaf 214`
export reset=`tput sgr0`

export jrpc_beta_v2=$PWD

if [ -x "$(command -v git)" ]; then
    echo "${gold}git version${reset}"
    git --version
else
    echo "${gold}Installing git${reset}"
    sudo apt-get install git
fi

if [ -x "$(command -v docker)" ]; then
    echo "${gold}docker version${reset}"
    docker --version
else
    echo "${gold}Installing docker${reset}"
    sudo apt-get install docker
fi

if [ -x "$(command -v docker-compose)" ]; then
    echo "${gold}docker-compose version${reset}"
    docker-compose --version
else
    echo "${gold}Installing docker-compose${reset}"
    sudo apt-get install docker-compose
fi

echo -e "${gold}Initializing git repo and dependencies${reset}"
git submodule update --init --recursive

function banner {
echo "     ____._____________________________  
    |    |\______   \______   \_   ___ \ 
    |    | |       _/|     ___/    \  \/ 
/\__|    | |    |   \|    |   \     \____
\________| |____|_  /|____|    \______  /
                  \/                  \/ "
}

export COMMAND="sleep infinity"
