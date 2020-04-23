//            ALL INCLUDED LIBRARIES



#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>
#include <stdio.h>
#include <TimerOne.h>      // implements timer-based interrupts
#include <EEPROM.h>        // EEPROM "hardrive" functionality



//            ALL DATA STRUCTURES



// TCB block structure
struct MyStruct
{
    void (*myTask)(void*);
    void* taskDataPtr;
    struct MyStruct* next;
    struct MyStruct* prev;
};
typedef struct MyStruct TCB;

// Data structure for TCBs
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
    int* hvIPtr;
    int* hvVPtr;
    
};
typedef struct DataStruct TaskData;

typedef struct
{
  char* contactorPtr;
  int* interruptPtr; 
  int* contactorStatePtr;
} contactorTaskDataStruct;

typedef struct
{
  int* hvilPtr;
  int* hvil_prevPtr;
  int* interruptStatePtr;
  char* contactorPtr;
  int* hvilStatePtr;
} interruptRoutineTaskDataStruct;



//            BOILTERPLATE



// Display
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// additional pins
#define inPin 21    // sets input pin as pin 31
#define outPin 35   // sets output pin as pin 35

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// Color definitions
#define ILI9341_BLACK       0x0000      /*   0,   0,   0 */
#define ILI9341_NAVY        0x000F      /*   0,   0, 128 */
#define ILI9341_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define ILI9341_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define ILI9341_MAROON      0x7800      /* 128,   0,   0 */
#define ILI9341_PURPLE      0x780F      /* 128,   0, 128 */
#define ILI9341_OLIVE       0x7BE0      /* 128, 128,   0 */
#define ILI9341_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define ILI9341_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define ILI9341_BLUE        0x001F      /*   0,   0, 255 */
#define ILI9341_GREEN       0x07E0      /*   0, 255,   0 */
#define ILI9341_CYAN        0x07FF      /*   0, 255, 255 */
#define ILI9341_RED         0xF800      /* 255,   0,   0 */
#define ILI9341_MAGENTA     0xF81F      /* 255,   0, 255 */
#define ILI9341_YELLOW      0xFFE0      /* 255, 255,   0 */
#define ILI9341_WHITE       0xFFFF      /* 255, 255, 255 */
#define ILI9341_ORANGE      0xFD20      /* 255, 165,   0 */
#define ILI9341_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define ILI9341_PINK        0xF81F

/******************* UI details */
#define BUTTON_X 40
#define BUTTON_Y 200
#define BUTTON_W 60
#define BUTTON_H 30
#define BUTTON_SPACING_X 100
#define BUTTON_SPACING_Y 20
#define BUTTON_TEXTSIZE 1

// text box where numbers go
#define TEXT_X 10
#define TEXT_Y 10
#define TEXT_W 220
#define TEXT_H 50
#define TEXT_TSIZE 1
#define TEXT_TCOLOR ILI9341_MAGENTA

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

//Touch For New ILI9341 TP
#define TS_MINX 120
#define TS_MAXX 900

#define TS_MINY 70
#define TS_MAXY 920

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Elegoo_TFTLCD tft;

Elegoo_GFX_Button buttons[5];
/* create 15 buttons, in classic candybar phone style */
char buttonlabels[5][4] = {"<", ">", "On", "Off", "ACK"};
uint16_t buttoncolors[5] = {ILI9341_ORANGE, ILI9341_ORANGE, ILI9341_RED, ILI9341_RED, ILI9341_GREEN};

// EEPROM addresses

// Voltage addresses
#define hivolt1 0
#define hivolt2 1
#define hivolt3 2
#define hivolt4 3

#define lovolt1 4
#define lovolt2 5
#define lovolt3 6
#define lovolt4 7
#define lovolt1 2
#define lovolt2 3

// Current addresses
#define hicurr1 8
#define hicurr2 9
#define hicurr3 10
#define hicurr4 11

#define locurr1 12
#define locurr2 13
#define locurr3 14
#define locurr4 15
#define hicurr1 4
#define hicurr2 5
#define locurr1 6
#define locurr2 7

