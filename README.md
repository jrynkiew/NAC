

![NAC](https://user-images.githubusercontent.com/63042547/215357605-72fe88a0-68ee-468e-90f0-fee1ff3b96ed.png)

# NAC
&nbsp;
New Age Computing LLC
<pre>
Jenkins + Jenkins SSH Agents + Docker = cross-compiling platform
</pre>
This project is designed to streamline testing multi-architecture builds of cross-platform projects.

Current support includes C++, C, OpenGL cross platform builds for Windows x32, Windows x64, Web, Linux x64
You will get Linux, Windows, and Emscripten Web executables as a result of a successful build.

## Requirements
- Docker
- Docker-Compose
- WSL2 Linux Containers or Linux Ubuntu (or similar)

## Run 
Windows host:
```sh .\install.sh``` 
Linux host:
```./install.sh``` [^1] [^2] [^3] [^4]

## Build
execute `sh install.sh` 

This script will start the Docker stack defined in the docker-compose `build\docker\docker-compose.yaml` script. This script will initialise Jenkins with the `build\jenkins\casc.yaml` Configuration-as-Code configuration file. This file contains the intial DSL Job definition, and SSH Slave agent specification for all the Docker build containers. 

Upon launching Jenkins, the script will then launch each Docker builder, with the entrypoint.sh script contents, which defines the ssh keys and starts the SSH server.

Jenkins slave agents are configured in such a way, that they continuously try to connect to the slave agents, so the moment the SSH server is up on the docker slaves, the Jenkins node will connect using the pre-defined `nac` user, using the private key in the `build\ssh-keys` folder. The SSH servers and connections are configured to be passwordless for the `nac` user between all Containers of the Docker stack.

## Debug
You can execute command `docker exec -it jrpc-[container]-builder /bin/bash`, so that's `docker exec -it jrpc-windows-builder /bin/bash` for example, to enter into an individual ssh builder agent container.

To test SSH connections between Containers, first open into bash on any given Container.
 `docker exec -it jrpc-windows64-builder /bin/bash`
 Now log into the `nac` user, for example `su nac` and `ssh nac@jrpc-web-builder`, or a one liner: `exec /usr/local/bin/gosu nac ssh nac@jrpc-web-builder`
- `id_ed25519` and `id_ed25519.pub` are the predefined keys. Using them, you login using ssh without using any passwords, but only for the `nac` user.

## Output
The output exe will be in the generated folder, for each build node name. So the windows builder will build it's output to `NAC\generated\windows`, while  the linux builder will build it's output to `NAC\generated\linux`

## Extra Info
Docker data directory needs to have the ssh-keys directory, with a shared key for all containers, like so
build/docker/ssh-keys.
`config` file needs to contain this:
```Host *
    User nac
    StrictHostKeyChecking no
    IdentityFile /keys/id_ed25519.pub
```

So summarizing, the contents should be 
```build/docker/ssh-keys/
config
id_ed25519
id_ed25519.pub
```

Please follow the appendixes for instructions and the below attached pictures for additional assistance.

[^1]: you need to set any configuration environmental variables required for your Makefiles, or any other scripts required at build time for that matter, in the Jenkins slave agent specification in `build\jenkins\casc.yaml`

[^2]: After first initial run of install.sh, you will need to log in to Jenkins. The pre-defined credentials are in the `docker-compose.yaml` file. Defaults are set to `U: admin` `P: admin`

[^3]: After initial Jenkins installation, if the Agents don't connect to Jenkins, open a command line, and run the command ```docker exec -it jrpc-[container]-builder /bin/bash``` in each of the required containers. Check the ssh connection. If you want, you can create a new Jenkins agent, and connect manually.
Jenkins agents have a string to execute a java program in their Agent configuration page if they are disconnected. Run this on your Container, for example `docker exec -it jrpc-windows-builder /bin/bash` and paste in the line you see in Jenkins, for example ```java -jar agent.jar -jnlpUrl http://jenkins:8080/manage/computer/Windows%2Dbuilder/jenkins-agent.jnlp -secret 8dc0f6a11068790fcd60d0958fda8f3e3b172637fa35da31bf7dc0f1a9ec7063 -workDir "/build/jenkins/"```
Execute each of those strings on each of the containers your wish to manually connect.

[^4]: the default Pipelines are defined in the casc.yaml file. You can create your own at any time. In the future there will be support for at-runtime *.groovy file detection and importing.

<p align="left">
<img src="https://user-images.githubusercontent.com/63042547/215356555-a29e78c9-8197-462a-8e73-fbaf86af9b1b.gif" width=20% height=20%>
</p>
