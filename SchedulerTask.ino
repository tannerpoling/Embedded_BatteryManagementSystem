// This task sets up the task schedule as a doubly linked-list
void schedulerTaskFnc(void* arg) {
    
    (*(*TCBPtr).myTask)((*TCBPtr).taskDataPtr);
    
    if ((*TCBPtr).next == NULL) 
    {
      TCBPtr = HEAD_QUEUE;
      loopCounter++;

      // reset the linked list to original form
      while(queueSize > DEFAULT_LIST_SIZE) {
        removeTask(TAIL_QUEUE);
        queueSize--;
        //erial.println("hi");
      }

      // add appropriate tasks based on loopCounter
      if (loopCounter % DATA_LOG_FREQUENCY == 0)
      {
        addTask(&remoteTerminalTask);
        addTask(&dataLogTask);
        queueSize += 2;
      } else if (loopCounter % TERMINAL_FREQUENCY == 0) {
        addTask(&remoteTerminalTask);
        queueSize++;
      }
      
    } else {
      TCBPtr = (*TCBPtr).next;
    }
}

// This task serves to remove tasks from the doubly linked-list.
void removeTask(TCB* currentTask) {
  // three cases: beginning of queue, middle of queue, end of queue
  TCB* prevTask = (*currentTask).prev;
  TCB* nextTask = (*currentTask).next;
  if(prevTask != NULL && nextTask != NULL) {
    // middle of queue
    (*prevTask).next = nextTask;
    (*nextTask).prev = prevTask;
  } else if (prevTask == NULL && nextTask != NULL) {
    // head of queue
    HEAD_QUEUE = nextTask;
    (*nextTask).prev = NULL;
  } else if (prevTask != NULL && nextTask == NULL) {
    // end of queue
    TAIL_QUEUE = prevTask;
    (*prevTask).next = NULL;
  } else {
    // only task in queue
    HEAD_QUEUE = NULL;
    TAIL_QUEUE = NULL;
  }
  TCBPtr = HEAD_QUEUE;
}

// This task serves to add a task onto the END of a doubly-linked list
void addTask(TCB* currentTask) {
//  TCB* prevTask = (*currentTask).prev;
//  TCB* nextTask = (*currentTask).next;
//    // end of queue
  (*currentTask).prev = TAIL_QUEUE;
  TAIL_QUEUE = currentTask;
  (*currentTask).next = NULL;
  TCBPtr = HEAD_QUEUE;
}



//// This task serves to remove tasks from the doubly linked-list.
//// Requires previous and next TCB addresses to be given
//void newRemoveTask(TCB* currentTask, TCB* prevTask, TCB* nextTask) {
//  // three cases: beginning of queue, middle of queue, end of queue
//  if(prevTask != NULL && nextTask != NULL) {
//    // middle of queue
//    (*prevTask).next = nextTask;
//    (*nextTask).prev = prevTask;
//  } else if (prevTask == NULL && nextTask != NULL) {
//    // head of queue
//    HEAD_QUEUE = nextTask;
//    (*nextTask).prev = NULL;
//  } else if (prevTask != NULL && nextTask == NULL) {
//    // end of queue
//    TAIL_QUEUE = prevTask;
//    (*prevTask).next = NULL;
//  } else {
//    // only task in queue
//    HEAD_QUEUE = NULL;
//    TAIL_QUEUE = NULL;
//  }
//  TCBPtr = HEAD_QUEUE;
//}
//
//// This task serves to add a task back into the doubly linked-list.
//// Requires previous and next TCB addresses to be given
//void newAddTask(TCB* currentTask, TCB* prevTask, TCB* nextTask) {
//  if(prevTask != NULL && nextTask != NULL) {
//    // middle of queue
//    (*prevTask).next = currentTask;
//    (*nextTask).prev = currentTask;
//  } else if (prevTask == NULL && nextTask != NULL) {
//    // head of queue
//    HEAD_QUEUE = currentTask;
//    (*nextTask).prev = currentTask;
//  } else if (prevTask != NULL && nextTask == NULL) {
//    // end of queue
//    TAIL_QUEUE = currentTask;
//    (*prevTask).next = currentTask;
//  } else {
//    // only task in queue
//    HEAD_QUEUE = currentTask;
//    TAIL_QUEUE = currentTask;
//  }
//  TCBPtr = HEAD_QUEUE;
//}
//
//
//
//
//
//// test code for adding and removing tasks
//
//void test_TCB1(void* arg) {
//  Serial.println("A");
//}
//TaskData test1Data = {};
//TCB test1 = {.myTask = &test_TCB1, .taskDataPtr = &test1Data};
//
//void test_TCB2(void* arg) {
//  Serial.println("B");
//}
//TaskData test2Data = {};
//TCB test2 = {.myTask = &test_TCB2, .taskDataPtr = &test2Data};
//
//void test_TCB3(void* arg) {
//  Serial.println("C");
//}
//TaskData test3Data = {};
//TCB test3 = {.myTask = &test_TCB3, .taskDataPtr = &test3Data};
//
//void test_add_remove() {
//  HEAD_QUEUE = &test1;
//  test1.next = &test2;
//  test1.prev = NULL;
//  test2.prev = &test1;
//  test2.next = &test3;
//  test3.prev = &test2;
//  test3.next = NULL;
//  TAIL_QUEUE = &test3;
//  TCBPtr = HEAD_QUEUE;
//
//  (*schedulerTask.myTask)(schedulerTask.taskDataPtr);
//  (*schedulerTask.myTask)(schedulerTask.taskDataPtr);
//  (*schedulerTask.myTask)(schedulerTask.taskDataPtr);
//  Serial.println("FIRST LOOP DONE, DESIRED OUTPUT: A B C");
//  removeTask(&test1);
//  Serial.println("A REMOVED");
//  Serial.println("RUN HEAD QUEUE:");
//  (*(*HEAD_QUEUE).myTask)((*HEAD_QUEUE).taskDataPtr);
//  Serial.println("RUN HEAD.next");
//  (*(*(*HEAD_QUEUE).next).myTask)((*(*HEAD_QUEUE).next).taskDataPtr);
//  Serial.println("RUN TCBPtr");
//  (*(*TCBPtr).myTask)((*TCBPtr).taskDataPtr);
//  Serial.println("RUN SCHEDULER:");
//  (*schedulerTask.myTask)(schedulerTask.taskDataPtr);
//  (*schedulerTask.myTask)(schedulerTask.taskDataPtr);
//  Serial.println("SECOND LOOP DONE, DESIRED OUTPUT: B C");
//  addTask(&test1);
//  (*schedulerTask.myTask)(schedulerTask.taskDataPtr);
//  (*schedulerTask.myTask)(schedulerTask.taskDataPtr);
//  (*schedulerTask.myTask)(schedulerTask.taskDataPtr);
//  Serial.println("THIRD LOOP DONE, DESIRED OUTPUT: A B C");
//  removeTask(&test2);
//  (*schedulerTask.myTask)(schedulerTask.taskDataPtr);
//  (*schedulerTask.myTask)(schedulerTask.taskDataPtr);
//  Serial.println("FOURTH LOOP DONE, DESIRED OUTPUT: A C");
//  removeTask(&test3);
//  (*schedulerTask.myTask)(schedulerTask.taskDataPtr);
//  Serial.println("FIFTH LOOP DONE, DESIRED OUTPUT: A");
//}
