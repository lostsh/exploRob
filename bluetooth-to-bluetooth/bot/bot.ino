#include <SoftwareSerial.h>
SoftwareSerial btSerial(7, 8);

void moove(int, int);

/* Motor B : Left Motor
 * Motor A : Right Motor
 */

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
  moove(motorPower[0], motorPower[1]);
}

void leftMotor(int value){
  if(value!=0){
    bool forwardDirection = (value>0);
    digitalWrite(13, forwardDirection);
    digitalWrite(8, LOW);
    analogWrite(11, abs(value));
  }else{
    digitalWrite(8, HIGH);
  }
}
void rightMotor(int value){
  if(value!=0){
    bool forwardDirection = (value>0);
    digitalWrite(12, forwardDirection);
    digitalWrite(9, LOW);
    analogWrite(3, abs(value));
  }else{
    digitalWrite(9, HIGH);
  }
}

void moove(int lPow, int rPow){
  leftMotor(lPow);
  rightMotor(rPow);
}
