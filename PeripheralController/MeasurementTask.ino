// Reads an input value from a voltage/current simulator and converts measurement into easily 
// transferrable bytes
void measurementTaskFnc(void* arg){
  sensorVal = analogRead(interruptPin);
  // Separate bytes into last two bits and first eight bits
  payload[0] = highByte(sensorVal);
  payload[1] = lowByte(sensorVal);
}