// SoC addresses
#define hisoc1 16
#define hisoc2 17
#define hisoc3 18
#define hisoc4 19

#define losoc1 20
#define losoc2 21
#define losoc3 22
#define losoc4 23
#define hisoc1 8
#define hisoc2 9
#define losoc1 10
#define losoc2 11



//                GLOBAL VARIABLES



// variables used for TCB linked list
TCB* HEAD_QUEUE;
TCB* TAIL_QUEUE;
TCB* TCBPtr;

// variables used for adding extraneous tasks to scheduler
// (equal to number of cycles corresponding to desired frequency)
const int TERMINAL_FREQUENCY = 10;   // probably wrong
const int DATA_LOG_FREQUENCY = 50;
const int DISPLAY_FREQUENCY  = 10;
bool      FASTER_TOUCH = 0;
int loopCounter = 0;

// variables used for touchscreen 
#define MINPRESSURE 10
#define MAXPRESSURE 1000

// task flags
int acknowledgeFlag = 1;      // Acknowledges changes in alarm state
volatile bool globalFlag = 0; // Timer flag
bool printed = 0;             // determines when to print prompts to remote terminal

// measurement screen variables
int soc = 0;
int temp = 0;
int hvI = 0;
int hvV = 0;
int hvIR = 0;
int hvICOM = 0;
int hvil = 0;       //maybe volatile
int hvil_prev = 0;  // maybe volatile

// alarm variables
char alarm[3][23] = {"NOT ACTIVE             ", "ACTIVE, NOT ACKNOWLEDGE", "ACTIVE, ACKNOWLEDGED   "};
int alarm_row = 3;
int alarm_col = 23;
char contactor[] = "OFF";
const int MIN_CURRENT = -5;
const int MAX_CURRENT = 20;
const int MIN_VOLTAGE = 280;
const int MAX_VOLTAGE = 405;

// scheduler task variables
int queueSize = 7;
const int DEFAULT_LIST_SIZE = 5;
TaskData schedulerTaskData = {};
TCB schedulerTask = {.myTask = &schedulerTaskFnc, .taskDataPtr = &schedulerTaskData};

// transmit task variables
int inbyte1; // Represents last two bits
int inbyte2; // Represents first eight bits
byte holder[2];
TaskData transmitTaskData = {};
TCB transmitTask = {.myTask = &transmitTaskFnc, .taskDataPtr = &transmitTaskData};

// measurement task variables
int hvil_r_volt = 0;
int hvil_r_curr = 0;
int fullVal = 0; // Represents full value

char voltChange = 0; // Flag indicating a change in measurement that needs to be logged into history
                     // 0 -> no change, 1 -> hi volt, 2 -> lo volt
                     // Just realized that this flag needs to be changed; multiple changed variables occuring at once is a real possibility
char currChange = 0;
char socChange = 0;
                      
typedef struct 
{
  int* socPtr;
} measurementTaskDataStruct;
measurementTaskDataStruct measurementTaskData = {.socPtr = &soc};
TCB measurementTask = {.myTask = &measurementTaskFnc, .taskDataPtr = &measurementTaskData};

// display task variables
int hvilState = 0;
int interruptState = 0;
int overIState = 0;
int overVState = 0;
int contactorFlag = 0;
int screen = 0;
TaskData displayTaskData = {.dataPtr1 = &soc, .dataPtr2 = &temp, .dataPtr3 = &hvI, .dataPtr4 = &hvV, 
                            .dataPtr5 = &hvIR, .dataPtr6 = &hvICOM, .dataPtr7 = &hvil, .dataPtr8 = (char*) alarm,
                            .dataPtr9 = contactor, .hvIPtr = &hvil_r_curr, .hvVPtr = &hvil_r_volt}; 
TCB displayTask = {.myTask = &displayTaskFnc, .taskDataPtr = &displayTaskData};

// SoC task variables
double battR = 0.5;
int socTemp[] = {-10, 0, 25,45};
int Voc[] = {200, 250, 300, 350, 400};
int battPerc[4][5] = {{0, 10, 35, 100, 100},
                      {0, 0, 20, 80, 100},
                      {0, 0, 10, 60, 100},
                      {0, 0, 0, 50, 100}};
