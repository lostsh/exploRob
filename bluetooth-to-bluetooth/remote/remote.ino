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

//for OLED 128x32
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET 4 // SDA - Arduino pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
void setup(){
    Serial.begin(9600);
    btSerial.begin(9600);  
    Serial.println("btSerial started at 9600");
    /*
    btSerial.print("AT+IMME1" );
    delay(1000);
    //btSerial.print("AT+ROLE1" );
    //delay(1000);
    btSerial.print("AT+CON90E2028DDAFC" );
    delay(1000);
    */

    //OLED conf
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
      Serial.println(F("SSD1306 allocation failed"));
      for (;;); // Don't proceed, loop forever
    }
    display.display();
    delay(5000);
    display.clearDisplay();
}

void loop(){
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println(F("Hello, world!"));
  display.display();
  delay(5000);
  
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
