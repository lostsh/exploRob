#include "bot.h"
#include <SoftwareSerial.h>
SoftwareSerial btSerial(7, 8);

void moove(int, int);
void readData(Data*);

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
  moove(0, 0);
}

int motorPower[2];

Data *datas;

void loop(){
  //parsePower(motorPower);
  readData(datas);
  
  Serial.print("\nLeft :");
  //Serial.println(datas->leftPow);
  Serial.print("Right : ");
  //Serial.println(datas->rightPow);

  moove(motorPower[0], motorPower[1]);
}

void readData(Data* dta){
  if(btSerial.available()){
    //btSerial.readBytes(dta, sizeof(*dta))
  }
}

void parsePower(int* tab){
  String data = "";
  while(btSerial.available()){
    char c = btSerial.read();
    if(c==';'){
      break;
    }
    data+=c;
  }
  if(data.length()>0){
    int indexComma = data.indexOf(',');
    tab[0] = data.substring(0, indexComma).toInt();
    tab[1] = data.substring(indexComma+1, data.length()).toInt();
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

void moove(int lPow, int rPow){
  leftMotor(lPow);
  rightMotor(rPow);
}
