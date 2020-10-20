unsigned long nowTime = 0;
unsigned long lastReceptionTime = 0;

/* Motor B : Left Motor
 * Motor A : Right Motor
 */

void setup() {
  Serial.begin(9600);
  Serial.println("Start");
  //Motor A
  pinMode(12, OUTPUT);
  pinMode(9, OUTPUT);
  //Motor B
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  //brake
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
}

String incoming = "0,0;";

void loop(){
  if(Serial.available()){
    incoming = Serial.readString();
    Serial.println("[+] "+incoming);
  }
  if(incoming.indexOf(";")>0){
    String y = incoming.substring(0, incoming.indexOf(","));
    String x = incoming.substring(incoming.indexOf(",")+1, incoming.indexOf(";"));
    Serial.print("[*] ");
    Serial.print(y.toInt());
    Serial.print(" - ");
    Serial.println(x.toInt());
    
    moove(y.toInt(), x.toInt());
  }else{
    if(incoming.indexOf("BRAKE")>=0){
      Serial.println("[+] Brake!");
      digitalWrite(9, HIGH);
      digitalWrite(8, HIGH);
    }
    if(incoming.indexOf("LF")>=0){
      Serial.println("[+] Left Forward");
      digitalWrite(13, true);
      digitalWrite(8, LOW);
      analogWrite(11, 255);
    }
    if(incoming.indexOf("LS")>=0){
      Serial.println("[+] Left Stop");
      digitalWrite(8, HIGH);
      //analogWrite(11, 255);
    }
    if(incoming.indexOf("LB")>=0){
      Serial.println("[+] Left Backward");
      digitalWrite(13, false);
      digitalWrite(8, LOW);
      analogWrite(11, 255);
    }
    if(incoming.indexOf("RF")>=0){
      Serial.println("[+] Right Forward");
      digitalWrite(12, true);
      digitalWrite(9, LOW);
      analogWrite(3, 255);
    }
    if(incoming.indexOf("RS")>=0){
      Serial.println("[+] Right Stop");
      digitalWrite(9, HIGH);
    }
    if(incoming.indexOf("RB")>=0){
      Serial.println("[+] Right Backward");
      digitalWrite(12, false);
      digitalWrite(9, LOW);
      analogWrite(3, 255);
    }
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

void moove(int yPot, int xPot){
  int lPow = yPot;
  int rPow = yPot;
  //Converting the potentino values to a motor power
  if(yPot>0){
    if(xPot>0){
      rPow-=xPot;
    }else{
      lPow-=abs(xPot);
    }
  }else{//mooving backward
    if(xPot>0){
      rPow+=abs(xPot);
    }else{
      lPow+=abs(xPot);
    }
  }
  //send values to motors
  leftMotor(lPow);
  rightMotor(rPow);
}
