/*
 * Note a moi même :
 * penser a ajouter l'affichage de l'ecrant
 * sur l'ecrant on aura plusieurs modes 
 * avec plusieurs vitesses, un omde de pressision et un mode de franchissenement
 * ensuite on pourra affichier l'êtat de la battierie sur l'ecrant
 * et enfin si possible l'etat du signal bluetooth
*/
#include <SoftwareSerial.h>
SoftwareSerial btSerial(2, 3);
char c=' ';
boolean NL = true;
 
void setup(){
    Serial.begin(9600);
    btSerial.begin(9600);  
    Serial.println("btSerial started at 9600");
    btSerial.print("AT+IMME1" );
    delay(1000);
    //btSerial.print("AT+ROLE1" );
    //delay(1000);
    btSerial.print("AT+CON90E2028DDAFC" );
    delay(1000);
}
 
void loop(){
    if (btSerial.available()){
        c = btSerial.read();
        Serial.write(c);
    }
    if (Serial.available()){
        c = Serial.read();

        if (c!=10 & c!=13 ){  
             btSerial.write(c);
        }
        if (NL) { Serial.print("\r\n>");  NL = false; }
        
        Serial.write(c);
        if (c==10) { NL = true; }
    }
    if(digitalRead(A0)){
      btSerial.print("a");
      Serial.println("Avence");
      delay(250);
    }
    if(digitalRead(A1)){
      btSerial.print("s");
      Serial.println("Stop");
      delay(250);
    }
}
