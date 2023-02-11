

![NAC](https://user-images.githubusercontent.com/63042547/215357605-72fe88a0-68ee-468e-90f0-fee1ff3b96ed.png)

# NAC
&nbsp;
New Age Computing LLC
<pre>
NFT platform cross-compiler
</pre>
This project is designed to streamline testing multi-architecture builds of imgui based projects.

You will get Linux x64, Windows x32, and Emscripten Web executables as a result of a successful build.

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
Once you have set up Jenkins, connect all nodes to your Jenkins server. Configure your pipelines accordingly, then all you need to do is run the Jeknins pipeline to build the solution.

After initial installations, execute command `docker exec -it jrpc-[container]-builder /bin/bash`, so that's `docker exec -it jrpc-windows-builder /bin/bash` for example.

The output exe will be in the generated folder, for each build node name. So a Jenkins node called windows will build it's output here - C:\Users\jrynk\Code\NAC\generated\windows solution directory, where `jrynk` is my username, you should pass your Windows User Name.  and the generated build files will be in the generated folder

## Extra Info
Please follow the appendixes for instructions and the below attached pictures for additional assistance.

[^1]: Upon launching the installation script, you will see command line output from Jenkins - you need to find the secret password from Jenkins in it, and go to `http://localhost:8080/` in your browser window to continue the installation. See pictures below:

![Jenkins--1](https://user-images.githubusercontent.com/63042547/215334738-74a6aaf4-06f3-4297-a1a9-fd7997e9bfd9.png)

![Jenkins-0](https://user-images.githubusercontent.com/63042547/215334760-34e9f4cf-a1d9-4d36-b7ff-b71f04efcf65.png)

![Jenkins-1](https://user-images.githubusercontent.com/63042547/215334781-b5242cce-cbbc-413f-a691-04715b5605a0.png)

![Untitled1](https://user-images.githubusercontent.com/63042547/218255931-f40119cf-e031-4813-a7e3-75a952cd96fa.png)

![Jenkins-2](https://user-images.githubusercontent.com/63042547/215334790-718e5c88-7bfa-4496-99e3-1604fbd4085c.png)

![Untitled1](https://user-images.githubusercontent.com/63042547/218256137-a0d6e337-0f74-47db-8690-c505ab747f87.png)

![Jenkins-3](https://user-images.githubusercontent.com/63042547/215335257-569400c7-4105-413b-bcff-3fad2398df62.png)


[^2]: After first initial run of install.sh, you will need to log in to Jenkins, and set up the admin password. During the initial installation, choose "Install Recommended Plugins", and make sure to set the address of the Jenkins server to either "server" or "jenkins", like `http://jenkins:8080/` 

[^3]: After initial Jenkins installation, go to the Agents section in Jenkins, and set up new agents, one for each - Web, Linux and Windows.
Each Node in Jenkins must have the build directory set to `/build/jenkins/`, and an environment variable representing it's destination, for example for jrpc-linux-builder you need to set LINUX_BUILDER=1 as the environmental variable.
Open three new command lines, and run the command ```docker exec -it jrpc-[container]-builder /bin/bash``` in each of them, where the container can be any of linux, windows, or web.
After that, Jenkins will give you a string to execute a java program to run on your node. For example ```java -jar agent.jar -jnlpUrl http://jenkins:8080/manage/computer/Linux%2Dbuilder/jenkins-agent.jnlp -secret 8dc0f6a11068790fcd60d0958fda8f3e3b172637fa35da31bf7dc0f1a9ec7063 -workDir "/build/jenkins/"```
Execute each of those strings on each of the containers.

[^4]: Lastly, create a new pipeline, and copy the contents of build/jenkins/pipeline.groovy into the pipeline section. Note, that you will have to modify the line ```agent { label 'Windows-builder' }``` to correspond to each of your nodes you created, each according to their own label you set.  
Quit (Ctrl+C) the program end edit build/jenkins/start-agent.sh initialization secret string with the proper one. This is a temporary step, will be fixed in the future.

<p align="left">
<img src="https://user-images.githubusercontent.com/63042547/215356555-a29e78c9-8197-462a-8e73-fbaf86af9b1b.gif" width=20% height=20%>
</p>
