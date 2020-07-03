#include <SoftwareSerial.h>
SoftwareSerial btSerial(7, 8);

void moove(int, int);

/* Motor B : Left Motor
 * Motor A : Right Motor
 */

void setup() {
  btSerial.begin(9600);
  Serial.begin(9600);
  Serial.println("Start");
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
    int indexComma = incoming.indexOf(',');
    motorPower[0] = incoming.substring(0, indexComma).toInt();
    motorPower[1] = incoming.substring(indexComma+1, incoming.length()).toInt();

    char a[128];
    sprintf(a, "[*] Inco :%s\n[+] LPow(B): %d\n[+] RPow(A): %d",incoming,motorPower[0],motorPower[1]);
    btSerial.println(a);
    Serial.println(a);
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
