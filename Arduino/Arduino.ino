#include <FastLED.h>

#include "Arduino.h"

#define COMMAND_STATUS 1
#define COMMAND_PLAY 10
#define COMMAND_STOP 20

#define RESPONSE_OK 1
#define RESPONSE_ERROR 255

#define LED_DATA_PIN_1 7
#define LED_DATA_PIN_2 8
#define LED_DATA_PIN_3 9
#define LED_DATA_PIN_4 10

#define LED_COUNT_PER_STRIP 60
#define LED_COUNT 240
CRGB leds[LED_COUNT];

void setup() {
  // Setup LEDs
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN_1>(leds, 0 * LED_COUNT_PER_STRIP, LED_COUNT_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN_2>(leds, 1 * LED_COUNT_PER_STRIP, LED_COUNT_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN_3>(leds, 2 * LED_COUNT_PER_STRIP, LED_COUNT_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN_4>(leds, 3 * LED_COUNT_PER_STRIP, LED_COUNT_PER_STRIP);

  FastLED.showColor(CRGB::White);
  delay(500);
  FastLED.showColor(CRGB::Black);

  // Setup communication
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
}


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
 * Starts to play the given pattern.
 * This method is blocking for the duration of the show.
 * @param pattern The pattern to play.
 * @return True if it was successful.
 */
bool playPattern(uint8_t pattern) {
  FastLED.showColor(CRGB::White);
  return true;
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
      bool result = playPattern(parameter);
      if (result) {
        Serial.write(RESPONSE_OK);
      }
      else {
        Serial.write(RESPONSE_ERROR);
      }
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
