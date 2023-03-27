# Initialize Environment
. ./build/.env/env.sh

# Display Banner
banner

# Launch Build
docker-compose -p jrpc -f $jrpc_beta_v2/build/docker/docker-compose.yaml build

mkdir -p $jrpc_beta_v2/build/jenkins/data

# Launch Docker
docker-compose -p jrpc -f $jrpc_beta_v2/build/docker/docker-compose.yaml up -d jenkins

printf "Waiting for Jenkins to be ready ..."
until [ ${http_code} -eq 403 ]; do
    http_code=$(curl -LI --max-time 2 http://localhost:8080 -o /dev/null -w '%{http_code}\n' -s)
    sleep 3
    printf "."
done
printf " ${green}done${reset}
"

docker-compose -p jrpc -f $jrpc_beta_v2/build/docker/docker-compose.yaml up -d jrpc-web-builder
docker-compose -p jrpc -f $jrpc_beta_v2/build/docker/docker-compose.yaml up -d nginx
echo "
┍━━━━━━━━━━━━━━━━━━━━ ⋆⋅☆⋅⋆ ━━━━━━━━━━━━━━━━━━━━┑"

echo "┃ ${green}Jenkins is ready!${reset}                             ┃"
echo "┃ http://localhost:8080                         ┃"

echo "┃ http://localhost:8080/configuration-as-code/  ┃"
echo "┃                                               ┃"
echo "┃ ${green}Python Web Server is ready!${reset}                   ┃"
echo "┃ http://localhost:80                           ┃"

echo "┕━━━━━━━━━━━━━━━━━━━━ ⋆⋅☆⋅⋆ ━━━━━━━━━━━━━━━━━━━━┙
"

sleep infinity

# Exit Docker
docker-compose -p jrpc -f $jrpc_beta_v2/build/docker/docker-compose.yaml down