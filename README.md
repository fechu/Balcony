# Balcony

A webapplication that interacts with alexa to control lights on a balcony.

## Technologies

The web application uses Flask to provide the necessary responses to alexa. The flask app is run with uwsgi and uses a certificate from Let's encrypt.
The router is setup to forward port 80 to port 2222 on the raspberry pi.

## Autostart Server

On the raspberry pi the server is setup to automatically start. This is done by adding

    screen -d -m -S server -L /home/pi/Balcony/server.log /home/pi/Balcony/start_server.sh

to the `/etc/rc.local` file

## Serial Communication vs. LED Updates
The update of the WS2812 leds is a blocking process because the used protocol is timing sensitive. Therefore, no serial communication can happen at the same time. To solve this, there's only two ways to display a light pattern:
- Static light. I.e. light you only set up and then stays like this.
- Shows that block any further communication for some time.

## Adding a new pattern
To add a new pattern follow these steps:

1. Go to developer.amazon.com and login with Sandro's account
2. Select the "Our Balcony" Alexa skill
3. Go to the Build tab
4. In "Intents" go to "Slot Types" and select "Show"
5. Add a new value. The value is what the user will have to say. So keep it short.
6. Add a unique ID to the value.
7. Open the `Arduino.ino` file
8. Program your pattern in the light.cpp file as a separate function.
9. The function `playPattern(...)` will receive the ID you specified in step 6. Therefore add another switch case and call your function.
10. Upload the sketch to the Arduino.
