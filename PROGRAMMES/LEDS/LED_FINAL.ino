#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        5 // On Trinket or Gemma, suggest changing this to 1
const int buttonG = 8;
const int buttonD = 9;
int stateG = 1;
int stateD = 1;
int old_stateG =1;
int old_stateD =1;

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 28 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 70 // Time (in milliseconds) to pause between pixels
int i=1;

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  pinMode(buttonG,INPUT_PULLUP);
  pinMode(buttonD,INPUT_PULLUP);
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'
  
  stateG = digitalRead(buttonG);
  stateD = digitalRead(buttonD);

  old_stateG = stateG;
  if(stateG==HIGH) {
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  
      pixels.show();   // Send the updated pixel colors to the hardware. 
    }
  }
  else{
    for (int i=0; i<3; i++){
        for(int i=0; i<7; i++) { // For each pixel...
          //pixels.setPixelColor(i, pixels.Color(255, 50, 0));
          pixels.setPixelColor(27-i, pixels.Color(255, 50, 0));
          pixels.setPixelColor(14+i, pixels.Color(255, 50, 0));
          //pixels.setPixelColor(13-i, pixels.Color(255, 50, 0));
        
          pixels.show();   // Send the updated pixel colors to the hardware.
          delay(DELAYVAL); // Pause before next pass through loop
        }
        stateG = digitalRead(buttonG);
        for(int i=0; i<7; i++) { // For each pixel...
          //pixels.setPixelColor(i, pixels.Color(0, 0, 0));
          pixels.setPixelColor(27-i, pixels.Color(0, 0, 0));
          pixels.setPixelColor(14+i, pixels.Color(0, 0, 0));
          //pixels.setPixelColor(13-i, pixels.Color(0, 0, 0));
      
          pixels.show();   // Send the updated pixel colors to the hardware.
      
          delay(DELAYVAL); // Pause before next pass through loop
        }
        delay(200);
      }
  }

  old_stateD = stateD;
    if(stateD==HIGH) {
      for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    
        pixels.show();   // Send the updated pixel colors to the hardware.
    
      }
    
    }

    else{
      for (int i=0; i<3; i++){
        for(int i=0; i<7; i++) { // For each pixel...
          pixels.setPixelColor(i, pixels.Color(255, 50, 0));
          //pixels.setPixelColor(27-i, pixels.Color(255, 50, 0));
          //pixels.setPixelColor(14+i, pixels.Color(255, 50, 0));
          pixels.setPixelColor(13-i, pixels.Color(255, 50, 0));
        
          pixels.show();   // Send the updated pixel colors to the hardware.
          delay(DELAYVAL); // Pause before next pass through loop
        }
        stateG = digitalRead(buttonG);
        for(int i=0; i<7; i++) { // For each pixel...
          pixels.setPixelColor(i, pixels.Color(0, 0, 0));
          //pixels.setPixelColor(27-i, pixels.Color(0, 0, 0));
          //pixels.setPixelColor(14+i, pixels.Color(0, 0, 0));
          pixels.setPixelColor(13-i, pixels.Color(0, 0, 0));
      
          pixels.show();   // Send the updated pixel colors to the hardware.
      
          delay(DELAYVAL); // Pause before next pass through loop
        }
        delay(200);
      }
    }
 
  
}
