// This task activates a hardware interrupt in response to a change in the hvil circuit's state.
void interruptRoutineTaskFnc(void * arg) {
  interruptFlag = 1;
  interruptRoutineTaskDataStruct* localDataPtr = arg;
  char* value = (*localDataPtr).contactorPtr;
  int* hvilData = (*localDataPtr).hvilPtr;
  int* hvil_prevData = (*localDataPtr).hvil_prevPtr;
  int* interruptStateData = (*localDataPtr).interruptStatePtr;
  int* hvilStateData = (*localDataPtr).hvilStatePtr;
  *hvil_prevData = *hvilData;
  *hvilData = digitalRead(inPin);
  if(*hvil_prevData == 0 && *hvilData == 1) {
    *interruptStateData = 1;
    digitalWrite(outPin, LOW);
    strcpy(value, "OFF");
  }   
}