typedef struct
{
  int* tempPtr;
  int* termVPtr;
  int* termIPtr;
  double* battRPtr;
  int* socPtr;
  int* testVocPtr;
  // pointers for three array. but first just access globally
} socTaskDataStruct;
int testVoc = 305;
int testTemp = 15;
socTaskDataStruct socTaskData = {.tempPtr = &testTemp, .termVPtr = &hvil_r_volt, .termIPtr = &hvil_r_curr, .battRPtr = &battR, .socPtr = &soc, .testVocPtr = &testVoc}; // hardcoding temperature atm
TCB socTask = {.myTask = &socTaskFnc, .taskDataPtr = &socTaskData};

// contactor task variables
int contactorState = 0;
contactorTaskDataStruct contactorTaskData = {.contactorPtr = contactor, .interruptPtr = &interruptState, .contactorStatePtr = &contactorState}; // contactor is request rn
TCB contactorTask = {.myTask = &contactorTaskFnc, .taskDataPtr = &contactorTaskData};

// alarm task variables
typedef struct
{
  int* hvilPtr;           // Pointer for HVIL Interrupt Alarm
  int* hvilStatePtr;      // Pointer for HVIL Alarm
  int* interruptStatePtr; // Pointer for state of interrupt
  int* overIStatePtr;     // Pointer for state of Over-Current Alarm
  int* overVStatePtr;     // Pointer for state of High-Voltage Alarm
  int* hvil_r_voltPtr;    // Pointer for measurement of voltage from simulator circuit
  int* hvil_r_currPtr;    // Pointer for measurement of current from simulator circuit
} alarmTaskDataStruct;

// Remote Terminal variables
char eeChar = 0;          // input from remote terminal
bool resetProm = 1;       // flag to reset EEPROM memory

TaskData remoteTerminalTaskData = {};
TCB remoteTerminalTask = {.myTask = &remoteTerminalTaskFnc, .taskDataPtr = &remoteTerminalTaskData};

int interruptFlag = 0;    // Flag for interrupt function
alarmTaskDataStruct alarmTaskData = {.hvilPtr = &hvil, .hvilStatePtr = &hvilState, .interruptStatePtr = &interruptState, .overIStatePtr = &overIState, .overVStatePtr = &overVState, 
                                      .hvil_r_voltPtr = &hvil_r_volt, .hvil_r_currPtr = &hvil_r_curr};
TCB alarmTask = {.myTask = &alarmTaskFnc, .taskDataPtr = &alarmTaskData};

// interrupt task routine variables
interruptRoutineTaskDataStruct interruptRoutineTaskData = {.hvilPtr = &hvil, .hvil_prevPtr = &hvil_prev, .interruptStatePtr = &interruptState, .contactorPtr = contactor, .hvilStatePtr = &hvilState};
TCB interruptTask = {.myTask = &interruptRoutineTaskFnc, .taskDataPtr = &interruptRoutineTaskData};


// data log task variables
int hi_lo_volt[2];      // hi voltage -> [0], lo voltage -> [1]
int hi_lo_curr[2];      // hi current -> [0], lo current -> [1]
int hi_lo_soc[2];       // hi soc -> [0], lo soc -> [1]
TaskData dataLogTaskData = {};
TCB dataLogTask = {.myTask = &dataLogTaskFnc, .taskDataPtr = &dataLogTaskData};

// Timer Interrupt
void timerISR()
{
   globalFlag = 1;
}


TaskData startupTaskData = {}; 
TCB startupTask = {.myTask = &startupTaskFnc, .taskDataPtr = &startupTaskData};

void fallingEdgeISR() {
  interruptRoutineTaskFnc((void*)(&interruptRoutineTaskData));
}


//            MAIN CODE



