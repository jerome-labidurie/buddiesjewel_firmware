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
 * AT45    RF430
 * -------------
 * PB2 --- SCL
 * PB0 --- SDA
 * PB1 --- <Debug LED>
 * GND --- Gnd,E0,E1,E2,/CS,
 * 
 *********************************************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "usiTwi/usiTwiMaster.h"
#include "RF430CL330H.h"

#define MESSAGEBUF_SIZE       4

#define LED PB1
#define QUICK 300
#define LONG 1000

/** do some quick blinks
 * @param n number of blinks
 */
void quickBlink (uint8_t n)
{
   while (n-- != 0)
   {
      PORTB |= _BV(LED); // on
      _delay_ms (QUICK);
      PORTB &= ~ _BV(LED); // off
      _delay_ms (QUICK);
   }
} //quickBlink

/** do some long blinks
 * @param n number of blinks
 */
void longBlink (uint8_t n)
{
   while (n-- != 0)
   {
      PORTB |= _BV(LED); // on
      _delay_ms (LONG);
      PORTB &= ~ _BV(LED); // off
      _delay_ms (LONG);
   }
} //longBlink

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

/** write a register to RF430
 * @param reg the register address to write. See RF430CL330H.h.
 * @param value the value to be written.
 * @return USI_TWI_Get_State_Info. See usiTwiMaster.h for error codes.
 */
uint8_t writeRegister (uint16_t reg, uint8_t value)
{
   uint8_t messageBuf[MESSAGEBUF_SIZE];
   
   // write register adress
   messageBuf[0] = RF430_I2C_ADDRESS << TWI_ADR_BITS;
   messageBuf[1] = reg >> 8;
   messageBuf[2] = reg & 0xFF;
   messageBuf[3] = value;
   USI_TWI_Start_Transceiver_With_Data( messageBuf, 4 );
   
   return USI_TWI_Get_State_Info();
} // writeRegister

/****** MAIN ******/
int main (void)
{
   uint8_t temp = 0;
   uint16_t value = 0;
   
   _delay_ms (2000);
   
   DDRB |= _BV(LED); // PBx as output
   // quick 2 blinks
   quickBlink (2);
   
   USI_TWI_Master_Initialise();  
   
   temp = readRegister  (VERSION_REG, &value);
   temp = writeRegister (CONTROL_REG, RF_ENABLE);
   temp = readRegister  (CONTROL_REG, &value);
   
   while (1)
   {
      _delay_ms (100);
      temp = readRegister (STATUS_REG, &value);
      
      if (temp != 0) {
         quickBlink (temp);
      }
      else {
         longBlink (value>>8);
         _delay_ms (LONG*2);
         longBlink (value & 0xFF);
      }
   }

   return 0;
} // main
