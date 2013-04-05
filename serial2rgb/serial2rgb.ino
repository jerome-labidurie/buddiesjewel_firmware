/* RGB led test */


#define PIN_RED 3
#define PIN_GREEN 5
#define PIN_BLUE 6

#define SERIAL_SPEED 9600
#define SERIAL_DEBUG 1
#define SERIAL_MAX_LEN 20

#define FADE_DELAY 25

uint8_t r,g,b;
char c;
boolean verbose=false;

void setup()
{
#ifdef SERIAL_DEBUG
   Serial.begin(SERIAL_SPEED);
   Serial.print ("> ");
#endif // SERIAL_DEBUG   
   
   // set pins mode
   pinMode(PIN_RED,   OUTPUT);
   pinMode(PIN_GREEN, OUTPUT);
   pinMode(PIN_BLUE,  OUTPUT);
   setColor (0,0,0);
}

void loop()
{
#ifdef SERIAL_DEBUG

   r = g = b = 0;
   
   /* get commands from serial line */   
   if (Serial.available() > 0)
   {
      c = Serial.read();
      switch (c)
      {
         case 'h': // usage
            Serial.read();
            usage();
            break;
         case 'c': // set a color
            r = Serial.parseInt ();
            g = Serial.parseInt ();
            b = Serial.parseInt ();
            if (Serial.read() == '\n') {
               Serial.print(r,HEX); Serial.print(",");
               Serial.print(g,HEX); Serial.print(",");
               Serial.println(b,HEX);
               setColor (r, g, b);
            }
            break;
         case 'v': // be more/less verbose
            Serial.read();
            verbose = ! verbose;
            Serial.print ("Verbose: ");
            Serial.println (verbose);
            break;
         case 'f': // do a color fade
            Serial.read();
            Serial.println("Fading...");
            fade();
            break;
         default:
            Serial.read();
            Serial.print ("Unknown command: ");
            Serial.println (c);
            break;
      }
      //       Serial.write(Serial.peek()); // echo 1st char
      Serial.print ("> ");
   }
#endif // SERIAL_DEBUG

   /* main NFC code */

} // main


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

#ifdef SERIAL_DEBUG
void usage(void)
{
   Serial.println ("h: usage");
   Serial.println ("c R G B: set a color");
   Serial.println ("v: toogle verbose");
   Serial.println ("f: fade");
}

void fade(void)
{
   /* Fading colors
    * R \ _ /
    * G / \ _
    * B _ / \
    */
   for (r=255, g=0, b=0 ; g < 255 ; r--, g++)
   {
      setColor (r, g, b);
      delay(FADE_DELAY);
   }
   for ( ; b < 255 ; g--, b++)
   {
      setColor (r, g, b);
      delay(FADE_DELAY);
   }
   for ( ; r < 255 ; r++, b--)
   {
      setColor (r, g, b);
      delay(FADE_DELAY);
   }
   setColor (0, 0, 0);
}//fade

#endif // SERIAL_DEBUG
