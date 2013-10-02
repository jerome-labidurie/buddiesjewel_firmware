#include <Wire.h>
#include <stdarg.h>

#define TAG_ADDR 0x28

/**************************************************************/



//Global datas
//Used for TMs/TCs
unsigned char tcHeader=0;
unsigned int adressRequest=0;
unsigned int dataRequest=0;
unsigned int scanStatus=0;


#define REG_VER_SOFTV 0xFFEE
//#define REG_VER_SOFTI 0xFFEE

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
Wire.endTransmission(); // stop transmitting
// read value
Wire.requestFrom(TAG_ADDR, 1);
while(Wire.available()) // no purpose loop
{ 
return Wire.read(); // receive a byte and return it
}

} // readRegister


/* Write a register
* 
* @param address theregister address
* @param data  theregister data to be written
* @return nothing
*/
void writeRegister(uint16_t address,uint16_t data)
{
// send address to read
Wire.beginTransmission(TAG_ADDR);
// registre soft id
Wire.write((address & 0xFF00) >>8);
Wire.write((address & 0xFF));
Wire.write((data & 0xFF00) >>8);
Wire.write((data & 0xFF));
Wire.endTransmission(); // stop transmitting


} // writeRegister

/* Format a string and send it to serial line (max 128 bytes)
*/
void sendSerialMessage(char *fmt, ... ){
        char tmp[128]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(tmp, 128, fmt, args);
        va_end (args);
        Serial.print(tmp);
		
}//sendSerialMessage



/* Read a TC from serial line
* 
* @param none
* @return the 1 if a valid TC has been receveid, 0 otherwise
* allowed TCs, ascii format : 
*     Rnnnn : read request for register 0xnnnn (ex: rfffe)
*     Wnnnnmmmm : write request for 16bits register 0xnnnn (ex:wfff80001 : clear IRQ flags ) 

*/
unsigned char readTC()
{
char debugmsg[128]; // resulting string limited to 128 chars


unsigned char length=0;
unsigned char adress_[4];
unsigned char dataReceived=0;
unsigned char byte=0;

unsigned char shift=0;
//Check for incomming message
if (Serial.available() > 0) {
		// read the incoming byte:
		tcHeader = Serial.read();
		switch (tcHeader) { 
			case 'w': // cas 1
			
				//Serial.print("Write request detected\n");
				//extract adress
				adressRequest=0;
				dataRequest=0;
				for (int i=0; i <= 3; i++){
				  byte=Serial.read();
				  //ASCII ->char
				  if (byte>=65)
				  {
					adress_[i]=byte-87;
				  }
				  else
				  {
					adress_[i]= byte-0x30;
				  }
				  
				  
				  //sendSerialMessage("adress %d: %d",i,adress_[i]);
				  shift=4*(3-i);
				  adressRequest+=adress_[i]<<shift;
				}

				//extract data to be written
				for (int i=0; i <= 3; i++){
				  byte=Serial.read();
				  //ASCII ->char
				  if (byte>=65)
				  {
					adress_[i]=byte-87;
				  }
				  else
				  {
					adress_[i]= byte-0x30;
				  }
				  				

				  //sendSerialMessage("adress %d: %x",i,adress_[i]);
				  shift=4*(3-i);
				  dataRequest+=adress_[i]<<shift;
				}
				//sendSerialMessage("adress requested:0x%x\n",adressRequest);
				//sendSerialMessage("data requested:0x%x\n",dataRequest);	
				dataReceived=1;
			  break;

			case 'r': 
				//Serial.print("Read request detected\n");
				//extract adress
				adressRequest=0;			  
				for (int i=0; i <= 3; i++){
				  byte=Serial.read();
				  //ASCII ->char
				  if (byte>=65)
				  {
					adress_[i]=byte-87;
				  }
				  else
				  {
					adress_[i]= byte-0x30;
				  }
				  //sendSerialMessage("adress %d: %x",i,adress_[i]);
				  shift=4*(3-i);
				  adressRequest+=adress_[i]<<shift;
				}
				//sendSerialMessage("adress requested:0x%x\n",adressRequest);		
				dataReceived=1;
			  break;
			case 'g': 			  
					scanStatus=1;
					dataReceived=1;					
			  break;
			case 's': 			  
					scanStatus=0;
					dataReceived=1;					
			  break;


			default: // cas par défaut
			  Serial.print("Unknown TC ?");	
		  }		


}
return dataReceived;

} // readTC

/**************************************************************/

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

void setup()
{
    // start serial port at 9600 bps and wait for port to open:
	Serial.begin(9600);
	Wire.begin(); // join i2c bus (address optional for master)
	pinMode(led, OUTPUT); 
	Serial.print("Go!");
}



void loop()
{
	unsigned char incomingTC=0;
	byte x = 0;
	digitalWrite(led, HIGH); // turn the LED on (HIGH is the voltage level) 

	//Check for any TC
	incomingTC=readTC();
	if (incomingTC)
	{
		switch (tcHeader) { 
					case 'r':	
						x = readRegister (adressRequest);
						sendSerialMessage("reading 0x%x from  @0x%x\n",x,adressRequest);	
						break;
					case 'w': 
						sendSerialMessage("writing 0x%x @0x%x\n",dataRequest,adressRequest);
						writeRegister(adressRequest,dataRequest);
						break;				
					default:
						;
		}
	}	

	
	if (scanStatus)
	{
	  x = readRegister (0xFFFC);
	  sendSerialMessage("S:0x%x",x);
	}
	
	delay(500);
	digitalWrite(led, LOW); // turn the LED off by making the voltage LOW
	delay(500); // wait for a second 
}
