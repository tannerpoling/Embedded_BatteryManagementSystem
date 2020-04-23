// This task encapsulates the states and state change criteria for the alarm screen.
void alarmTaskFnc(void* arg) {
  //Serial.println("alarm"); // Debug line
  
  alarmTaskDataStruct* localDataPtr = arg;
  int* hvilData = (*localDataPtr).hvilPtr;                     // Pointer to state of change of hvil circuit
  int* hvilStateData =(*localDataPtr).hvilStatePtr;            // Pointer to state of hvil circuit
  int* interruptStateData = (*localDataPtr).interruptStatePtr; // Pointer to state of interrupt pin
  int* overIStateData = (*localDataPtr).overIStatePtr;         // Pointer to state of current simulator circuit
  int* overVStateData = (*localDataPtr).overVStatePtr;         // Pointer to state of voltage simulator circuit
  int* hvil_r_voltData = (*localDataPtr).hvil_r_voltPtr;       // Pointer to voltage measurement from voltage simulator circuit
  int* hvil_r_currData = (*localDataPtr).hvil_r_currPtr;       // Pointer to current measurement from current simulator circuit

  // HVIL alarm
  if(*hvilData == 1 && *hvilStateData == 0) {
    *hvilStateData = 1;
  } 
  if(*hvilStateData == 2 && *hvilData == 0) {
    *hvilStateData = 0;
  }

  //HVIL interrupt alarm
  if(*hvilData == 0 && *interruptStateData == 2) {
    *interruptStateData = 0;
  }

  //overI alarm
  if((*hvil_r_currData <= MIN_CURRENT || *hvil_r_currData >= MAX_CURRENT) && acknowledgeFlag == 1 && *overIStateData == 0) {
    *overIStateData = 1;
    //acknowledgeFlag = 0;
    //Serial.println(*overIStateData); // Debug line
  } 
  if(*overIStateData == 2 && *hvil_r_currData > MIN_CURRENT && *hvil_r_currData < MAX_CURRENT) {
    *overIStateData = 0;
  }
  //overV alarm
  //Serial.println("test enter"); // Debug line
  if((*hvil_r_voltData <= MIN_VOLTAGE || *hvil_r_voltData >= MAX_VOLTAGE) && acknowledgeFlag == 1 && *overVStateData == 0) {
    //Serial.println("enter success"); // Debug line
    *overVStateData = 1;
    acknowledgeFlag = 0;
    //Serial.println(*overVStateData); // Debug line
 
  } 
  if(*overVStateData == 2 && *hvil_r_voltData > MIN_VOLTAGE && *hvil_r_voltData < MAX_VOLTAGE) {
    *overVStateData = 0;
  }
}
