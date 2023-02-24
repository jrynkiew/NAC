#!/bin/sh

# JSON_OBJECT=$(cat <<EOF
# {"name":"${NODE_NAME}","nodeDescription":"","numExecutors":"1","remoteFS":"/build/jenkins","labelString":"","mode":"NORMAL","":["hudson.slaves.JNLPLauncher","0"],"launcher":{"stapler-class":"hudson.slaves.JNLPLauncher","$class":"hudson.slaves.JNLPLauncher","workDirSettings":{"disabled":false,"workDirPath":"","internalDir":"remoting","failIfWorkDirIsMissing":false},"webSocket":false,"tunnel":""},"retentionStrategy":{"stapler-class":"hudson.slaves.RetentionStrategy$Always","$class":"hudson.slaves.RetentionStrategy$Always"},"nodeProperties":{"stapler-class-bag":"true"},"type":"hudson.slaves.DumbSlave","Jenkins-Crumb":"${JENKINS_CRUMB}"}
# EOF
# )

# JENKINS_CRUMB=$(curl -u "$JENKINS_USER:$JENKINS_USER_PASS" -s --cookie-jar /tmp/cookies $JENKINS_URL'/crumbIssuer/api/xml?xpath=concat(//crumbRequestField,":",//crumb)')

# ACCESS_TOKEN=$(curl -u "$JENKINS_USER:$JENKINS_USER_PASS" -H $JENKINS_CRUMB -s --cookie /tmp/cookies $JENKINS_URL'/me/descriptorByName/jenkins.security.ApiTokenProperty/generateNewToken' --data 'newTokenName=GlobalToken' | jq -r '.data.tokenValue')

# echo $ACCESS_TOKEN
# echo $JENKINS_CRUMB

# curl -L -s -o /dev/null -w "%{http_code}" -u "${JENKINS_USER}:${ACCESS_TOKEN}" -H "Content-Type:application/x-www-form-urlencoded" -H "Jenkins-Crumb:${JENKINS_CRUMB}" -X POST -d 'json={"name":+"${NODE_NAME}",+"nodeDescription":+"",+"numExecutors":+"1",+"remoteFS":+"/build/jenkins/",+"labelString":+"",+"mode":+"NORMAL",+"":+["hudson.slaves.JNLPLauncher",+"0"],+"launcher":+{"stapler-class":+"hudson.slaves.JNLPLauncher",+"$class":+"hudson.slaves.JNLPLauncher",+"workDirSettings":+{"disabled":+false,+"workDirPath":+"",+"internalDir":+"remoting",+"failIfWorkDirIsMissing":+false},+"webSocket":+false,+"tunnel":+""},+"retentionStrategy":+{"stapler-class":+"hudson.slaves.RetentionStrategy$Always",+"$class":+"hudson.slaves.RetentionStrategy$Always"},+"nodeProperties":+{"stapler-class-bag":+"true"},+"type":+"hudson.slaves.DumbSlave",+"Jenkins-Crumb":+"${JENKINS_CRUMB}"}' "${JENKINS_URL}/computer/doCreateItem?name=${NODE_NAME}&type=hudson.slaves.DumbSlave"

whoami

sleep infinity