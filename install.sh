# Initialize Environment
. ./build/env.sh

# Display Banner
banner

# Launch Build
docker-compose -p jrpc -f $jrpc_beta_v2/build/docker-compose.yaml build

# Launch Docker
docker-compose -p jrpc -f $jrpc_beta_v2/build/docker-compose.yaml up

# Exit Docker
docker-compose -f $jrpc_beta_v2/build/docker-compose.yaml down
