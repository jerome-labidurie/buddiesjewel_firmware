#!/bin/bash
# flash a attiny45 with blinkm proprietary firmware
# firmware extracted from http://code.google.com/p/blinkm-projects/wiki/ReflashBlinkM

if [ -z "$1" ]
then
   USB=/dev/ttyUSB0
else
   USB=$1
fi

PGM="avrisp -b 19200"
#PGM=stk500

# lire fuses
avrdude -V -p t45 -c $PGM  -P $USB -U lfuse:r:-:b -U hfuse:r:-:b -U efuse:r:-:b
# flash program & eeprom
avrdude -V -p t45 -c $PGM -P $USB -U flash:w:blinkmv1.hex:a -U eeprom:w:blinkmv1.eep
# write lfuse
avrdude -V -p t45 -c $PGM -P $USB -U lfuse:w:0xDD:m
