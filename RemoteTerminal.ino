// This task handels communication between the Mega and a Remote Terminal, e.g. a connected computer
void remoteTerminalTaskFnc(void* arg) {
    if (printed == 0) {
    printed = 1;
    Serial.println(" ");
    
    Serial.println("[1] Reset EEPROM");
    Serial.println("[2] Operating HV Current Range [Hi, Lo]");
    Serial.println("[3] Operating HV Voltage Range [Hi, Lo]");
    Serial.println(" ");
    Serial.print("Enter your menu choice [1-3]: ");
  }
  // wait for user input from remote terminal
  if (Serial.available() > 0) { // Note: Serial Terminal must be set to 
    eeChar = Serial.read();
  
    Serial.println(eeChar);

    if(eeChar == '1') {
      // Send flag that will reset EEPROM's memory
      resetProm = 1;
      Serial.println("R");      // Debug
    } else if (eeChar == '2') {
      Serial.println("C");      // Debug
      Serial.print(hi_lo_curr[0]);
      Serial.print(", ");
      Serial.println(hi_lo_curr[1]);
      // Print [Hi, Lo] values of current saved on EEPROM
      // through EEProm.read(?) or a new global variable, int[] hi_lo_curr
    } else if (eeChar == '3') {
      Serial.println("V");      // Debug
      Serial.print(hi_lo_volt[0]);
      Serial.print(", ");
      Serial.println(hi_lo_volt[1]);
      // Print [Hi, Lo] values of voltage saved on EEPROM
      // through EEProm.read(?) or a new global variable, int[] hi_lo_volt
    } else {
      // do nothing
    }
    printed = 0;
  }
}
