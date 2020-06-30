/*
 * Note a moi même :
 * penser a ajouter l'affichage de l'ecrant
 * sur l'ecrant on aura plusieurs modes 
 * avec plusieurs vitesses, un omde de pressision et un mode de franchissenement
 * ensuite on pourra affichier l'êtat de la battierie sur l'ecrant
 * et enfin si possible l'etat du signal bluetooth
*/
#include "remote.h"
SoftwareSerial btSerial(2, 3);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//char c=' ';
//boolean NL = true;

const unsigned int xPin = A2;
const unsigned int yPin = A3;
unsigned int init_value;

void setup(){
    Serial.begin(9600);

    //Joistick
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
    init_value = (analogRead(xPin)+analogRead(yPin))/2;

    //OLED 128x32 configuration
    oledConf();
    
    btSerial.begin(9600);  
    Serial.println("btSerial started at 9600");
    connecTo("AT+CON90E2028DDAFC");
    if(btSerial.readString().indexOf("CONNA")>-1){
      oledPrint("Connection OK");
    }else{
      oledPrint("Connection Failed");
    }
    delay(1000);
    display.clearDisplay();
}

int val(int pinNumer){
  return (analogRead(pinNumer)-init_value);
}

unsigned int mode = 0;
void loop(){
  switch(mode){
    case 1:
    oledPrint("You are now in drive mode");
    delay(500);
    mode = 0;
    break;
    default:
    mode = menu(&mode);
    break;
  }
  /*
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
    */
    /*
    if(digitalRead(A0)){
      btSerial.print("a");
      oledPrint("Avence");
      delay(250);
    }
    if(digitalRead(A1)){
      btSerial.print("s");
      oledPrint("Stop");
      delay(250);
    }
    */
}
