# NAC

## Requirements
- Docker
- Docker-Compose
- WSL2 Linux Containers or Linux Ubuntu (or similar)

## Run 
```./install.sh``` [^1]

## Contents of the Container
CMAKE_VERSION = 3.24.1
GLFW_VERSION = 3.3.8
SDL_VERSION = 2.26.2
mingw-w64-i686-dev
mingw-w64-x86-64-dev
emsdk

[^1]: After first initial run of install.sh, you will need to log in to Jenkins, and set up the admin password. After initial Jenkins installation, go to the Agents in Jenkins, and copy the secret string.
Quit (Ctrl+C) the program end edit build/jenkins/start-agent.sh initialization secret string with the proper one. This is a temporary step, will be fixed in the future.