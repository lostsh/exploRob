void connecTo(char *moduleName){
  btSerial.print("AT+IMME1" );
  delay(1000);
  //btSerial.print("AT+ROLE1" );//already done, permanante change
  //delay(1000);
  btSerial.print(moduleName);
  delay(1000);
}
