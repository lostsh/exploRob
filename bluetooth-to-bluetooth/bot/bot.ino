#include <SoftwareSerial.h>
SoftwareSerial btSerial(7, 8);

String incoming;

/*
 * Note a moi même :
 * après on recevre deux valeur séparés par une virgule
 * qui représenterone respectivement la vitesse du moteur1, moteur2
 * et donc une vitesse negative signifiera que le moteur recule
 * et positive qu'il devra avancer
 * 
 * il faudra penser a maper et a borner ses valeures
*/

void setup() {
  btSerial.begin(9600);
  incoming = "s";
  
  //Motor A
  pinMode(12, OUTPUT);
  pinMode(9, OUTPUT);
  //Motor B
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  btSerial.write("[*] Seems to be ok then start !\n");
}
void loop(){
  if(btSerial.available() > 0){
    incoming = btSerial.readString();
    btSerial.print("[+] ");
    btSerial.println(incoming);
  }
  
  if(incoming == "a"){
    avence();
  }
  if(incoming == "r"){
    recule();
  }
  if(incoming == "s"){
    arret();
  }
  if(incoming != "a" && incoming != "r" && incoming != "s"){
    arret();
  }
}

void avence(){
  //btSerial.write("[*] Avence\n");
  digitalWrite(12, HIGH);// forward direction
  digitalWrite(9, LOW);// disable brake
  analogWrite(3, 255);// full speed
  
  digitalWrite(13, HIGH);
  digitalWrite(8, LOW);
  analogWrite(11, 255);
}
void recule(){
  //btSerial.write("[*] Recule\n");
  digitalWrite(12, LOW);
  digitalWrite(9, LOW);
  analogWrite(3, 255);
  
  digitalWrite(13, LOW);
  digitalWrite(8, LOW);
  analogWrite(11, 255);
}
void arret(){
  //btSerial.write("[*] Stop\n");
  digitalWrite(9, HIGH);//Brake A
  digitalWrite(8, HIGH);//Brake B
}
