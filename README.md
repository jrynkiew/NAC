# NAC
New Age Computing LLC
![NAC](https://user-images.githubusercontent.com/63042547/215334795-b302b1ad-217e-49cc-b339-1eafd7171ff9.png)

This project is designed to streamline testing multi-architecture builds of imgui based projects.

You will get Linux x64, Windows x32, and Emscripten Web executables as a result of a successful build.

## Requirements
- Docker
- Docker-Compose
- WSL2 Linux Containers or Linux Ubuntu (or similar)

## Run 
```./install.sh``` [^1] [^2] [^3] [^4]

## Build
Once you have set up Jenkins, connected all nodes to your Jenkins server, and configured your pipeline, all you need to do is run the Jeknins pipeline to build the solution. 

The output exe will be in the root solution directory, and the generated build files will be in the generated folder

## Extra Info
Please follow the appendixes for instructions and the below attached pictures for additional assistance.

[^1]: Upon launching the installation script, you will see command line output from Jenkins - you need to find the secret password from Jenkins in it, and go to `http://localhost:8080/` in your browser window to continue the installation. See pictures below:

![Jenkins--1](https://user-images.githubusercontent.com/63042547/215334738-74a6aaf4-06f3-4297-a1a9-fd7997e9bfd9.png)

![Jenkins-0](https://user-images.githubusercontent.com/63042547/215334760-34e9f4cf-a1d9-4d36-b7ff-b71f04efcf65.png)

![Jenkins-1](https://user-images.githubusercontent.com/63042547/215334781-b5242cce-cbbc-413f-a691-04715b5605a0.png)

![Jenkins-2](https://user-images.githubusercontent.com/63042547/215334790-718e5c88-7bfa-4496-99e3-1604fbd4085c.png)

[^2]: After first initial run of install.sh, you will need to log in to Jenkins, and set up the admin password. During the initial installation, choose "Install Recommended Plugins", and make sure to set the address of the Jenkins server to either "server" or "jenkins", like `http://jenkins:8080/` 

[^3]: After initial Jenkins installation, go to the Agents section in Jenkins, and set up new agents, one for each - Web, Linux and Windows.
Each Node in Jenkins must have the build directory set to `/build/jenkins/`, and an environment variable representing it's destination, for example for jrpc-linux-builder you need to set LINUX_BUILDER=1 as the environmental variable.
Open three new command lines, and run the command ```docker exec -it jrpc-[container]-builder /bin/bash``` in each of them, where the container can be any of linux, windows, or web.
After that, Jenkins will give you a string to execute a java program to run on your node. For example ```java -jar agent.jar -jnlpUrl http://jenkins:8080/manage/computer/Linux%2Dbuilder/jenkins-agent.jnlp -secret 8dc0f6a11068790fcd60d0958fda8f3e3b172637fa35da31bf7dc0f1a9ec7063 -workDir "/build/jenkins/"```
Execute each of those strings on each of the containers.

[^4]: Lastly, create a new pipeline, and copy the contents of build/jenkins/pipeline.groovy into the pipeline section. Note, that you will have to modify the line ```agent { label 'Windows-builder' }``` to correspond to each of your nodes you created, each according to their own label you set.  
Quit (Ctrl+C) the program end edit build/jenkins/start-agent.sh initialization secret string with the proper one. This is a temporary step, will be fixed in the future.
