
#include <FastLED.h>
#include "light.hpp"

#define LED_DATA_PIN_1 7
#define LED_DATA_PIN_2 8
#define LED_DATA_PIN_3 9
#define LED_DATA_PIN_4 10

#define LED_COUNT_PER_STRIP 60
#define LED_COUNT 240
CRGB leds[LED_COUNT];

// TODO: Make this variable. I.e. modify it via alexa to play patterns longer. 
#define PATTERN_DURATION 10000

void initLights() {
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN_1>(leds, 0 * LED_COUNT_PER_STRIP, LED_COUNT_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN_2>(leds, 1 * LED_COUNT_PER_STRIP, LED_COUNT_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN_3>(leds, 2 * LED_COUNT_PER_STRIP, LED_COUNT_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN_4>(leds, 3 * LED_COUNT_PER_STRIP, LED_COUNT_PER_STRIP);
}

/**
 * Starts to play the given pattern.
 * This method is blocking for the duration of the show.
 * @param pattern The pattern to play.
 * @return True if it was successful.
 */
void playPattern(uint8_t pattern) {
  switch (pattern) {
    case 0: {
      FastLED.showColor(CRGB::White, 50);
      break;
    }
    case 1: {
      FastLED.showColor(CRGB::White, 20);
      break;
    }
    case 2: {
      FastLED.showColor(CRGB::White, 255);
      break;
    }
    case 3: {
      rainbow(PATTERN_DURATION);
      playPattern(0);
      break;
    }
    case 4: {
      dots(PATTERN_DURATION);
      playPattern(0);
      break;
    }
    case 5: {
      random_dots(PATTERN_DURATION);
      playPattern(0);
      break;
    }

    case 6: {
      flash(PATTERN_DURATION);
      playPattern(0);
      break;
    }
    default: {
      FastLED.showColor(CRGB::Red);
      break;
    }
  }
  return true;
}

void rainbow(uint32_t duration) {
  uint8_t initialHue = 0;
  uint8_t deltaHue = 5;
  uint8_t loop_delay = 40;
  uint32_t time = 0;

  while (time < duration) {
    time += loop_delay;
    initialHue += deltaHue;
    fill_rainbow(leds, LED_COUNT_PER_STRIP, initialHue, deltaHue);
    FastLED.show();

    delay(loop_delay);
  }
}

void dots(uint32_t duration) {
  uint8_t hue = 0;
  uint8_t deltaHue = 1;
  uint8_t loop_delay = 40;
  uint32_t time = 0;
  uint32_t position = 0;

  while (time < duration) {
    time += loop_delay;
    hue += deltaHue;

    fadeToBlackBy( leds, LED_COUNT_PER_STRIP, 20);
    leds[position] += CHSV( hue, 255, 192);
    
    FastLED.show();

    position += 1;
    if (position >= LED_COUNT_PER_STRIP) {
      position = 0;
    }

    delay(loop_delay);
  }
}

void random_dots(uint32_t duration) {
  uint8_t loop_delay = 40;
  uint32_t time = 0;

  while (time < duration) {
    time += loop_delay;

    fadeToBlackBy( leds, LED_COUNT_PER_STRIP, 20);

    long numberOfLeds = random(5);
    for (long i = 0; i < numberOfLeds; ++i) {
      // Find a position
      long pos = random(LED_COUNT_PER_STRIP);
      leds[pos].r = static_cast<uint8_t>(random(255));
      leds[pos].g = static_cast<uint8_t>(random(255));
      leds[pos].b = static_cast<uint8_t>(random(255));
    }
    
    FastLED.show();

    delay(loop_delay);
  }
}

void flash(uint32_t duration) {
  uint8_t flash_delay = 50;
  uint8_t loop_delay = 2 * flash_delay;
  uint32_t time = 0;

  while (time < duration) {
    time += loop_delay;

    FastLED.showColor(CRGB::White);
    delay(flash_delay);
    FastLED.showColor(CRGB::Black);
    delay(flash_delay);
  }
}

