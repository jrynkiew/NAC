#!/bin/bash
set -e

# Call original entrypoint
cat /mnt/secret_keys/config >> /home/nac/.ssh/config
cat /mnt/secret_keys/id_ed25519 >> /home/nac/.ssh/id_ed25519
cat /mnt/secret_keys/id_ed25519.pub >> /home/nac/.ssh/id_ed25519.pub
cat /mnt/secret_keys/id_ed25519.pub >> /home/nac/.ssh/authorized_keys

service ssh start

# Run supplied command as non-root user
exec /usr/local/bin/gosu nac "$@"