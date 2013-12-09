/*********************************************************************
 * BuddiesJewel prototype with ATtiny45/RF430CL330H
 *********************************************************************
 * Copyright: (c) 2013 Jérôme Labidurie
 * Licence:   GNU General Public Licence version 3
 * Email:     jerome.labidurie at gmail.com
 *********************************************************************
 * This file is part of BuddiesJewel.
 * 
 * BuddiesJewel is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BuddiesJewel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with BuddiesJewel.  If not, see <http://www.gnu.org/licenses/>.
 *********************************************************************
 * 
 * ATtiny45
 *                                      ---v---
 *         (PCINT5/RESET/ADC0/dW) PB5 -| 1   8 |- VCC
 *  (PCINT3/XTAL1/CLKI/OC1B/ADC3) PB3 -| 2   7 |- PB2 (SCK/USCK/SCL/ADC1/T0/INT0/PCINT2)
 *  (PCINT4/XTAL2/CLKO/OC1B/ADC2) PB4 -| 3   6 |- PB1 (MISO/DO/AIN1/OC0B/OC1A/PCINT1)
 *                                GND -| 4   5 |- PB0 (MOSI/DI/SDA/AIN0/OC0A/OC1A/AREF/PCINT0)
 *                                      -------
 * 
 * RF430CL330H
 *        ----v---
 *  Vcc -|  1  14 |- Gnd
 *   A1 -|  2  13 |- Vcore
 *   A2 -|  3  12 |- SDA
 * /RST -|  4  11 |- SCL
 *   E0 -|  4  10 |- SCK
 *   E1 -|  6   9 |- /CS
 *   E2 -|  7   8 |- Int
 *        --------
 * 
 * AT45    RF430   NeoPixel
 * -------------------
 * PB2 --- SCL
 * PB0 --- SDA
 * GND --- Gnd,E0,E1,E2,/CS,
 * PB4 ----------- In
 * 
 *********************************************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "usiTwiMaster.h"
#include "RF430CL330H.h"

#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

#define MESSAGEBUF_SIZE       10

#define NEO 4
#define QUICK 100
#define LONG 1000

// predefined colors
//      NAME      0xRRGGBB
#define BLUE      0x0000FF
#define GREEN     0x00FF00
#define RED       0xFF0000

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel led = Adafruit_NeoPixel(1, NEO, NEO_GRB + NEO_KHZ800);

uint8_t temp = 0;    /** temporary variable */
uint16_t value = 0;  /** used to store read values from registers */
uint32_t savedColor = 0x000000; /** color read from eeprom */


/** do some quick blinks
 * @param n number of blinks
 * @param color the color to blink (created by Adafruit_NeoPixel.Color() )
 */
void quickBlink (uint8_t n, uint32_t color)
{
   while (n-- != 0)
   {
      led.setPixelColor (0, color );
      led.show();
      _delay_ms (QUICK);
      led.setPixelColor (0, 0 );
      led.show();
      _delay_ms (QUICK);
   }
} //quickBlink


/** read register from RF430
 * @param reg the register address to read. See RF430CL330H.h.
 * @param pValue pointer to the read value
 * @return USI_TWI_Get_State_Info. See usiTwiMaster.h for error codes.
 */
uint8_t readRegister (uint16_t reg, uint16_t* pValue)
{
   uint8_t messageBuf[MESSAGEBUF_SIZE];
   
   // write register adress
   messageBuf[0] = RF430_I2C_ADDRESS << TWI_ADR_BITS;
   messageBuf[1] = reg >> 8;
   messageBuf[2] = reg & 0xFF;
   USI_TWI_Start_Transceiver_With_Data( messageBuf, 3 );
   // read register
   messageBuf[0] = ( RF430_I2C_ADDRESS << TWI_ADR_BITS ) | (RF430_I2C_READBIT);
   USI_TWI_Start_Transceiver_With_Data( messageBuf, 3 );
   
   *pValue = (messageBuf[1] << 8) | messageBuf[2];
   
   return USI_TWI_Get_State_Info();
} // readRegister

