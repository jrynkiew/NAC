#!/bin/sh
#sleep infinity
# Change the following appropriately

JENKINS_URL="http://jenkins:8080"
JENKINS_USER=admin
JENKINS_USER_PASS=admin

JSON_OBJECT=$(cat <<EOF
{"name":"${NODE_NAME}","nodeDescription":"","numExecutors":"1","remoteFS":"/build/jenkins","labelString":"","mode":"NORMAL","":["hudson.slaves.JNLPLauncher","0"],"launcher":{"stapler-class":"hudson.slaves.JNLPLauncher","$class":"hudson.slaves.JNLPLauncher","workDirSettings":{"disabled":false,"workDirPath":"","internalDir":"remoting","failIfWorkDirIsMissing":false},"webSocket":false,"tunnel":""},"retentionStrategy":{"stapler-class":"hudson.slaves.RetentionStrategy$Always","$class":"hudson.slaves.RetentionStrategy$Always"},"nodeProperties":{"stapler-class-bag":"true"},"type":"hudson.slaves.DumbSlave","Jenkins-Crumb":"${JENKINS_CRUMB}"}
EOF
)

JENKINS_CRUMB=$(curl -u "$JENKINS_USER:$JENKINS_USER_PASS" -s --cookie-jar /tmp/cookies $JENKINS_URL'/crumbIssuer/api/xml?xpath=concat(//crumbRequestField,":",//crumb)')

ACCESS_TOKEN=$(curl -u "$JENKINS_USER:$JENKINS_USER_PASS" -H $JENKINS_CRUMB -s --cookie /tmp/cookies $JENKINS_URL'/me/descriptorByName/jenkins.security.ApiTokenProperty/generateNewToken' --data 'newTokenName=GlobalToken' | jq -r '.data.tokenValue')

echo $ACCESS_TOKEN
echo $JENKINS_CRUMB

curl -L -s -o /dev/null -w "%{http_code}" -u "${JENKINS_USER}:${ACCESS_TOKEN}" -H "Content-Type:application/x-www-form-urlencoded" -H "Jenkins-Crumb:${JENKINS_CRUMB}" -X POST -d 'json={"name":+"${NODE_NAME}",+"nodeDescription":+"",+"numExecutors":+"1",+"remoteFS":+"/build/jenkins/",+"labelString":+"",+"mode":+"NORMAL",+"":+["hudson.slaves.JNLPLauncher",+"0"],+"launcher":+{"stapler-class":+"hudson.slaves.JNLPLauncher",+"$class":+"hudson.slaves.JNLPLauncher",+"workDirSettings":+{"disabled":+false,+"workDirPath":+"",+"internalDir":+"remoting",+"failIfWorkDirIsMissing":+false},+"webSocket":+false,+"tunnel":+""},+"retentionStrategy":+{"stapler-class":+"hudson.slaves.RetentionStrategy$Always",+"$class":+"hudson.slaves.RetentionStrategy$Always"},+"nodeProperties":+{"stapler-class-bag":+"true"},+"type":+"hudson.slaves.DumbSlave",+"Jenkins-Crumb":+"${JENKINS_CRUMB}"}' "${JENKINS_URL}/computer/doCreateItem?name=${NODE_NAME}&type=hudson.slaves.DumbSlave"

# cd /build/jenkins-scripts/
# curl -sO http://jenkins:8080/jnlpJars/agent.jar
# java -jar agent.jar -jnlpUrl $JENKINS_URL/manage/computer/$NODE_NAME/jenkins-agent.jnlp -secret 1bf8cc2f8f80430983448f36e1c99d47c91cd86f8b4aee41bd9f4dd1ed614bc8  -workDir "/jenkins"

sleep infinity


# $ cat credential.xml
# <org.jenkinsci.plugins.plaincredentials.impl.StringCredentialsImpl>
#   <scope>GLOBAL</scope>
#   <id>myId</id>
#   <secret>mysecret</secret>
#   <description>Test</description>
# </org.jenkinsci.plugins.plaincredentials.impl.StringCredentialsImpl>
# $ curl -X POST -H content-type:application/xml -d @credential.xml 'https://user:password@jenkins_server:8080/jenkins/credentials/store/system/domain/_/credential/myId/config.xml'