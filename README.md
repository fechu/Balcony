# Balcony

A webapplication that interacts with alexa to control lights on a balcony.

## Technologies

The web application uses Flask to provide the necessary responses to alexa. The flask app is run with uwsgi and uses a certificate from Let's encrypt.
The router is setup to forward port 80 to port 2222 on the raspberry pi.
