#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <ws2812.h>

struct cRGB led[1];

const uint8_t colors[] PROGMEM = {
  255, 0,   0,   // red
  0,   255, 0,   // green
  0,   0,   255, // blue
  255, 0,   255, // magenta
  255, 255, 0,   // yellow
  0,   255, 255, // cyan
  255, 40,  40,  // pink
  255, 100, 0,   // orange
  255, 255, 255  // white
};

int main(void) {
  DDRB = 0x00;  // PORTB input
  PORTB = 0xFF; // enable pull-ups

  uint8_t i = eeprom_read_byte((uint8_t*)0);
  if (i > 8) i = 0;

  while (1) {
    uint16_t idx = (uint16_t)i * 3;
    led[0].r = pgm_read_byte(&colors[idx + 0]);
    led[0].g = pgm_read_byte(&colors[idx + 1]);
    led[0].b = pgm_read_byte(&colors[idx + 2]);
    ws2812_setleds(led, 1);

    // on button press
    if (!(PINB & _BV(PB2))) {
      // debounce
      _delay_ms(20);
      // still pressed?
      if (!(PINB & _BV(PB2))) {
        // change color
        i = (i + 1) % 9;
        // store color in
        eeprom_write_byte((uint8_t*)0, i);
        // wait for release
        while (!(PINB & _BV(PB2)));
      }
    }
  }
}
