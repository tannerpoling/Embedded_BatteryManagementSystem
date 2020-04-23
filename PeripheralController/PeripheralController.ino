//            ALL INCLUDED LIBRARIES


// 
#include <stdio.h>
#include <SoftwareSerial.h> 
#include <stdint.h>
#include <TimerOne.h>



//            ALL DATA STRUCTURES


#define interruptPin A2

// TCB block structure
struct MyStruct
{
    void (*myTask)(void*);
    void* taskDataPtr;
    struct MyStruct* next;
    struct MyStruct* prev;
};
typedef struct MyStruct TCB;

TCB* tcb_linked_list;

struct DataStruct
{
    // data pointers
    int* dataPtr1;
    int* dataPtr2;
    int* dataPtr3;
    int* dataPtr4;
    int* dataPtr5;
    int* dataPtr6;
    int* dataPtr7;
    char* dataPtr8;
    char* dataPtr9;
    
};
typedef struct DataStruct TaskData;



//            GLOBAL VARIABLES

// Global Timer Flag
volatile bool globalFlag = 0;
volatile bool requestData = 0;

// variables used for TCB linked list
TCB* HEAD_QUEUE;
TCB* TAIL_QUEUE;
TCB* TCBPtr;
const int TASK_FREQUENCY = 5; // fill in with details for whatever task desired.
                              // number = number of cycles between each operation of task
int loopCounter = 0;



//            FUNCTIONS



// scheduler TCB
const int DEFAULT_LIST_SIZE = 1;
int listSize = 1;
TaskData schedulerTaskData = {};
TCB schedulerTask = {.myTask = &schedulerTaskFnc, .taskDataPtr = &schedulerTaskData};

// measurement TCB
unsigned int sensorVal = 0;
byte payload[2];  
TaskData measurementTaskData = {};
TCB measurementTask = {.myTask = &measurementTaskFnc, .taskDataPtr = &measurementTaskData};

// transmit task TCB
TaskData transmitTaskData = {};
TCB transmitTask = {.myTask = &transmitTaskFnc, .taskDataPtr = &transmitTaskData};

// This waits for a "TRUE" serial signal, then calls transmit task
void serialEvent() {
  (*transmitTask.myTask)(transmitTask.taskDataPtr);
  requestData = Serial.read(); // Reads TRUE signal to ensure buffer empties

}

// startup task TCB
TaskData startupTaskData = {}; 
TCB startupTask = {.myTask = &startupTaskFnc, .taskDataPtr = &startupTaskData};



//            MAIN CODE


void setup() {
  // put your setup code here, to run once:
  // set pin value to input & creates pullup resistor
  pinMode(interruptPin, INPUT_PULLUP);
  (*startupTask.myTask)(startupTask.taskDataPtr);
  
}

void loop() {
  if ( 1 == globalFlag)
  {
    globalFlag = 0;

    (*schedulerTask.myTask)(schedulerTask.taskDataPtr);
    //if (requestData == 1) {  
      //  (*transmitTask.myTask)(transmitTask.taskDataPtr);
    //}
  }

}

// Timer Interrupt
void timerISR()
{
   globalFlag = 1;
}
