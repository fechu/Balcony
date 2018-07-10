# Balcony

A webapplication that interacts with alexa to control lights on a balcony.

## Technologies

The web application uses Flask to provide the necessary responses to alexa. The flask app is run with uwsgi and uses a certificate from Let's encrypt.
The router is setup to forward port 80 to port 2222 on the raspberry pi.

## Autostart Server

On the raspberry pi the server is setup to automatically start. This is done by adding

    (python3 /home/pi/Balcony/server.py &) > /dev/null 2>&1

to the `/etc/rc.local` file

## Serial Communication vs. LED Updates
The update of the WS2812 leds is a blocking process because the used protocol is timing sensitive. Therefore, no serial communication can happen at the same time. To solve this, there's only two ways to display a light pattern:
- Static light. I.e. light you only set up and then stays like this.
- Shows that block any further communication for some time.
