#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN_L        6 // On Trinket or Gemma, suggest changing this to 1
#define PIN_R        5

const int buttonL = 8;
const int buttonR = 9;
int stateL = 1;
int stateR = 1;
int old_stateL =1;
int old_stateR =1;

// How many NeoPixels are attached to the Arduino?
#define NUMPIXEL_L 6 // Popular NeoPixel ring size
#define NUMPIXEL_R 37 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels1(NUMPIXEL_L, PIN_L, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(NUMPIXEL_R, PIN_R, NEO_GRB + NEO_KHZ800);


#define DELAYVAL_L 50 // Time (in milliseconds) to pause between pixels
#define DELAYVAL_R 10 // Time (in milliseconds) to pause between pixels
int i=0;
void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
  
  pixels1.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels2.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  pinMode(buttonL,INPUT_PULLUP);
  pinMode(buttonR,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  pixels1.clear(); // Set all pixel colors to 'off'
  pixels2.clear(); // Set all pixel colors to 'off'
  
  stateL = digitalRead(buttonL);
  stateR = digitalRead(buttonR);

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.

  /*if((state==LOW) && (old_state==HIGH)) {
    etat = 1 - etat;
    Serial.println("HIGH");
  }*/
  old_stateL = stateL;
  if(stateL==HIGH) {
    for(int i=0; i<NUMPIXEL_L; i++) { // For each pixel...
  
      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      // Here we're using a moderately bright green color:
      pixels1.setPixelColor(i, pixels1.Color(0, 0, 0));
  
      pixels1.show();   // Send the updated pixel colors to the hardware.
  
    }
    Serial.println("LOW");    
  }
  else{
    Serial.println("HIGH");
    for (int i=0; i<3; i++){
      for(int i=0; i<NUMPIXEL_L; i++) { // For each pixel...
    
        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        
        pixels1.setPixelColor(i, pixels1.Color(255, 50, 0));
        //pixels.setPixelColor(i, pixels.Color(253, 50, 80));
    
        pixels1.show();   // Send the updated pixel colors to the hardware.
    
        delay(DELAYVAL_L); // Pause before next pass through loop
        }
      
        delay(100);
        stateL = digitalRead(buttonL);
        for(int i=0; i<NUMPIXEL_L; i++) { // For each pixel...
    
        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        // Here we're using a moderately bright green color:
        pixels1.setPixelColor(i, pixels1.Color(0, 0, 0));
    
        pixels1.show();   // Send the updated pixel colors to the hardware.
    
        delay(DELAYVAL_L); // Pause before next pass through loop
        }
      }
  }

    old_stateR = stateR;
    if(stateR==HIGH) {
      for(int i=0; i<NUMPIXEL_R; i++) { // For each pixel...
    
        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        // Here we're using a moderately bright green color:
        pixels2.setPixelColor(i, pixels2.Color(0, 0, 0));
    
        pixels2.show();   // Send the updated pixel colors to the hardware.
    
      }
      Serial.println("LOW");
    
    }
  
    else{
      Serial.println("HIGH");
      for (int i=0; i<3; i++){
        for(int i=0; i<NUMPIXEL_R; i++) { // For each pixel...
      
          // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
          
          pixels2.setPixelColor(i, pixels2.Color(255, 50, 0));
          //pixels.setPixelColor(i, pixels.Color(253, 50, 80));
      
          pixels2.show();   // Send the updated pixel colors to the hardware.
      
          delay(DELAYVAL_R); // Pause before next pass through loop
        }
        
        delay(100);
        stateR = digitalRead(buttonL);
        for(int i=0; i<NUMPIXEL_R; i++) { // For each pixel...
    
        // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
        // Here we're using a moderately bright green color:
        pixels2.setPixelColor(i, pixels2.Color(0, 0, 0));
    
        pixels2.show();   // Send the updated pixel colors to the hardware.
    
        delay(DELAYVAL_R); // Pause before next pass through loop
      }
      }
  }
  
  
}
