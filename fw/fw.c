#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <ws2812.h>

struct cRGB led[1];

int main(void) {
  DDRB = 0x00; // set PORTB as input
  PORTB = 0xFF; // enable pull up on PORTB

  uint8_t i = eeprom_read_byte((uint8_t*)0);
  uint8_t colors[9][3] = {
    {255, 0, 0}, // red
    {0, 255, 0}, // blue
    {0, 0, 255}, // green
    {255, 0, 255}, // magenta
    {255, 255, 0}, // yellow
    {0, 255, 255}, // cyan
    {255, 40, 40}, // pink
    {255, 100, 0}, // orange
    {255, 255, 255}, // white
  };

  while(1) {
    led[0].r=colors[i][0];
    led[0].g=colors[i][1];
    led[0].b=colors[i][2];
    ws2812_setleds(led,1);

    if (!(PINB & _BV(PB2))) {
      if (i >= 8) {
	i = 0;
      } else {
	i++;
      }
      eeprom_write_byte((uint8_t*)0, i);
      _delay_ms(180);
    }
  }
}
