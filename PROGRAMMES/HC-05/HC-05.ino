//HC-05


int state=20;
int buttonState=0;
int interupteurState=0;
int warningState =0;
#include <SoftwareSerial.h>
#define RX 8
#define TX 9
#define clignoD 10
#define clignoG 11
#define warning 12
SoftwareSerial BlueT(RX,TX);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  delay(500);
  Serial.println("Bonjour -Pret pour les commandes AT");
  pinMode(clignoD,INPUT_PULLUP);
  pinMode(clignoG,INPUT_PULLUP);
  pinMode(warning, INPUT_PULLUP);
  BlueT.begin(38400);
  delay(500);
  
  

}

void loop() {
  // put your main code here, to run repeatedly:
  
  //bouton poussoir
  
  buttonState = digitalRead(clignoD); //on lit la valeur du bouton
  interupteurState= digitalRead(clignoG); //meme systeme que le bouton poussoir
  warningState = digitalRead(warning);
  if (buttonState ==HIGH && interupteurState==HIGH && warningState==HIGH){ //on renvoit 1 si on appuie sur aucun des 2 boutons 
    Serial.println('1');//pour verifier sur le moniteur serie de l'ordinateur que ça marche
    BlueT.write("1"); //on envoie par le bluetooth
  }

  if (buttonState ==LOW && interupteurState==HIGH && warningState==HIGH){ //on renvoit 0 si on appuie uniquement sur le bouton 1
    Serial.println('0');
    BlueT.write("0"); //on envoie par le bluetooth
  }
  
  if (buttonState ==HIGH && interupteurState==LOW && warningState==HIGH){ // on renvoit 2 si on appuie uniquement sur le bouton 2
    Serial.println('2');
    BlueT.write("2");
  }  

  if (buttonState ==HIGH && interupteurState==HIGH && warningState==LOW){ // on renvoit 2 si on appuie uniquement sur le bouton 2
    Serial.println('3');
    BlueT.write("3");
  } 

  
  
  else if (buttonState ==LOW && interupteurState==LOW && warningState==LOW){ // si on appuie sur les 2 en même temps on renvoie 1
    Serial.println('1');
    BlueT.write("1");
  }
}
