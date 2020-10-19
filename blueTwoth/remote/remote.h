//for BLE 4.0
#include <SoftwareSerial.h>

//for OLED 128x32
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET 4 // SDA - Arduino pin

/*
I use prototypes of function on the wront header file I know it and that's all
*/

//============prototypes===============
//oled
void oledConf();
void oledPrint(char*);
void oledPrint(char*, bool);
void oledPrint(char*, int, int);
void oledPrint(char*, bool, int, int);
void oled(char*, bool, int, int);
//menu
void menu(int*);
void box(int);
void box(int, int, int, int);
