#include <Arduino.h>
#include <FastLED.h>

#define TOUCH_SENSOR_PIN 8

// Duration of a long touch in milliseconds
#define LONG_TOUCH_DURATION 800

#define PIN_LED_STRIPE_1 4
#define PIN_LED_STRIPE_2 5
#define PIN_LED_STRIPE_3 6
#define PIN_LED_STRIPE_4 7
#define LEDS_PER_STRIPE 60

class TouchSensor {
public:
    static void Setup() {
        pinMode(TOUCH_SENSOR_PIN, INPUT);
    }

    static bool IsTouched() {
        return digitalRead(TOUCH_SENSOR_PIN);
    }
};

typedef enum {
    None = 0,
    WhiteLow,
    WhiteMedium,
    WhiteHigh,
    Rainbow,
    NiceColor1,
    NiceColor2,
    NiceColor3,
    ShowEnd
} Show;

struct State {
    bool forceLEDRefresh;
    Show show;
};

// Records when the last touch started.
// The value 0 means no touch started
unsigned long touchStart = 0;
unsigned long lastTouchEnd = 0;

struct State state;

CRGB ledsStrip1[LEDS_PER_STRIPE];
CRGB ledsStrip2[LEDS_PER_STRIPE];
CRGB ledsStrip3[LEDS_PER_STRIPE];
CRGB ledsStrip4[LEDS_PER_STRIPE];

void InitLEDs() {
    state.forceLEDRefresh = true;
    state.show = None;

    // TODO: Initialize LEDs
    FastLED.addLeds<WS2812B, PIN_LED_STRIPE_1>(ledsStrip1, LEDS_PER_STRIPE);
    FastLED.addLeds<WS2812B, PIN_LED_STRIPE_2>(ledsStrip2, LEDS_PER_STRIPE);
    FastLED.addLeds<WS2812B, PIN_LED_STRIPE_3>(ledsStrip3, LEDS_PER_STRIPE);
    FastLED.addLeds<WS2812B, PIN_LED_STRIPE_4>(ledsStrip4, LEDS_PER_STRIPE);
}

void UpdateLEDs(unsigned long currentTime) {

    switch (state.show) {
        case None: {
            if (state.forceLEDRefresh) {
                // Set everything to black
                FastLED.showColor(CRGB::Black);
            }
            break;
        }
        case WhiteLow: {
            if (state.forceLEDRefresh) {
                // Set everything to low brightness white
                FastLED.showColor(CRGB::White, 100);
            }
            break;
        }
        case WhiteMedium: {

            if (state.forceLEDRefresh) {
                // Set everything to medium brightness white
                FastLED.showColor(CRGB::White, 150);
            }
            break;
        }
        case WhiteHigh: {
            if (state.forceLEDRefresh) {
                // Set everything to high brightness white
                FastLED.showColor(CRGB::White, 255);

            }
            break;
        }
        case Rainbow: {
            uint8_t initialHue = (currentTime / 100) % 255;
            fill_rainbow(ledsStrip1, LEDS_PER_STRIPE, initialHue);
            fill_rainbow(ledsStrip2, LEDS_PER_STRIPE, initialHue);
            fill_rainbow(ledsStrip3, LEDS_PER_STRIPE, initialHue);
            fill_rainbow(ledsStrip4, LEDS_PER_STRIPE, initialHue);
            FastLED.show();
            break;
        }

        case NiceColor1: {
            if (state.forceLEDRefresh) {
                // Coral
                FastLED.showColor(CRGB(0xFF7F50));
            }
            break;
        }

        case NiceColor2: {
            if (state.forceLEDRefresh) {
                // Orchid
                FastLED.showColor(CRGB(0xDA70D6));
            }
            break;
        }

        case NiceColor3: {
            if (state.forceLEDRefresh) {
                // Honeydew
                FastLED.showColor(CRGB(0xF0FFF0));
            }
            break;
        }
    }

    if (state.forceLEDRefresh) {
        state.forceLEDRefresh = false;
    }
}

void setup() {
    Serial.begin(9600);
    TouchSensor::Setup();
    pinMode(LED_BUILTIN, OUTPUT);
    InitLEDs();
}

void loop() {
    digitalWrite(LED_BUILTIN, TouchSensor::IsTouched());

    // Check if the button was touched.
    if (TouchSensor::IsTouched()) {
        if (touchStart == 0) {
            // New touch started
            touchStart = millis();
        }
    } else {
        if (touchStart > 0) {
            // The touch ended
            if (millis() - lastTouchEnd > 200) {
                unsigned long touchDuration = millis() - touchStart;
                touchStart = 0;

                Serial.println(touchDuration);
                if (touchDuration >= LONG_TOUCH_DURATION) {
                    // Turn off
                    state.show = None;
                    state.forceLEDRefresh = true;
                    Serial.println("sh");
                } else {
                    // Go to the next show
                    Serial.println("l");
                    int currentShowId = state.show;
                    currentShowId++;
                    if (currentShowId >= ShowEnd) {
                        currentShowId = 0;
                    }
                    state.forceLEDRefresh = true;
                    state.show = (Show) currentShowId;
                }
            }

            lastTouchEnd = millis();
        }
    }

    // Update the LEDs
    UpdateLEDs(millis());

    // Slow down the loop a little bit
    _delay_ms(20);
}
