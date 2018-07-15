#include <FastLED.h>
#include "light.hpp"

#include "Arduino.h"

// TODO: Implement a finite state machine to better handle command parsing.
#define COMMAND_STATUS 1
#define COMMAND_PLAY 10
#define COMMAND_STOP 20

// Commands to set a specific color to all leds
#define COMMAND_SET_HUE         0xA0
#define COMMAND_SET_SATURATION  0xA1
#define COMMAND_SET_VALUE       0xA2
#define COMMANd_SHOW_HSV        0xA4

#define RESPONSE_OK 1
#define RESPONSE_ERROR 255

void setup() {
  // Setup LEDs
  initLights();

  // Setup communication
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
}

// storage for the color received over serial
uint8_t h, s, v, brightness = 0;

// For command parsing
uint8_t byte1 = 0;

/**
 * Get a command from the serial port.
 *
 * @param command Command is stored in here if one is received.
 * @param parameter Paramter is stored in here if one is received.
 * @return True if a command was received. False if not.
 */
bool getCommand(uint8_t &command, uint8_t &parameter) {
  int new_byte = Serial.read();
  if (new_byte != -1) {
    if (byte1 == 0) {
      byte1 = static_cast<uint8_t>(new_byte);
    }
    else {
      // We got the second byte.
      command = byte1;
      parameter = static_cast<uint8_t>(new_byte);

      // Reset the first byte.
      byte1 = 0;

      return true;
    }
  }

  return false;
}



/**
 * Handles the received command with the paramter.
 * @param command
 * @param parameter
 */
void handleCommand(uint8_t command, uint8_t parameter) {
  switch (command) {
    case COMMAND_STATUS: {
      Serial.write(RESPONSE_OK);
      break;
    }
    case COMMAND_STOP: {
      // Turn off leds
      FastLED.showColor(CRGB::Black);
      Serial.write(RESPONSE_OK);
      break;
    }
    case COMMAND_PLAY: {
      Serial.write(RESPONSE_OK);
      playPattern(parameter);
      break;
    }
    case COMMAND_SET_HUE: {
      h = parameter;
      break;
    }
    case COMMAND_SET_SATURATION: {
      s = parameter;
      break;
    }
    case COMMAND_SET_VALUE: {
      v = parameter;
      break;
    }
    case COMMANd_SHOW_HSV: {
      set_color(h, s, v);
      Serial.write(RESPONSE_OK);
      break;
    }
    default:
      break;
  }

}

/**
 * The main loop of the application. This loop is running all the time.
 * No operation in the loop may be blocking.
 */
void loop() {
  uint8_t command, paramter;
  bool result = getCommand(command, paramter);
  if (result) {
    // Need to handle the command!
    handleCommand(command, paramter);
  }
}
