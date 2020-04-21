/* By : lostsh
 *  
 * The purpose of this program is to
 * facilitate the control of the engine control module.
 * 
 * Acutal version use BLE (Bluetooth Low Energy)
 */
#include <SoftwareSerial.h>

SoftwareSerial blueSerial(7, 8);

String incoming;

void setup() {
  blueSerial.begin(9600);
  incoming = "s";
  //Motor A
  pinMode(12, OUTPUT);
  pinMode(9, OUTPUT);
  //Motor B
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  blueSerial.write("[*] Seems to be ok then start !\n");
}
void loop(){
  if(blueSerial.available() > 0){
    incoming = blueSerial.readString();
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
  //blueSerial.write("[*] Avence\n");
  digitalWrite(12, HIGH);// forward direction
  digitalWrite(9, LOW);// disable brake
  analogWrite(3, 255);// full speed
  
  digitalWrite(13, HIGH);
  digitalWrite(8, LOW);
  analogWrite(11, 255);
}
void recule(){
  //blueSerial.write("[*] Recule\n");
  digitalWrite(12, LOW);
  digitalWrite(9, LOW);
  analogWrite(3, 255);
  
  digitalWrite(13, LOW);
  digitalWrite(8, LOW);
  analogWrite(11, 255);
}
void arret(){
  //blueSerial.write("[*] Stop\n");
  digitalWrite(9, HIGH);//Brake A
  digitalWrite(8, HIGH);//Brake B
}
