# Makefile
MCU = attiny45
# F_CPU=16500000
F_CPU=1000000
#avr2
TARGET=main
CC=avr-gcc
CFLAGS=-Os -Wall -I. -mmcu=$(MCU)  -IusiTwi -DF_CPU=$(F_CPU)
LDFLAGS=-mmcu=$(MCU) -lm -Wl,--gc-sections -Os -DF_CPU=$(F_CPU)
# PGMERARD=-c arduino -b 115200 -P /dev/ttyUSB0
PGMERISP=-c avrisp  -b 57600 -P /dev/ttyUSB0
STK500=-c stk500  -P /dev/ttyUSB0
PGMER=$(STK500)
DUDE=/usr/bin/avrdude -V -p t45

# if avr slow clock is defined (128KHz/8)
# use make SLOW_CLOCK=Y
ifeq "$(SLOW_CLOCK)" "Y"
	DUDE+=  -B62
else
	DUDE+=  -B1.1
endif

# C_SRCS=$(wildcard *.c)
# C_SRCS=$(TARGET).c
OBJ_FILES=usiTwi/usiTwiMaster.o $(TARGET).o
# OBJ_FILES=$(C_SRCS:.c=.o)

all: $(TARGET).hex size

clean:
	rm -f *.hex $(OBJ_FILES) $(TARGET).elf

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

%.o: %.S
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET).elf: $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $(OBJ_FILES)

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex

upload: $(TARGET).hex
	$(DUDE) $(PGMER) -U flash:w:$(TARGET).hex

size: $(TARGET).elf
	@echo "----------------"
	@avr-size --format=avr --mcu=$(MCU) $(TARGET).elf

display_fuses:
	$(DUDE) $(PGMER) -q -U lfuse:r:-:b -U hfuse:r:-:b -U efuse:r:-:b

# Fuse low byte:
# 0xe1 = 1 1 1 0   0 0 0 1
#        ^ ^ \+/   \--+--/
#        | |  |       +------- CKSEL 3..0 (clock selection -> HF PLL)
#        | |  +--------------- SUT 1..0 (BOD enabled, fast rising power)
#        | +------------------ CKOUT (clock output on CKOUT pin -> disabled)
#        +-------------------- CKDIV8 (divide clock by 8 -> don't divide)
fuse:
	$(DUDE) $(PGMER) -U lfuse:w:0xe1:m
