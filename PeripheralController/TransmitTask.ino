// Writes both bytes of data to the System Controller
void transmitTaskFnc(void* arg) {
  // Send both to Mega sequentially
  Serial.write(payload[0]);
  Serial.write(payload[1]);
  
}
