#include "icon.h"

int mainMenu(){
  int mode = 1;
  bool choosing = true;
  while(choosing){
    box(0);
    if(mode == 1){
      display.drawRect(4, 5, 22, 22, WHITE);
      display.drawRect(101, 5, 22, 22, BLACK);
    }
    if(mode == 2){
      display.drawRect(4, 5, 22, 22, BLACK);
      display.drawRect(101, 5, 22, 22, WHITE);
    }
    display.drawBitmap(5, 6, wheel, 20, 20, WHITE);
    display.drawBitmap(127-25, 6, gear, 20, 20, WHITE);
    if(val(xPin)>10){
      mode=1;
    }else if(val(xPin)<-10){
      mode=2;
    }
    if(digitalRead(A0)) choosing = false;
  }
  delay(200);
  return mode;
}
void driveMenu(){
  oledPrint("driving Menu");
}
void setingMenu(){
  oledPrint("Settings");
}

int menu(int *mode){
  display.clearDisplay();
  switch(*mode){
    case 1:
    driveMenu();
    break;
    default:
    *mode = mainMenu();
    Serial.println(*mode);
    break;
  }
  return *mode;
}

/*=======Graphical things that allow the menu to be a bit less ugly=======*/
void box(int marge){
  box(marge, marge, marge, marge);
}
void box(int mUp, int mRight, int mDown, int mLeft){
  display.drawLine(0+mLeft,0+mUp,127-mRight,0+mUp, SSD1306_WHITE);//line up
  display.drawLine(127-mRight,0+mUp,127-mRight,31-mDown, SSD1306_WHITE);//lige right
  display.drawLine(0+mLeft,31-mDown,127-mRight,31-mDown, SSD1306_WHITE);//line down
  display.drawLine(0+mLeft,0+mUp,0+mLeft,31-mDown, SSD1306_WHITE);//line left
  display.display();
}
