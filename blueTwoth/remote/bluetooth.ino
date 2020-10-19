void connecTo(char *moduleName){
  btSerial.print("AT+IMME1" );
  delay(1000);
  //btSerial.print("AT+ROLE1" );//already done, permanante change
  //delay(1000);
  btSerial.print(moduleName);
  delay(1000);
}
/* Send the values to the motor
 *  Values beetwin 0 and 255
 */
void btSend(int left, int right){
  char values[64];
  sprintf(values, "%d,%d;", left, right);
  btSerial.println(values);
  Serial.println(values);
}

int maper(int value){
  return map(value, -512, 512, -255, 255);
}

/* Main function
 * 
 * Take the values of the joistick from
 * X and Y axis
 */
void masterOperator(int xValue, int yValue){
  int leftPower = 0;
  int rightPower = 0;
  /*
  if(yValue>4 && -4>yValue){
    leftPower = map(xValue, -512, 512, -255, 255);
    rightPower = leftPower;
  }*/
  leftPower = map(xValue, -512, 512, -255, 255);
  rightPower = leftPower;
  
  if(yValue>0){
    if(xValue>0){
      leftPower -= maper(yValue);
    }else{
      leftPower += maper(yValue);
    }
  }else if(yValue<0){
    if(xValue>0){
      rightPower -= maper(-yValue);
    }else{
      rightPower -= maper(yValue);
    }
  }
  char b[16];
  sprintf(b, "L: %d", leftPower);
  oled(b, false, 70, 10);
  sprintf(b, "R: %d", rightPower);
  oled(b, false, 70, 20);
  btSend(leftPower, rightPower);
}
