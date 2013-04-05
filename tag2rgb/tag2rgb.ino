//This example reads a MIFARE memory block. It is tested with a new MIFARE 1K cards. Uses default keys.
//Contributed by Seeed Technology Inc (www.seeedstudio.com)

#include <PN532.h>
#include <SPI.h>

#define PIN_RED 3
#define PIN_GREEN 5
#define PIN_BLUE 6

#define SERIAL_SPEED 9600
#define SERIAL_DEBUG 1
#define SERIAL_MAX_LEN 20

/*Chip select pin can be connected to D10 or D9 which is hareware optional*/
/*if you the version of NFC Shield from SeeedStudio is v2.0.*/
#define PN532_CS 10

PN532 nfc(PN532_CS);
#define  SERIAL_DEBUG 1

void setup(void) {
#ifdef SERIAL_DEBUG
  Serial.begin(SERIAL_SPEED);
  Serial.println("Hello!");
#endif
  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
#ifdef SERIAL_DEBUG
    Serial.print("Didn't find PN53x board");
#endif
    while (1); // halt
  }
#ifdef SERIAL_DEBUG
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); 
  Serial.println((versiondata>>24) & 0xFF, HEX);
  Serial.print("Firmware ver. "); 
  Serial.print((versiondata>>16) & 0xFF, DEC);
  Serial.print('.'); 
  Serial.println((versiondata>>8) & 0xFF, DEC);
  Serial.print("Supports "); 
  Serial.println(versiondata & 0xFF, HEX);
#endif
  // configure board to read RFID tags and cards
  nfc.SAMConfig();
}

void loop(void) {
  uint32_t id;
  // look for MiFare type cards
  id = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A);

  if (id != 0) 
  {
#ifdef SERIAL_DEBUG
      Serial.print("Read card #"); 
      Serial.println(id);
#endif  
      uint8_t keys[]= { 0xD3,0xF7,0xD3,0xF7,0xD3,0xF7 };
      uint8_t block[16];
      //read memory block 0x06
         if(nfc.authenticateBlock(1, id ,0x06,KEY_A,keys)) //authenticate block
         {
            //if authentication successful
            if(nfc.readMemoryBlock(1,0x06,block))
            {
#ifdef SERIAL_DEBUG
               //if read operation is successful
               for(uint8_t i=0;i<16;i++)
               {
                  //print memory block
                  Serial.print(block[i],HEX);
                  Serial.print(" ");
               }
               Serial.println();
            }
            else
            {
               Serial.println("Authentification failed");
            }
#endif
         }
      setColor ( block[10], block[11], block[12] );
   }
 delay(500);
}


/**  set the RGB LED color
 * @param red the R value (0-255)
 * @param green the G value
 * @param blue the B value
 */
void setColor(uint8_t red, uint8_t green, uint8_t blue)
{
   // anode commune, on inverse les valeurs
   analogWrite (PIN_RED,   255 - red);
   analogWrite (PIN_GREEN, 255 - green);
   analogWrite (PIN_BLUE,  255 - blue);
}

