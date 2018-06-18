#include "Arduino.h"

void setup() {
  // TODO: Setup LEDs
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    byte incomingByte = Serial.read();
    if (incomingByte == 'a') {
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}