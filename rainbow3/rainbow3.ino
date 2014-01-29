#include <avr/io.h>
#include <avr/interrupt.h>
#include <Adafruit_NeoPixel.h>

#define RAINBOWING_LED_PIN 0      /* Physical Pin 5: for PCINT1: Play/Stop Pin      */
#define LED_PIN            1      /* Physical Pin 6: LED connection                 */
#define DEBUG_PIN          2      /* Physical Pin 7: debugging with a led:          */
                                  /*                 HIGH when the button is pushed */
                                  /*                 LOW  otherwise                 */ 
                                  
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

// Parameter 1 = number of pixels in led
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel   led           = Adafruit_NeoPixel(1, LED_PIN, NEO_GRB + NEO_KHZ800);
volatile unsigned char rainbowing = TRUE;
volatile unsigned char flag       = DOWN; 
volatile unsigned char count      = 0; 

/** interrupt service routine
 * called when PCINT changes state
 */
void stop_rainbow()
{
   rainbowing=!rainbowing;
} // stop_rainbow()


void setup() {
  pinMode(DEBUG_PIN,OUTPUT);

  led.begin();
  led.show(); // Initialize all pixels to 'off'
  rainbowing = TRUE; // activate the rainbow 
  count=0;
  flag       = DOWN; // no detected interrupt yet
  attachInterrupt(RAINBOWING_LED_PIN, stop_rainbow, FALLING);
}

void loop() {
  uint8_t wait = 200;  

  if(digitalRead(RAINBOWING_LED_PIN)==LOW) {
    digitalWrite(DEBUG_PIN,LOW);
  }
  else {
    digitalWrite(DEBUG_PIN,HIGH);
  }
  
  if(rainbowing) {
    led.setPixelColor(0, Wheel(count++));
    led.show();
  }
  delay(wait);
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 84) {
    return led.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos >=84 && WheelPos < 88) { // fix blue color
    return led.Color(0, 0, 255);  
  } else if(WheelPos < 170) {
    WheelPos -= 85;
    return led.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
    WheelPos -= 170;
    return led.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

