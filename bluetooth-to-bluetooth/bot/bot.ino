#include <SoftwareSerial.h>
SoftwareSerial btSerial(7, 8);

void setup() {
  btSerial.begin(9600);
  //Motor A
  pinMode(12, OUTPUT);
  pinMode(9, OUTPUT);
  //Motor B
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  btSerial.write("[*] Seems to be ok then start !\n");
}

int motorPower[2];
void loop(){
  if(btSerial.available() > 0){
    String incoming = btSerial.readString();
    String powers[2] = strtok(incoming, ',');
    motorPower[0] = atoi(powers[0]);
    motorPower[1] = atoi(posers[1]);
    btSerial.print("[+] ");
    btSerial.println(incoming);
  }
  
}

/* a driot c'est a droite et a gache c'est a gauceh 
 * si c'est une valeur negative alors on recule sinon on avence
 * point finnale c'est tout rien de plus simple
 */


void moove(int lPow, int rPow){
  avence(lPow, rPow);
}

void avence(int leftPower, int rightPower){
  //btSerial.write("[*] Avence\n");
  digitalWrite(12, HIGH);// forward direction
  digitalWrite(9, LOW);// disable brake
  analogWrite(3, abs(leftPower));// full speed
  
  digitalWrite(13, HIGH);
  digitalWrite(8, LOW);
  analogWrite(11, abs(rightPower));
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
