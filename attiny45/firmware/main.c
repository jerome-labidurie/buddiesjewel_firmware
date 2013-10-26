/*********************************************************************
 * ATtiny45
 *                                      ---v---
 *         (PCINT5/RESET/ADC0/dW) PB5 -| 1   8 |- VCC
 *  (PCINT3/XTAL1/CLKI/OC1B/ADC3) PB3 -| 2   7 |- PB2 (SCK/USCK/SCL/ADC1/T0/INT0/PCINT2)
 *  (PCINT4/XTAL2/CLKO/OC1B/ADC2) PB4 -| 3   6 |- PB1 (MISO/DO/AIN1/OC0B/OC1A/PCINT1)
 *                                GND -| 4   5 |- PB0 (MOSI/DI/SDA/AIN0/OC0A/OC1A/AREF/PCINT0)
 *                                      -------
 * 
 *********************************************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define TWI_GEN_CALL         0x00  // The General Call address is 0
#include "usiTwi/usiTwiMaster.h"

#include "RF430CL330H.h"

#define MESSAGEBUF_SIZE       4

#define LED PB1
#define QUICK 300
#define LONG 1000
/**************************************/
/************** MAIN ******************/
/**************************************/

void quickBlink (uint8_t n)
{
   while (n-- != 0)
   {
      PORTB |= _BV(LED); // on
      _delay_ms (QUICK);
      PORTB &= ~ _BV(LED); // off
      _delay_ms (QUICK);
   }
}

void longBlink (uint8_t n)
{
   while (n-- != 0)
   {
      PORTB |= _BV(LED); // on
      _delay_ms (LONG);
      PORTB &= ~ _BV(LED); // off
      _delay_ms (LONG);
   }
}

uint8_t readRegister (uint16_t reg, uint8_t* messageBuf)
{
   
   // write register adress
   messageBuf[0] = RF430_I2C_ADDRESS << TWI_ADR_BITS;
   messageBuf[1] = reg >> 8;
   messageBuf[2] = reg & 0xFF;
   USI_TWI_Start_Transceiver_With_Data( messageBuf, 3 );
   // read register
   messageBuf[0] = ( RF430_I2C_ADDRESS << TWI_ADR_BITS ) | (RF430_I2C_READBIT);
   USI_TWI_Start_Transceiver_With_Data( messageBuf, 3 );
   
   return USI_TWI_Get_State_Info();
}

uint8_t writeRegister (uint16_t reg, uint16_t value)
{
   uint8_t messageBuf[MESSAGEBUF_SIZE];
   
   // write register adress
   messageBuf[0] = RF430_I2C_ADDRESS << TWI_ADR_BITS;
   messageBuf[1] = reg >> 8;
   messageBuf[2] = reg & 0xFF;
//    messageBuf[3] = value >> 8;
   messageBuf[3] = value & 0xFF;
   USI_TWI_Start_Transceiver_With_Data( messageBuf, 4 );
   
   return USI_TWI_Get_State_Info();
}

int main (void)
{
   unsigned char messageBuf[MESSAGEBUF_SIZE], temp;
   
   _delay_ms (2000);
   
   DDRB |= _BV(LED); // PBx as output
   // quick 2 blinks
   quickBlink (2);
   
   USI_TWI_Master_Initialise();  
   
   while (1)
   {
      _delay_ms (1000);
      temp = readRegister ( VERSION_REG, messageBuf);
      temp = writeRegister ( CONTROL_REG, 0x0002 );
      temp = readRegister ( CONTROL_REG, messageBuf);
      if (temp != 0) {
         quickBlink (temp);
      }
      else {
         longBlink (messageBuf[1]);
         _delay_ms (LONG*2);
         longBlink (messageBuf[2]);
      }
   }

   return 0;
} // main
