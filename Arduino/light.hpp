
#pragma once

void initLights();

/**
 * Set all LEDs to the given color.
 */
void set_color(uint8_t h, uint8_t s, uint8_t v);

/**
 * Play a patter defined by ID.
 */
void playPattern(uint8_t pattern);


/**
 * A rainbow pattern
 */
void rainbow(uint32_t duration);

/**
 * A colored dot sweeping back and forth, with fading trails
 */
void dots(uint32_t duration);

/**
 * Random dots fading out
 */
void random_dots(uint32_t duration);

/**
 * Flashing!
 */
void flash(uint32_t duration);
