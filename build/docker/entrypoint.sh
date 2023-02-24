#!/bin/bash
set -e



if [ -d /mnt/secret_keys/ ]; then
#Check if ssh is already running
service ssh status > /dev/null && echo "sshd is running" || service ssh start

# Use mounted ssh keys for the default nac user.
cat /mnt/secret_keys/config >> /home/nac/.ssh/config
cat /mnt/secret_keys/id_ed25519 >> /home/nac/.ssh/id_ed25519
cat /mnt/secret_keys/id_ed25519.pub >> /home/nac/.ssh/id_ed25519.pub
cat /mnt/secret_keys/id_ed25519.pub >> /home/nac/.ssh/authorized_keys

# Run command as default nac user
exec /usr/local/bin/gosu nac "$@"
else 
echo 'Keys not mounted. Ignoring.'
exit 1;
fi