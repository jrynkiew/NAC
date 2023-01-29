# NAC
New Age Computing llc

This project is designed to streamline testing multi-architecture builds of imgui based projects.

You will get Linux x64, Windows x32, and Emscripten Web executables as a result of a successful build.

## Requirements
- Docker
- Docker-Compose
- WSL2 Linux Containers or Linux Ubuntu (or similar)

## Run 
```./install.sh``` [^1] [^2] [^3]

## Build
Once you have set up Jenkins, connected all nodes to your Jenkins server, and configured your pipeline, all you need to do is run the Jeknins pipeline to build the solution. 

The output exe will be in the root solution directory, and the generated build files will be in the generated folder

[^1]: After first initial run of install.sh, you will need to log in to Jenkins, and set up the admin password. During the initial installation, choose "Install Recommended Plugins", and make sure to set the address of the Jenkins server to either "server" or "jenkins", like `http://jenkins:8080/` 

[^2]: After initial Jenkins installation, go to the Agents section in Jenkins, and set up new agents, one for each - Web, Linux and Windows.
Each Node in Jenkins must have the build directory set to `/build/jenkins/`, and an environment variable representing it's destination, for example for jrpc-linux-builder you need to set LINUX_BUILDER=1 as the environmental variable.
Open three new command lines, and run the command ```docker exec -it jrpc-[container]-builder /bin/bash``` in each of them, where the container can be any of linux, windows, or web.
After that, Jenkins will give you a string to execute a java program to run on your node. For example ```java -jar agent.jar -jnlpUrl http://jenkins:8080/manage/computer/Linux%2Dbuilder/jenkins-agent.jnlp -secret 8dc0f6a11068790fcd60d0958fda8f3e3b172637fa35da31bf7dc0f1a9ec7063 -workDir "/build/jenkins/"```
Execute each of those strings on each of the containers.

[^3]: Lastly, create a new pipeline, and copy the contents of build/jenkins/pipeline.groovy into the pipeline section. Note, that you will have to modify the line ```agent { label 'Windows-builder' }``` to correspond to each of your nodes you created, each according to their own label you set.  
Quit (Ctrl+C) the program end edit build/jenkins/start-agent.sh initialization secret string with the proper one. This is a temporary step, will be fixed in the future.