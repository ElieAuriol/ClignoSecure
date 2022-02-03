#include <SoftwareSerial.h>
#define RX 10
#define TX 11
char state=0;
SoftwareSerial BlueT(RX,TX);
//int PWM=128;
//char Data;

// État d'activation de la tempo
int tempoActive = 0;
 
// Temps à l'activation de la tempo
unsigned long tempoDepart = 0;

//etat de la led
int ledState = LOW;



#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        12 // On Trinket or Gemma, suggest changing this to 1
const int buttonG = 8;
const int buttonD = 9;
const int buttonW = 10;
int stateG = 1;
int stateD = 1;
int stateW = 1;
int old_stateG =1;
int old_stateD =1;
int old_stateW =1;

int V_Led = 0;
int C_Led = 1;
long int chrono = 0;

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 28 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 60 // Time (in milliseconds) to pause between pixels
int i=1;
int t = 0;
int tw=0;
void setup() {

  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial.begin(38400);
  delay(500);
  Serial.println("Bonjour -Pret pour les commandes AT");
  BlueT.begin(38400);
  delay(500);

 

  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  pinMode(buttonG,INPUT_PULLUP);
  pinMode(buttonD,INPUT_PULLUP);
  pinMode(buttonW,INPUT_PULLUP);
}

void loop() {

  // put your main code here, to run repeatedly:
  state = '2';
  /*if (BlueT.available()>0){
    state = BlueT.read();
    Serial.println(state);
  }*/

  
  pixels.clear(); // Set all pixel colors to 'off'
  
  /*stateG = digitalRead(buttonG);
  stateD = digitalRead(buttonD);
  stateW = digitalRead(buttonW);*/

  //old_stateG = stateG;
  if(state=='1') {
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  
      pixels.show();   // Send the updated pixel colors to the hardware. 
    }
  }
  
  else if(state=='2'){
      /*for(int i=0; i<7; i++) { // For each pixel...
      
        pixels.setPixelColor(27-i, pixels.Color(255, 50, 0));
        pixels.setPixelColor(14+i, pixels.Color(255, 50, 0));
        pixels.show();   // Send the updated pixel colors to the hardware.
        if (millis() >= t + DELAYVAL ){  
          t = millis();
        }*/

      V_Led=1;
      if (( V_Led ==1) && (C_Led==1)){
        chrono = millis();
        pixels.setPixelColor(28-C_Led,pixels.Color(255,50,0));
        pixels.setPixelColor(13+C_Led ,pixels.Color(255,50,0));
        pixels.show();
        Serial.println(C_Led);
        C_Led++;
        //delay(1000);
        Serial.println("Etape 1");
      }
      if ( V_Led == 1 && C_Led > 1 && C_Led <8 && millis()>chrono + 60){
        chrono= millis();
        pixels.setPixelColor(28-C_Led,pixels.Color(255,50,0));
        pixels.setPixelColor(13+C_Led ,pixels.Color(255,50,0));
        pixels.show();
        Serial.println(C_Led);
        C_Led++;
                //delay(1000);
     
      }
  if (C_Led>7) {C_Led=1;}      
  /*
        //delay(DELAYVAL); // Pause before next pass through loop
        //stateG = digitalRead(buttonG);
      
      for(int i=0; i<7; i++) { // For each pixel...
        if (millis() >= t + DELAYVAL ){
          pixels.setPixelColor(27-i, pixels.Color(0, 0, 0));
          pixels.setPixelColor(14+i, pixels.Color(0, 0, 0));
    
          pixels.show();   // Send the updated pixel colors to the hardware.
          
          t = millis();
        }
     // C_Led =1;
      if ( V_Led ==1 && C_Led==1){
        chrono = millis();
        pixels.setPixelColor(26-C_Led,pixels.Color(0,0,0));
        pixels.setPixelColor(13+C_Led ,pixels.Color(0,0,0));
        pixels.show();
        C_Led++;
      }
      if ( V_Led == 1 && C_Led > 1 && C_Led <8 && millis()>chrono + 60){
        chrono= millis();
        pixels.setPixelColor(26-C_Led,pixels.Color(0,0,0));
        pixels.setPixelColor(13+C_Led ,pixels.Color(0,0,0));
        pixels.show();
        C_Led++;
      }
        //delay(DELAYVAL); // Pause before next pass through loop
      }
  

  //old_stateD = stateD;
    if(state=='1') {
      for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    
        pixels.show();   // Send the updated pixel colors to the hardware.
    
      }
    }

    else if (state=='0'){
      for (int i=0; i<1; i++){
        for(int i=0; i<7; i++) { // For each pixel...
          pixels.setPixelColor(i, pixels.Color(255, 50, 0));
          pixels.setPixelColor(13-i, pixels.Color(255, 50, 0));
        
          pixels.show();   // Send the updated pixel colors to the hardware.
          delay(DELAYVAL); // Pause before next pass through loop
        }
        stateG = digitalRead(buttonG);
        for(int i=0; i<7; i++) { // For each pixel...
          pixels.setPixelColor(i, pixels.Color(0, 0, 0));
          pixels.setPixelColor(13-i, pixels.Color(0, 0, 0));
      
          pixels.show();   // Send the updated pixel colors to the hardware.
      
          delay(DELAYVAL); // Pause before next pass through loop
        }
        delay(200);
      }
    }
    
    //old_stateW = stateW;
    if(state=='1') {
      for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels.show();   // Send the updated pixel colors to the hardware.
      }
    }
    else if (state=='3'){
      for(int i = 0; i < NUMPIXELS; i++ ) { // On fait une boucle pour définir la couleur de chaque led
        pixels.setPixelColor(i, pixels.Color(255,50,0));      
      } 
      pixels.show(); // on affiche 
      if (millis() > tw + 400){
        for(int i = 0; i < NUMPIXELS; i++ ) { // On fait une boucle pour définir la couleur de chaque led
          pixels.setPixelColor(i, pixels.Color(0,0,0));      
        } 
        pixels.show();
        tw=millis();
      }
  */
    }
 
  
}
