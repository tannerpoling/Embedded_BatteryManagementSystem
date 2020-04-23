void transmitTaskFnc(void* arg) { 
  Serial1.write(1);
  while(Serial1.available() < 2)
  {

  }
  holder[0] = Serial1.read();
  holder[1] = Serial1.read();
}
