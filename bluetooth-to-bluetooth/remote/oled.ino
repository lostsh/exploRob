void oledPrint(char* text){
  oledPrint(text, true);
}
void oledPrint(char* text, bool clearDisplay){
  oledPrint(text, clearDisplay, 0, 0);
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
