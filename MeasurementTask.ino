// This task measures the state of the hvil input pin and maps current and voltage from the 
// simulator circuit.
void measurementTaskFnc(void* arg) {
  measurementTaskDataStruct* localDataPtr = arg;
  int* socData = (*localDataPtr).socPtr;
  //Serial.println("measurement"); // Debug line
  hvil_prev = hvil;
  hvil = digitalRead(inPin); // reads state of input pin
  // ask secondary board to get value from input pin
  // current implementation: secondary board will read input pin when system controller
  //    sends ANY value across the serial comms. 
  (*transmitTask.myTask)(transmitTask.taskDataPtr);
  
  int fullVal_prev = fullVal; // Saves previous current/voltage in case of glitch
  fullVal = (holder[0] << 8) + holder[1]; // Update current/voltage measurement
  
  // Checks if fullVal has glitched 
  if (fullVal == 0)
  {
    fullVal = fullVal_prev;
  }
  
  // obtain value from secondary board, convert to hvil values
  hvil_r_volt = map(fullVal, 0, 1023, 0, 450); // Maps sensor data to voltage values
  
  
  // Convert input to current
  hvil_r_curr = map(fullVal, 0, 1023, -25, 25); // Maps sensor data to current values
  
  if (resetProm == 1) {
    //reset values here
    hi_lo_curr[0] = 0;
    hi_lo_curr[1] = 0;
    hi_lo_volt[0] = -1;
    hi_lo_volt[1] = -1;
    hi_lo_soc[0] = -1;
    hi_lo_soc[1] = -1;
    resetProm = 0; 
  } else {
    if (hvil_r_volt > hi_lo_volt[0]) {
      hi_lo_volt[0] = hvil_r_volt;
      voltChange = '1'; 
    }
    if(hi_lo_volt[1] == -1) {
      hi_lo_volt[1] = hvil_r_volt;
    }
    if (hvil_r_volt < hi_lo_volt[1]) {
      hi_lo_volt[1] = hvil_r_volt;
      voltChange = '2';
    }
    if (hvil_r_curr > hi_lo_curr[0]) {
      hi_lo_curr[0] = hvil_r_curr;
      currChange = '1'; 
    }
    if (hvil_r_curr < hi_lo_curr[1]) {
      hi_lo_curr[1] = hvil_r_curr;
      currChange = '2';
    }
    
    if (*socData > hi_lo_soc[0]) {
      hi_lo_soc[0] = *socData;
      socChange = '1'; 
    }
    if(hi_lo_soc[1] == -1) {
      hi_lo_soc[1] = *socData;
    }
    if (*socData < hi_lo_soc[1]) {
      hi_lo_soc[1] = *socData;
      socChange = '2';
    }
   
  }
  // flush serial just to make sure we arent requesting info all the time
  Serial1.flush();
}
