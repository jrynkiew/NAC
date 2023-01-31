# Initialize Environment
. ./build/env.sh

# Display Banner
banner

# # Launch Build
# docker-compose -p jrpc -f $jrpc_beta_v2/build/docker-compose.yaml build

# mkdir -p $jrpc_beta_v2/build/jenkins/data

# # Launch Docker
# docker-compose -p jrpc -f $jrpc_beta_v2/build/docker-compose.yaml up -d jenkins

# printf "Waiting for Jenkins to be ready ..."
# until [ ${http_code} -eq 403 ]; do
#     http_code=$(curl -LI --max-time 2 http://localhost:8080 -o /dev/null -w '%{http_code}\n' -s)
#     sleep 3
#     printf "."
# done
# printf " ${green}done${reset}
# "

# # Check if the secret file is empty
# # If it's empty, it means that it's not the first time Jenkins has been started, 
# # in which case we don't show the startup sequence
# if [ ! -s "$jrpc_beta_v2/build/jenkins/data/secrets/initialAdminPassword" ]; then
#     docker-compose -p jrpc -f $jrpc_beta_v2/build/docker-compose.yaml up jrpc-windows-builder jrpc-web-builder jrpc-linux-builder
# else

# echo "
# ┍━━━━━━━━━━━━━━━━━━━━ ⋆⋅☆⋅⋆ ━━━━━━━━━━━━━━━━━━━━┑"
# echo "
# Please finish the installation on ${green}http://localhost:8080${reset}"
# echo "You will need to set up the following:
# "
# echo "  - ${gold}Admin Account${reset}  -  set to u:admin p:admin"
# echo "  - ${gold}Server URL${reset}  -  set to http://jenkins:8080/"
# echo "  - ${gold}Install plugins${reset}  -  select any you want"

# echo "
# You will be asked to provide a 'one-time' Jenkins administrator password."

# echo "
# Your password is 
#     ${red}
#         $(cat $jrpc_beta_v2/build/jenkins/data/secrets/initialAdminPassword)
#     ${reset}" 

# echo "┕━━━━━━━━━━━━━━━━━━━━ ⋆⋅☆⋅⋆ ━━━━━━━━━━━━━━━━━━━━┙
# "

# while :
# do
# # Getting necessary user input
# read -p "When you have completed the Jenkins server setup, press Enter" CONTINUE

# case $CONTINUE in
#     *) # Build IoTeX Full Node
#     docker-compose -p jrpc -f $jrpc_beta_v2/build/docker-compose.yaml up jrpc-windows-builder jrpc-web-builder jrpc-linux-builder 
#     exit ;;
# esac
# done

# fi


# Exit Docker
docker-compose -p jrpc -f $jrpc_beta_v2/build/docker-compose.yaml down
