F_CPU = 9600000
MCU = attiny13a
# 9.6MHz w/ fast rising power
LFUSE = 0x76
HFUSE = 0xFF

CFLAGS = -g2 -I. -Ilib -mmcu=$(MCU) -DF_CPU=$(F_CPU)
CFLAGS+= -Os -ffunction-sections -fdata-sections -fpack-struct \
         -fno-move-loop-invariants -fno-tree-scev-cprop -fno-inline-small-functions
CFLAGS+= -Wall -Wno-pointer-to-int-cast
LDFLAGS = -Wl,--relax,-Map=main.map

all: fw.elf fuse flash

fw.elf: fw.c lib/ws2812.c
	avr-gcc $(CFLAGS) $(LDFLAGS) -o $@ $^
	avr-size $@
	avr-objcopy -j .text -j .data -O ihex $@ fw.hex
	avr-objdump -d -S $@ >fw.lss

clean:
	rm -f *.hex *.elf *.lss main.map

fuse:
	sudo avrdude -c stk500v1 -b 19200 -p t13a -P /dev/ttyACM0 \
		-U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m

flash: fw.hex
	sudo avrdude -c stk500v1 -b 19200 -p t13a -P /dev/ttyACM0 -U flash:w:$<

.PHONY: all clean fuse flash
