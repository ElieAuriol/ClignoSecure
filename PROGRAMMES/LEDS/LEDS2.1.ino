#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1

const int button = 8;
int state = 1;
int etat = 1;
int old_state =1;

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 16 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 50 // Time (in milliseconds) to pause between pixels
int i=0;
void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  pinMode(button,INPUT);
  Serial.begin(9600);
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'
  
  state = digitalRead(button);

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.

  /*if((state==LOW) && (old_state==HIGH)) {
    etat = 1 - etat;
    Serial.println("HIGH");
  }*/
  old_state = state;
  if(state==LOW) {
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
  
      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      // Here we're using a moderately bright green color:
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  
      pixels.show();   // Send the updated pixel colors to the hardware.
  
      delay(DELAYVAL); // Pause before next pass through loop
    }
    Serial.println("LOW");
    
  }
  
  else{
    Serial.println("HIGH");
    for (int i=0; i<3; i++){
      for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    
        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        // Here we're using a moderately bright green color:
        pixels.setPixelColor(i, pixels.Color(255, 50, 0));
    
        pixels.show();   // Send the updated pixel colors to the hardware.
    
        delay(DELAYVAL); // Pause before next pass through loop
      }
      
      delay(200);
      state = digitalRead(button);
      for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
  
      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      // Here we're using a moderately bright green color:
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  
      pixels.show();   // Send the updated pixel colors to the hardware.
  
      delay(DELAYVAL); // Pause before next pass through loop
    }
    }
    
  }
  
  
}
