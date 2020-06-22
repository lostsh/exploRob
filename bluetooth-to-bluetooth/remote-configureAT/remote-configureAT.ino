#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3);
char c=' ';
boolean NL = true;
 
void setup(){
    Serial.begin(9600);
    Serial.print("Sketch:   ");   Serial.println(__FILE__);
    Serial.print("Uploaded: ");   Serial.println(__DATE__);
    Serial.println(" ");
 
    BTserial.begin(9600);  
    Serial.println("BTserial started at 9600");
}
 
void loop(){
    if (BTserial.available()){
        c = BTserial.read();
        Serial.write(c);
    }
    if (Serial.available()){
        c = Serial.read();

        if (c!=10 & c!=13 ){  
             BTserial.write(c);
        }
        if (NL) { Serial.print("\r\n>");  NL = false; }
        
        Serial.write(c);
        if (c==10) { NL = true; }
    }
}
