#!/bin/sh
# Change the following appropriately

JENKINS_URL="http://localhost:8080"
JENKINS_USER=admin
JENKINS_USER_PASS=admin

JENKINS_CRUMB=$(curl -u "$JENKINS_USER:$JENKINS_USER_PASS" -s --cookie-jar /tmp/cookies $JENKINS_URL'/crumbIssuer/api/xml?xpath=concat(//crumbRequestField,":",//crumb)')

ACCESS_TOKEN=$(curl -u "$JENKINS_USER:$JENKINS_USER_PASS" -H $JENKINS_CRUMB -s --cookie /tmp/cookies $JENKINS_URL'/me/descriptorByName/jenkins.security.ApiTokenProperty/generateNewToken' --data 'newTokenName=GlobalToken' | jq -r '.data.tokenValue')
echo $ACCESS_TOKEN
