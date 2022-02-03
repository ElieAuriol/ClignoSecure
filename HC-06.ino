//HC-06

#include <SoftwareSerial.h>
#define RX 10
#define TX 11
#define LED 12
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

void setup(){ 
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial.begin(38400);
  delay(500);
  Serial.println("Bonjour -Pret pour les commandes AT");
  pinMode(LED, OUTPUT);
  BlueT.begin(38400);
  delay(500);
  
 

}

void loop() {
  // put your main code here, to run repeatedly:
  if (BlueT.available()>0){
    state = BlueT.read();
    Serial.println(state);
  }

  //state=BlueT.read();

  if (state =='1'){
    digitalWrite(LED,HIGH);
    Serial.println("Etape 1");
  }

  if (state=='0'){
    digitalWrite(LED,LOW);
    Serial.println("Etape 2");
  }

  if (state=='2'){
     Serial.println("Etape 3");
    // Alors on active la temporisation
    tempoActive = 1;
    if (tempoActive){     
      unsigned long tempoArriv = millis();
      if ((tempoArriv-tempoDepart)>= 500){ // Et si il s'est écoulé 500 millisecondes,
        tempoDepart=tempoArriv;
        
        // if the LED is off turn it on and vice-versa:
        if (ledState == LOW) {
          ledState = HIGH;
        } else {
          ledState = LOW;
        }
    
        // set the LED with the ledState of the variable:
        digitalWrite(LED, ledState);
      }         
    }
  }
  
 

}
