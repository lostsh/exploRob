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
void btSend(Data *dta){
  Serial.println("[+] Sending datas");
  //btSerial.write((const char*)dta, sizeof(*dta));
  String out = "";
  out += String(dta->yPot)+','+String(dta->xPot)+";";
  btSerial.print(out);
  Serial.println(out);
  delay(100);//ATTTTTTTTTTTTTTTENNNNNNNNNNNNTTTIONNNNNNNNN DELLAY
}

int maper(int value){
  return map(value, -512, 512, -255, 255);
}

/* Main function
 * 
 * Take the values of the joistick from
 * X and Y axis
 */
void masterOperator(){
  if(datas.xPot != maper(val(xPin))){
    datas.xPot = maper(val(xPin));
  }
  if(datas.yPot != maper(val(yPin))){
    datas.yPot = maper(val(yPin));
  }
  btSend(&datas);
}
void masterOperator(int xValue, int yValue){
  int leftPower = 0;
  int rightPower = 0;
  
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
