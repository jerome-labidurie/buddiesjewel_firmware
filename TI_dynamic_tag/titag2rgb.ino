/* 
 * Get buddiesjewel write and send it to rgb led
 * -----------------------
 * Copyright 2013 Ten Wong, wangtengoo7@gmail.com
 *  https://github.com/awong1900/RF430CL330H_Shield 
 *  RF430CL330H datasheet reference http://www.ti.com/
 */

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include <Wire.h>
#include <RF430CL330H_Shield.h>

/* pins for RF430 communication */
#define IRQ   (1)
#define RESET (32)  

/* pins for RGB led */
#define PIN_RED 8
#define PIN_GREEN 9
#define PIN_BLUE 10

/* on board led */
#define LED 13

#define READ_LEN 4

RF430CL330H_Shield nfc(IRQ, RESET);

unsigned char NDEF_Application_Data[] = RF430_DEFAULT_DATA;
volatile byte into_fired = 0;
uint16_t flags = 0;
byte ndefdata[1024];
uint16_t Tag4Length = 0;

void setup(void) 
{
    Serial.begin(115200);    
    Serial.println("Hello!");
    pinMode(LED, OUTPUT); 
    digitalWrite(LED, HIGH);
    
   pinMode(PIN_RED, OUTPUT);
   pinMode(PIN_GREEN, OUTPUT);
   pinMode(PIN_BLUE, OUTPUT);
   setColor (0, 255, 0);

    //reset RF430
    nfc.begin();
    delay(1000);
}

void loop(void) 
{
    while(!(nfc.Read_Register(STATUS_REG) & READY)); //wait until READY bit has been set
    Serial.print("Fireware Version:"); Serial.println(nfc.Read_Register(VERSION_REG), HEX);    

    //write NDEF memory with Capability Container + NDEF message
    nfc.Write_Continuous(0, NDEF_Application_Data, sizeof(NDEF_Application_Data));

    //Enable interrupts for End of Read and End of Write
    nfc.Write_Register(INT_ENABLE_REG, EOW_INT_ENABLE + EOR_INT_ENABLE);

    //Configure INTO pin for active low and enable RF
    nfc.Write_Register(CONTROL_REG, INT_ENABLE + INTO_DRIVE + RF_ENABLE );

    //enable interrupt 1
    attachInterrupt(1, RF430_Interrupt, FALLING);
    
    Serial.println("Wait for read or write...");
    while(1)
    {
        if(into_fired)
        {
            //clear control reg to disable RF
            nfc.Write_Register(CONTROL_REG, INT_ENABLE + INTO_DRIVE); 
            delay(750);
            
            //read the flag register to check if a read or write occurred
            flags = nfc.Read_Register(INT_FLAG_REG); 
            Serial.print("INT_FLAG_REG = 0x");Serial.println(flags, HEX);
            
            //ACK the flags to clear
            nfc.Write_Register(INT_FLAG_REG, EOW_INT_FLAG + EOR_INT_FLAG); 
            
            if(flags & EOW_INT_FLAG)      //check if the tag was written
            {
                Serial.println("The tag was writted!");
                getNDEFdata(ndefdata, Tag4Length);
                setColor ( ndefdata[1], ndefdata[2], ndefdata[3] );
                digitalWrite(LED, HIGH);
            }
            else if(flags & EOR_INT_FLAG) //check if the tag was read
            {
                Serial.println("The tag was readed!");
                digitalWrite(LED, LOW);
            }
            flags = 0;
            into_fired = 0; //we have serviced INT1

            //Enable interrupts for End of Read and End of Write
            nfc.Write_Register(INT_ENABLE_REG, EOW_INT_ENABLE + EOR_INT_ENABLE);

            //Configure INTO pin for active low and re-enable RF
            nfc.Write_Register(CONTROL_REG, INT_ENABLE + INTO_DRIVE + RF_ENABLE);

            //re-enable INTO
            attachInterrupt(1, RF430_Interrupt, FALLING);
        }
    }
}

/**
**  @brief  interrupt service
**/
void RF430_Interrupt()            
{
    into_fired = 1;
    detachInterrupt(1);//cancel interrupt
}


/**
**  @brief get the writted NDEF data
**/
boolean getNDEFdata(uint8_t* ndefdata, uint16_t Tag4Length)
{
    byte buffer[1024];
    uint16_t NDEFMessageLength = 0;
    
    /* get the NDEF Message Length */
//     nfc.Read_Continuous(0, buffer, (uint16_t)0x1C);
//     NDEFMessageLength = buffer[0x1A] << 8 | buffer[0x1B];
    //Serial.print("NDEFMessageLength = 0x");Serial.println(NDEFMessageLength, HEX);

    /* entire Tag length */
    Tag4Length = NDEFMessageLength + 0x1C;
//     Tag4Length = READ_LEN;
    //Serial.print("Tag4Length = 0x");Serial.println(Tag4Length, HEX);
    
    /* get the entire tag data */
    nfc.Read_Continuous(0x41, buffer, READ_LEN);
    for (uint8_t k=0; k < READ_LEN; k++)
    {
        ndefdata[k] = buffer[k];
        Serial.print("ndefdata[0x");Serial.print(k, HEX);Serial.print("]=");Serial.println(buffer[k], HEX); 
    }
    
    return true;
}

/**  set the RGB LED color
 * @param red the R value (0-255)
 * @param green the G value
 * @param blue the B value
 */
void setColor(uint8_t red, uint8_t green, uint8_t blue)
{
   analogWrite (PIN_RED,   255 - red);
   analogWrite (PIN_GREEN, 255 - green);
   analogWrite (PIN_BLUE,  255 - blue);
}

