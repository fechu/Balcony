#!/bin/bash
set -e

#
# This script renews the Let's encrypt certificates
#

# Spin up a python server serving test_webserver
screen -d -m -S python_server "cd /home/pi/webserver && python -m SimpleHTTPServer 2223"

# Renew the certificates
certbot renew 

# Stop the python webserver
screen -X -S python_server quit
