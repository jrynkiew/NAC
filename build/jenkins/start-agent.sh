#!/bin/sh
cd /build/jenkins-scripts/
curl -sO http://server:8080/jnlpJars/agent.jar
java -jar agent.jar -jnlpUrl http://server:8080/manage/computer/SDL%20Builder/jenkins-agent.jnlp -secret 477f7f790efb604a1ed61a407dc3db950cbb8da6e75a1864f5faed431d460e03 -workDir "/jenkins"