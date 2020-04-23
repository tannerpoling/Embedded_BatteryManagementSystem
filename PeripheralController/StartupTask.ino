void startupTaskFnc(void* arg) {

  Timer1.initialize(100000); // 10 Hz = 100,000 microseconds

  Timer1.attachInterrupt(timerISR);
  
  //Timer1.start();
  
  TaskData* localDataPtr = arg;
  HEAD_QUEUE = &measurementTask;
  TCBPtr = HEAD_QUEUE;
  measurementTask.next = NULL;
  measurementTask.prev = NULL;
  TAIL_QUEUE = &measurementTask;
  Serial.begin(9600);
  Serial.setTimeout(1000);
}
