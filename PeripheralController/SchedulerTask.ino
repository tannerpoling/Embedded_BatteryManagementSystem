void schedulerTaskFnc(void* arg) { 
    
  (*(*TCBPtr).myTask)((*TCBPtr).taskDataPtr);
    
  if ((*TCBPtr).next == NULL) 
    {
      TCBPtr = HEAD_QUEUE;
      loopCounter++;

      // reset the linked list to original form

      // add appropriate tasks based on loopCounter
      
    } else {
      TCBPtr = (*TCBPtr).next;
    }

//    TCBPtr = queue[taskIndex];
//    (*(*TCBPtr).myTask)((*TCBPtr).taskDataPtr);
//    taskIndex = (taskIndex + 1)%5;  
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
