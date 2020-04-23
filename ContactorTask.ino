// This task encapsulates the functions related to the simulated contactor circuit.
void contactorTaskFnc(void* arg) {
  //Serial.println("contactor"); // Debug line
  
  contactorTaskDataStruct* localDataPtr = arg;
  char* contactorValue = (*localDataPtr).contactorPtr;          // Pointer to value found at contactor's output pin
  int* interruptStateData = (*localDataPtr).interruptPtr;       // Pointer to state of interrupt pin
  int* contactorStateData = (*localDataPtr).contactorStatePtr;  // Pointer to state of contactor circuit
  if(*interruptStateData == 1 || *interruptStateData == 2) {
    *contactorStateData = 0;
  }
  // Turns off contactor circuit if interrupt routine is started
  if(*interruptStateData == 0 && strcmp(contactorValue, "ON ") == 0) {
    *contactorStateData = 1;
  }
  // Allows user to turn contactor circuit on or off on Battery Screen
  if(strcmp(contactorValue, "ON ") == 0) {
    digitalWrite(outPin, HIGH);
  }else{
    digitalWrite(outPin, LOW);
  }
  
}
