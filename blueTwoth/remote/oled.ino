void oledPrint(char* text){
  oledPrint(text, true);
}
void oledPrint(char* text, bool clearDisplay){
  oledPrint(text, clearDisplay, 0, 0);
}
void oledPrint(char* text, int x, int y){
  oledPrint(text, true, x, y);
}
void oledPrint(char* text, bool clearDisplay, int x, int y){
  if(clearDisplay){
    display.clearDisplay();
  }
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(x,y);
  display.println(text);
  display.display();
}
/*Do the same thing but without the display.display();*/
void oled(char* text, bool clearDisplay, int x, int y){
  if(clearDisplay){
    display.clearDisplay();
  }
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(x,y);
  display.println(text);
}

void oledConf(){
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.display();
  delay(1500);
  display.clearDisplay();
}
