#include "Arduino.h"

#define COMMAND_STATUS 1

#define RESPONSE_OK 1

void setup() {
  // TODO: Setup LEDs

  // Setup communication
  Serial.begin(9600);
  Serial.println("Finished Setup");
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
    Serial.println("Received byte");
    if (byte1 == 0) {
      byte1 = static_cast<uint8_t>(new_byte);
    }
    else {
      // We got the second byte.
      command = byte1;
      parameter = static_cast<uint8_t>(new_byte);

      // Reset the first byte.
      byte1 = 0;
      Serial.println("Received second byte");

      return true;
    }
  }

  return false;
}

void loop() {

  uint8_t command, paramter;
  bool result = getCommand(command, paramter);
  if (result) {
    // Need to handle the command!
    switch (command) {
      case COMMAND_STATUS: {
        Serial.write(RESPONSE_OK);
        break;
      }
      default:
        break;
    }
  }

  // TODO: Control the LEDs
}