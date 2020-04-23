// This task sets up the Mega Hardware to run tasks according to a timer, and sets serial1 port for communication.
void startupTaskFnc(void* arg) {
  TaskData* localDataPtr = arg;
  Timer1.initialize(100000); // 10 Hz = 100,000 microseconds = 100 milliseconds
  Timer1.attachInterrupt(timerISR);
  HEAD_QUEUE = &measurementTask;
  TCBPtr = HEAD_QUEUE;
  measurementTask.next = &displayTask;
  displayTask.prev = &measurementTask;
  displayTask.next = &socTask;
  socTask.prev = &displayTask;
  socTask.next = &contactorTask;
  contactorTask.prev = &socTask;
  contactorTask.next = &alarmTask;
  alarmTask.prev = &contactorTask;
  alarmTask.next = &remoteTerminalTask;
  remoteTerminalTask.prev = &alarmTask;
  remoteTerminalTask.next = &dataLogTask;
  dataLogTask.prev = &remoteTerminalTask;
  dataLogTask.next = NULL;
  TAIL_QUEUE = &dataLogTask;
  Serial1.begin(9600);
  Serial1.setTimeout(1000);
  Serial.begin(345600);
}
