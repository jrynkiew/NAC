# Initialize Environment
. ./build/env.sh

# Display Banner
banner

# Launch Build
docker-compose -p jrpc -f $jrpc_beta_v2/build/docker-compose.yaml build --parallel

# Launch Docker
docker-compose -p jrpc -f $jrpc_beta_v2/build/docker-compose.yaml up -d

echo "
┍━━━━━━━━━━━━━━━━━━━━ ⋆⋅☆⋅⋆ ━━━━━━━━━━━━━━━━━━━━┑"
echo "
Please finish the installation on ${green}http://localhost:8080${reset}"
echo "You will need to set up the following:
"
echo "  - ${gold}Admin Account${reset}  -  set to u:admin p:admin"
echo "  - ${gold}Server URL${reset}  -  set to http://jenkins:8080"
echo "  - ${gold}Install plugins${reset}  -  select any you want"

echo "
You will be asked to provide a 'one-time' Jenkins administrator password."

echo "
Your password is 
      ${red}
        $(cat $jrpc_beta_v2/build/jenkins/data/secrets/initialAdminPassword)
      ${reset}" 

echo "┕━━━━━━━━━━━━━━━━━━━━ ⋆⋅☆⋅⋆ ━━━━━━━━━━━━━━━━━━━━┙
"

while :
do
  # Getting necessary user input
  read -p "When you have completed the Jenkins node setup, press any key" CONTINUE

  case $CONTINUE in
    *) # Build IoTeX Full Node
      cd $jrpc_beta/external/JRPC/
      bash $jrpc_beta/external/JRPC/install.sh 
  esac
done

# Exit Docker
docker-compose -p jrpc -f $jrpc_beta_v2/build/docker-compose.yaml down