/** read NFC data from RF430 
 * 
 * If active, RF must be disabled before. eg: writeRegister (CONTROL_REG, 0);
 * Note: offset+length must be < 0x0BFF. Else we go into registers.
 * 
 * @param offset the offset in NFC tag data
 * @param length the length to be read
 * @param data byte array for the read data. Must be at least length+1. Read data begins at data[1]
 * @return USI_TWI_Get_State_Info. See usiTwiMaster.h for error codes.
 * 
 */
uint8_t readData (uint16_t offset, uint16_t length, uint8_t* data)
{
   // write data address
   data[0] = RF430_I2C_ADDRESS << TWI_ADR_BITS;
   data[1] = offset >> 8;
   data[2] = offset & 0xFF;
   USI_TWI_Start_Transceiver_With_Data( data, 3 );
   // read register
   data[0] = ( RF430_I2C_ADDRESS << TWI_ADR_BITS ) | (RF430_I2C_READBIT);
   USI_TWI_Start_Transceiver_With_Data( data, length + 1 );

   return USI_TWI_Get_State_Info();
} // readData

/** write a register to RF430
 * @param reg the register address to write. See RF430CL330H.h.
 * @param value the value to be written.
 * @return USI_TWI_Get_State_Info. See usiTwiMaster.h for error codes.
 */
uint8_t writeRegister (uint16_t reg, uint16_t value)
{
   uint8_t messageBuf[MESSAGEBUF_SIZE];
   
   // write register adress
   messageBuf[0] = RF430_I2C_ADDRESS << TWI_ADR_BITS;
   messageBuf[1] = reg >> 8;
   messageBuf[2] = reg & 0xFF;
   messageBuf[3] = value & 0xFF;
   messageBuf[4] = value >> 8;
   USI_TWI_Start_Transceiver_With_Data( messageBuf, 5 );
   
   return USI_TWI_Get_State_Info();
} // writeRegister

/****** MAIN ******/
   
void setup()
{
   // quick 2 blue blinks
   led.begin();
   USI_TWI_Master_Initialise();
   temp = readRegister  (VERSION_REG, &value);
   quickBlink (value>>8, BLUE );
   quickBlink (value, GREEN);

   // read color from eeprom
   savedColor = ((uint32_t)EEPROM.read(0)<<16) | ((uint32_t)EEPROM.read(1)<<8) | EEPROM.read(2);
   // Initialize pixel to saved color
   led.setPixelColor (0, savedColor);
   led.show();
   // Initialize tag with color
   // TODO :)

   
   temp = writeRegister (CONTROL_REG, RF_ENABLE);
   temp = readRegister  (CONTROL_REG, &value);
} // setup

void loop()
{
   uint8_t data[MESSAGEBUF_SIZE]; /** array to store read NDEF data */
   uint32_t readColor = 0;

   _delay_ms (1000);
   temp = readRegister (STATUS_REG, &value);
   
   if (temp != 0) {
      quickBlink(temp, RED );
   }
   else {
      if ( ! ( (value>>8) & RF_BUSY ) )
      {
         // no rf field present, disable RF
         // we should only disable the right bit !
         temp = writeRegister (CONTROL_REG, 0x0);
         // read ndef data
         // 0x1C: NDEf begin 0x24: offset to color
         temp = readData (0x1C + 0x25, 4, data);
         // enable RF
         temp = writeRegister (CONTROL_REG, RF_ENABLE);
         if (data[1] == 0xFF)
         {
            // first read byte if 0xFF, this is transparency, assume color is ok
            readColor = ((uint32_t)data[2]<<16) | ((uint32_t)data[3]<<8) | data[4];
            led.setPixelColor (0, readColor );
            led.show();
            // if needed, save new color in eeprom
            if (savedColor != readColor) {
               EEPROM.write(0, readColor >> 16);
               EEPROM.write(1, (readColor >> 8) & 0xFF);
               EEPROM.write(2, readColor & 0xFF);
               savedColor = readColor;
            }
         }
      }
   }
} // loop

