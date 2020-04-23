// This task is respoonsible for logging data from the other tasks into the EEPROM "hardrive"
void dataLogTaskFnc(void* arg){
  // Using signed int16 numbers, each piece of information will take up two bytes of memory
  // As such, high voltage currently takes up EEPROM spaces 0 and 1, low voltage -> spaces 2 and 3, and so on and so forth
  byte allValues[24]; 
  byte reset0 = 0x00000000;
  byte reset1 = 0xFFFFFFFF; 
  
  if (resetProm == 1) {
    resetProm = 0;
    // Reset EEPROM values to 0, -1, -1
    EEPROM.write(hivolt1, reset1);
    EEPROM.write(hivolt2, reset1);
    EEPROM.write(hivolt3, reset1);
    EEPROM.write(hivolt4, reset1);

    EEPROM.write(lovolt1, reset1);
    EEPROM.write(lovolt2, reset1);
    EEPROM.write(lovolt3, reset1);
    EEPROM.write(lovolt4, reset1);

    EEPROM.write(hicurr1, reset0);
    EEPROM.write(hicurr2, reset0);
    EEPROM.write(hicurr3, reset0);
    EEPROM.write(hicurr4, reset0);

    EEPROM.write(locurr1, reset0);
    EEPROM.write(locurr2, reset0);
    EEPROM.write(locurr3, reset0);
    EEPROM.write(locurr4, reset0);

    EEPROM.write(hisoc1, reset1);
    EEPROM.write(hisoc2, reset1);
    EEPROM.write(hisoc3, reset1);
    EEPROM.write(hisoc4, reset1);

    EEPROM.write(losoc1, reset1);
    EEPROM.write(losoc2, reset1);
    EEPROM.write(losoc3, reset1);
    EEPROM.write(losoc4, reset1);

    // High Voltage
    allValues[0] = (hi_lo_volt[0] & 0xFF000000) >> 24;
    allValues[1] = (hi_lo_volt[0] & 0x00FF0000) >> 16;
    allValues[2] = (hi_lo_volt[0] & 0x0000FF00) >> 8;
    allValues[3] = (hi_lo_volt[0] & 0x000000FF);

    // Low Voltage
    allValues[4] = (hi_lo_volt[1] & 0xFF000000) >> 24;
    allValues[5] = (hi_lo_volt[1] & 0x00FF0000) >> 16;
    allValues[6] = (hi_lo_volt[1] & 0x0000FF00) >> 8;
    allValues[7] = (hi_lo_volt[1] & 0x000000FF);
    
    // High Current
    allValues[8] = (hi_lo_curr[0] & 0xFF000000) >> 24;
    allValues[9] = (hi_lo_curr[0] & 0x00FF0000) >> 16;
    allValues[10] = (hi_lo_curr[0] & 0x0000FF00) >> 8;
    allValues[11] = (hi_lo_curr[0] & 0x000000FF);

    // Low Current
    allValues[12] = (hi_lo_curr[1] & 0xFF000000) >> 24;
    allValues[13] = (hi_lo_curr[1] & 0x00FF0000) >> 16;
    allValues[14] = (hi_lo_curr[1] & 0x0000FF00) >> 8;
    allValues[15] = (hi_lo_curr[1] & 0x000000FF);

    // High SoC
    allValues[16] = (hi_lo_soc[0] & 0xFF000000) >> 24;
    allValues[17] = (hi_lo_soc[0] & 0x00FF0000) >> 16;
    allValues[18] = (hi_lo_soc[0] & 0x0000FF00) >> 8;
    allValues[19] = (hi_lo_soc[0] & 0x000000FF);

    // Low Current
    allValues[20] = (hi_lo_soc[1] & 0xFF000000) >> 24;
    allValues[21] = (hi_lo_soc[1] & 0x00FF0000) >> 16;
    allValues[22] = (hi_lo_soc[1] & 0x0000FF00) >> 8;
    allValues[23] = (hi_lo_soc[1] & 0x000000FF);

  if (voltChange == '1') {
    EEPROM.write(hivolt1, allValues[0]);
    EEPROM.write(hivolt2, allValues[1]);
    EEPROM.write(hivolt3, allValues[2]);
    EEPROM.write(hivolt4, allValues[3]);    
    voltChange = '0';
  } else if (voltChange == '2') {
    EEPROM.write(lovolt1, allValues[4]);
    EEPROM.write(lovolt2, allValues[5]);
    EEPROM.write(lovolt3, allValues[6]);
    EEPROM.write(lovolt4, allValues[7]);
    voltChange = '0';
  } else {
    // do nothing
  }

  if (currChange == '1') {
    EEPROM.write(hicurr1, allValues[8]);
    EEPROM.write(hicurr2, allValues[9]);
    EEPROM.write(hicurr3, allValues[10]);
    EEPROM.write(hicurr4, allValues[11]);
    currChange = '0';
  } else if (currChange == '2') {
    EEPROM.write(locurr1, allValues[12]);
    EEPROM.write(locurr2, allValues[13]);
    EEPROM.write(locurr3, allValues[14]);
    EEPROM.write(locurr4, allValues[15]);
    currChange = '0';
  } else {

  }

  if (socChange == '1') {
    EEPROM.write(hisoc1, allValues[16]);
    EEPROM.write(hisoc2, allValues[17]);
    EEPROM.write(hisoc3, allValues[18]);
    EEPROM.write(hisoc4, allValues[19]);
    socChange = '0';
  } else if (socChange == '2') {
    EEPROM.write(losoc1, allValues[20]);
    EEPROM.write(losoc2, allValues[21]);
    EEPROM.write(losoc3, allValues[22]);
    EEPROM.write(losoc4, allValues[23]);
    socChange = '0';
  } else {
    // do nothing
  }
  }
  
}