void setup(void) {
  Serial.begin(9600);
  
//  Serial.println(F("TFT LCD test"));
  

#ifdef USE_Elegoo_SHIELD_PINOUT
//  Serial.println(F("Using Elegoo 2.4\" TFT Arduino Shield Pinout"));
#else
//  Serial.println(F("Using Elegoo 2.4\" TFT Breakout Board Pinout"));
#endif

//  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();

   uint16_t identifier = tft.readID();
   if(identifier == 0x9325) {
//    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
//    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x4535) {
//    Serial.println(F("Found LGDP4535 LCD driver"));
  }else if(identifier == 0x7575) {
//    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
//    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
//    Serial.println(F("Found HX8357D LCD driver"));
  } else if(identifier==0x0101)
  {     
      identifier=0x9341;
//       Serial.println(F("Found 0x9341 LCD driver"));
  }
  else if(identifier==0x1111)
  {     
      identifier=0x9328;
//       Serial.println(F("Found 0x9328 LCD driver"));
  }
  else {
    identifier=0x9328;
  
  }
  pinMode(inPin, INPUT_PULLUP);     // set input pin logic
  attachInterrupt(digitalPinToInterrupt(inPin), fallingEdgeISR, CHANGE);
  pinMode(outPin, OUTPUT);   // set output pin logic
  
  //digitalWrite(inPin, HIGH); // set pullup resistor in input pin
  tft.begin(identifier);
  tft.setRotation(2);
  tft.fillScreen(BLACK);
  generateButtons();
  
  (*startupTask.myTask)(startupTask.taskDataPtr);
}

void loop() {
  // put your main code here, to run repeatedly:

  if ( 1 == globalFlag )
  {
    // 100 ms have passed
    globalFlag = 0; 
    tft.setCursor(0, 0);
    tft.fillRect(90, 0, 200, 100, ILI9341_BLACK);
    if(interruptFlag == 1) {
      interruptFlag = 0;
      (*displayTask.myTask)(displayTask.taskDataPtr);
    }
    (*schedulerTask.myTask)(schedulerTask.taskDataPtr);
  }
  
  ////////////////////////////////////
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  //pinMode(XP, OUTPUT);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  //pinMode(YM, OUTPUT);

  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  
 // p = ts.getPoint(); 
  /*
  if (ts.bufferSize()) {
    
  } else {
    // this is our way of tracking touch 'release'!
    p.x = p.y = p.z = -1;
  }*/
  
  // Scale from ~0->4000 to tft.width using the calibration #'s
  /*
  if (p.z != -1) {
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
    Serial.print("("); Serial.print(p.x); Serial.print(", "); 
    Serial.print(p.y); Serial.print(", "); 
    Serial.print(p.z); Serial.println(") ");
  }*/
  // touch sensing done here
   if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // scale from 0->1023 to tft.width
    p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
    p.y = (tft.height()-map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
   }
   
  // go thru all the buttons, checking if they were pressed
  for (uint8_t b=0; b<5; b++) {
    if (buttons[b].contains(p.x, p.y)) {
      //Serial.print("Pressing: "); Serial.println(b);
      buttons[b].press(true);  // tell the button it is pressed
    } else {
      buttons[b].press(false);  // tell the button it is NOT pressed
    }
  }

  // now we can ask the buttons if their state has changed
  for (uint8_t b=0; b<5; b++) {
    if (buttons[b].justReleased()) {
      // Serial.print("Released: "); Serial.println(b);
      buttons[b].drawButton();  // draw normal
    }
    
    if (buttons[b].justPressed()) {
      buttons[b].drawButton(true);  // draw invert!
      if(b == 0) {
        screen--;
        if(screen < 0) {
          screen = 2;
        }
      }
      if(b == 1){
        screen = (screen + 1)% 3;
      }

      if(b == 2) {
        strcpy(contactor, "ON ");
      }
      if(b == 3) {
        strcpy(contactor, "OFF");
      }
      if(b == 4) {
        acknowledgeFlag = 1;
        if(hvilState == 1) {
          hvilState = 2;
        }
        if(interruptState == 1) {
          interruptState = 2;
        }
        if(overIState == 1) {
          overIState = 2;
        }
        if(overVState == 1) {
          overVState = 2;
        }

      }
      //tft.fillRect(0, 0, 250, 200, ILI9341_BLACK);
      tft.fillScreen(BLACK);
      generateButtons();  
        
      delay(100); // UI debouncing
    }
  }
}
