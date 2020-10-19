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

Data datas;

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
    menu(&mode);
    break;
    default:
    menu(&mode);
    break;
  }
}
