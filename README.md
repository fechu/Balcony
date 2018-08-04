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

## Renewing SSL Certificates

SSL Certificates from Let's Encrypt are used. A cronjob is setup to run (in `/etc/crontab`) to run the `renew_certificates.sh` script once a month. If you need to refresh the certificate manually, run the script as follows:

        sudo ./renew_certificates.sh

## Arduino Communication

The arduino supports several commands to turn on the lights. The following table describes the different commands. 
See also the file `Balcony/Arduino/rgb_communication_test.py` that plays a hue sweep but controlled from a python script. 

A command consists of two bytes. The first byte is the command, the second is an optional parameter. If nothing else is mentioned each command either returns 0x01 (success) or 0xFF (error). 

| Command Name   | Command Identifier | Parameter          | Description                                                                                                                                    |
|----------------|--------------------|--------------------|------------------------------------------------------------------------------------------------------------------------------------------------|
| STATUS         | 0x01               | -                  | Check if the Arduino is up and running and responds to commands                                                                                |
| PLAY           | 0x0A               | Pattern identifier | Play a pattern. The parameter is the pattern identifier. E.g. 0 to set the color to white.                                                     |
| STOP           | 0x14               | -                  | Turn the lights off                                                                                                                            |
| SET_HUE        | 0xA0               | Hue value          | Set the hue values of the LEDs. The color is not yet shown. Only if the command SHOW_HSV is sent. This command does not return anything.       |
| SET_SATURATION | 0xA1               | Saturation value   | Set the saturation value of the LEDs. The color is not yet shown. Only if the command SHOW_HSV is sent. This command does not return anything. |
| SET_VALUE      | 0xA2               | Value              | Set the value of the LEDs. The color is not yet shown. Only if the command SHOW_HSV is sent. This command does not return anything.            |
| SHOW_HSV       | 0xA4               | -                  | Show the Hue, Saturation and Value previously set with the SET_HUE, SET_SATURATION and SET_VALUE commands.                                     |
