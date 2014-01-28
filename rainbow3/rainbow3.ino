#include <avr/io.h>
#include <avr/interrupt.h>
#include <Adafruit_NeoPixel.h>


#define LED_PIN            1      /* Pin 0: LED connection              */
#define RAINBOWING_LED_PIN 0      /* Pin 1: for PCINT1: Play/Stop Pin   */
#define DEBUG_PIN          2      /* Pin 2: debugging with a led:       */
                                  /*        HIGH if rainbow has stopped */
                                  /*        LOW in rainbow mode         */ 
                                  
// Parameter 1 = number of pixels in led
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
#ifdef TRUE
#  undef TRUE
#endif
#ifdef FALSE
#  undef FALSE
#endif
#ifdef UP
#  undef UP
#endif
#ifdef DOWN
#  undef DOWN
#endif

#define TRUE  0x01
#define FALSE 0x00
#define UP    1
#define DOWN  0


Adafruit_NeoPixel   led           = Adafruit_NeoPixel(1, LED_PIN, NEO_GRB + NEO_KHZ800);
volatile unsigned char rainbowing = TRUE;
volatile unsigned char flag       = DOWN; 
volatile unsigned char jsave      = 0; 

/** interrupt service routine
 * called when PCINT changes state
 */
void stop_rainbow()
{
//    quickBlink (1, BLUE ); // quick 1 blue blink
//  flag = UP;
   rainbowing=!rainbowing;
} // stop_rainbow()


void setup() {
  pinMode(DEBUG_PIN,OUTPUT);

  led.begin();
  led.show(); // Initialize all pixels to 'off'
  rainbowing = TRUE; // activate the rainbow 
  jsave=0;
  flag       = DOWN; // no detected interrupt yet
  attachInterrupt(RAINBOWING_LED_PIN, stop_rainbow, FALLING); 
  
//  digitalWrite(DEBUG_PIN, HIGH);
//  delay(5000);
}

void loop() {
  uint8_t wait = 20;
  //uint8_t i, s = 250;
  // Some example procedures showing how to display to the pixels:
  /*
  colorWipe(led.Color(255, 0, 0), 50); // Red
  colorWipe(led.Color(0, 255, 0), 50); // Green
  colorWipe(led.Color(0, 0, 255), 50); // Blue
  // Send a theater pixel chase in...
  theaterChase(led.Color(127, 127, 127), 50); // White
  theaterChase(led.Color(127,   0,   0), 50); // Red
  theaterChase(led.Color(  0,   0, 127), 50); // Blue
  */
  /*
  for(i=0;i<s;i++) {
    digitalWrite(DEBUG_PIN, HIGH);
    delay(wait);
    digitalWrite(DEBUG_PIN, LOW);
    delay(wait);
  }
  */
   
   /*
   for(i=0;i<3;i++) {
    digitalWrite(DEBUG_PIN, HIGH);
    delay(1000);
    digitalWrite(DEBUG_PIN, LOW);
    delay(1000);
  }
  */

#if 0
  //rainbow(wait);
  noInterrupts();                // disable interrupts
  if(flag==UP) {
    //rainbowing=~rainbowing;
    //rainbowing?rainbowing=FALSE:rainbowing=TRUE;
    rainbowing=!rainbowing;
    digitalWrite(DEBUG_PIN, LOW);
    flag=DOWN;
    delay(1000);
  }
  else {
    flag=DOWN;
  }
  interrupts();                  // re-enable interrupts
#endif 
  
  if(digitalRead(RAINBOWING_LED_PIN)==LOW) {
    digitalWrite(DEBUG_PIN,LOW);
  }
  else {
    digitalWrite(DEBUG_PIN,HIGH);
  }

  
  if(rainbowing) {
    //digitalWrite(DEBUG_PIN, HIGH);
    led.setPixelColor(0, Wheel((++jsave % 256) & 255));
    led.show();
  }
   
  delay(wait);
 
  /*
  rainbowCycle(20);
  theaterChaseRainbow(50);
  */
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return led.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return led.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return led.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

