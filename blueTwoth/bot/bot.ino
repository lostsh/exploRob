#include "bot.h"
#include <SoftwareSerial.h>
SoftwareSerial btSerial(7, 8);

Data *datas;
unsigned long nowTime = 0;
unsigned long lastReceptionTime = 0;

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
  //btSerial.write("[*] Seems to be ok then start !\n");
  //brake
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
  resetData(datas);
}

void loop(){
  readData(datas, &nowTime, &lastReceptionTime);
  
  Serial.print("\nXpot val : [");
  Serial.println(datas->xPot);
  Serial.print("] yPot val : [");
  Serial.print(datas->yPot);
  Serial.println("]");

  moove(datas);
}

void readData(Data* dta, unsigned long *currentTime, unsigned long *lastReceptionTime){
  currentTime = millis();
  if(currentTime-lastReceptionTime > 800){
    resetData(dta);
  }
  
  if(btSerial.available()){
    btSerial.readBytes((char*)dta, sizeof(*dta));
    *lastReceptionTime = millis();
  }
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

void moove(Data *dt){
  int lPow = dt->yPot;
  int rPow = dt->yPot;
  //Converting the potentino values to a motor power
  if(dt->yPot>0){
    if(dt->xPot>0){
      rPow-=dt->xPot;
    }else{
      lPow-=abs(dt->xPot);
    }
  }else{//mooving backward
    if(dt->xPot>0){
      rPow+=abs(dt->xPot);
    }else{
      lPow+=abs(dt->xPot);
    }
  }
  //send values to motors
  leftMotor(lPow);
  rightMotor(rPow);
}

void resetData(Data *dta){
  dta->xPot = 0;
  dta->yPot = 0;
  //dta->btn = 0;
}
