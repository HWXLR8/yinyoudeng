F_CPU = 9600000
MCU = attiny13a
LFUSE = 0x76 # 9.6MHz w/ fast rising power
HFUSE = 0xFF

CFLAGS = -g2 -I. -Ilib -mmcu=$(MCU) -DF_CPU=$(F_CPU)
CFLAGS+= -Os -ffunction-sections -fdata-sections -fpack-struct -fno-move-loop-invariants -fno-tree-scev-cprop -fno-inline-small-functions
CFLAGS+= -Wall -Wno-pointer-to-int-cast
LDFLAGS = -Wl,--relax,--section-start=.text=0,-Map=main.map

all: fw

ws2812: lib/ws2812.h
	avr-gcc $(CFLAGS) -o obj/$@.o -c lib/$@.c

fw: ws2812
	avr-gcc $(CFLAGS) -o obj/$@.o fw.c lib/$^.c
	avr-size obj/$@.o
	avr-objcopy -j .text  -j .data -O ihex obj/$@.o $@.hex
	avr-objdump -d -S obj/$@.o >obj/$@.lss

.PHONY:	clean fuse upload
clean:
	rm -f *.hex obj/*.o obj/*.lss

fuse:
	sudo avrdude -c stk500v1 -b 19200 -p t13a -P /dev/ttyACM0 -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m

upload:
	sudo avrdude -c stk500v1 -b 19200 -p t13a -P /dev/ttyACM0 -U flash:w:fw.hex
