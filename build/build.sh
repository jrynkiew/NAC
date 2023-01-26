# Build Docker
docker-compose -p jrpc -f docker-compose.yaml build

# Launch Docker
docker-compose -p jrpc -f docker-compose.yaml up --remove-orphans

# Exit Docker
docker-compose -f docker-compose.yaml down