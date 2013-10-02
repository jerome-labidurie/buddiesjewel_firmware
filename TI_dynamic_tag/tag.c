#include <Wire.h>

// tag address with E0-E2 to gnd
#define TAG_ADDR 0x28

/**************************************************************/

#define REG_VER_SOFTV 0xFFFE
#define REG_VER_SOFTI 0xFFEE

/* Read a register
 * 
 * @param address theregister address
 * @return the read value
 */
byte readRegister(uint16_t address)
{
    // send address to read
   Wire.beginTransmission(TAG_ADDR);
   // registre soft id
   Wire.write((address & 0xFF00) >>8);
   Wire.write((address & 0xFF));
   Wire.endTransmission();    // stop transmitting
   // read value
   Wire.requestFrom(TAG_ADDR, 1);
   while(Wire.available())    // no purpose loop
   { 
      return Wire.read(); // receive a byte and return it
   }

} // readRegister

/**************************************************************/

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

void setup()
{
   Wire.begin(); // join i2c bus (address optional for master)
   pinMode(led, OUTPUT);  
}

byte x = 0;

void loop()
{
   digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)  
   
   x = readRegister (REG_VER_SOFTV);
   Serial.print(x, HEX);         // print the character

   delay(500);
   digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
   delay(500);               // wait for a second  
}
