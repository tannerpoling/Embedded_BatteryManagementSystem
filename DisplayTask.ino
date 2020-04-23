// This task encapsulates the appearance of screens on the touchscreen
void displayTaskFnc(void* arg) {
    //noInterrupts();
    TaskData* localDataPtr = arg;
    int* field1 = (*localDataPtr).dataPtr1;
    int* field2 = (*localDataPtr).dataPtr2;
    int* field3 = (*localDataPtr).dataPtr3;
    int* field4 = (*localDataPtr).dataPtr4;
    int* field5 = (*localDataPtr).dataPtr5;
    int* field6 = (*localDataPtr).dataPtr6;
    int* field7 = (*localDataPtr).dataPtr7;
    char* field8 = (*localDataPtr).dataPtr8;
    char* field9 = (*localDataPtr).dataPtr9;
    int* hv_current_data = (*localDataPtr).hvIPtr;
    int* hv_voltage_data = (*localDataPtr).hvVPtr;

    // switch to alarm screen if necessary
    //Serial.println("display task"); // Debug line
//    Serial.println(hvilState);
//    Serial.println(interruptState);
//    Serial.println(overIState);
//    Serial.println(overVState);
    if(hvilState == 1 || interruptState == 1 || overIState == 1 || overVState == 1) {
      //generate button
      screen = 2;
      tft.fillScreen(BLACK);
      
      
      generateButtons(); 
      tft.setCursor(0, 0);
      
    } else {
      tft.fillRect(0, 280, 200, 100, ILI9341_BLACK);
    }
    if(screen == 0) {
      tft.print("Charge:          ");
      tft.println(*field1);
      
      tft.print("Temp:            ");
      tft.println(*field2);
      
      tft.print("HV Curr:         ");
      tft.println(*hv_current_data);
      
      tft.print("HV Volt:         ");
      tft.println(*hv_voltage_data);
      
      tft.print("HV Iso R:        ");
      tft.println(*field5);
  
      tft.print("HV IsoClk Mode:  ");
      tft.println(*field6);

      
      tft.print("HVIL Status:     ");
      tft.println(*field7);
    } 
    if(screen == 1) {
      tft.print("Battery Power:   ");
      for(int j = 0; j < sizeof(field9) + 1; j++)
      {
          tft.print(*(field9 + j));
      }
      tft.println("");
    }
    // alarm screen
    if(screen == 2) {
      tft.print("HVIL:           ");
//      tft.print(hvilState);
      for(int j = 0; j < alarm_col; j++)
      {
          tft.print(*((field8 + hvilState*alarm_col)+ j));
      }
      tft.println("");
      tft.print("Interrupt:      ");
//      tft.print(interruptState);
      for(int j = 0; j < alarm_col; j++)
      {
          tft.print(*((field8 + interruptState*alarm_col)+ j));
      }
      tft.println("");
      tft.print("OverI:          ");
      for(int j = 0; j < alarm_col; j++)
      {
          tft.print(*((field8 + overIState*alarm_col)+ j));
      }
      tft.println("");
      tft.print("HighV OoR:      ");
      for(int j = 0; j < alarm_col; j++)
      {
          tft.print(*((field8 + overVState*alarm_col)+ j));
      }
      tft.println("");
   }

    
    delay(1000);
    //interrupts();
}

void generateButtons() {
  int buttonDisplay;
  if(screen == 0 || screen == 2) {
    buttonDisplay = 1;
  } else {
    buttonDisplay = 2;
  }
  for (uint8_t row=0; row<buttonDisplay; row++) {
    for (uint8_t col=0; col<2; col++) {
      buttons[col + row*2].initButton(&tft, BUTTON_X+col*(BUTTON_W+BUTTON_SPACING_X), 
                 BUTTON_Y+row*(BUTTON_H+BUTTON_SPACING_Y),    // x, y, w, h, outline, fill, text
                  BUTTON_W, BUTTON_H, ILI9341_WHITE, buttoncolors[col+row*2], ILI9341_WHITE,
                  buttonlabels[col + row*2], BUTTON_TEXTSIZE); 
      buttons[col + row*2].drawButton();
    }
  }
  if(screen == 2 && (hvilState == 1 || interruptState == 1 || overIState == 1 || overVState == 1)) {
    buttons[4].initButton(&tft, BUTTON_X+0*(BUTTON_W+BUTTON_SPACING_X), 
                 BUTTON_Y+2*(BUTTON_H+BUTTON_SPACING_Y),    // x, y, w, h, outline, fill, text
                  BUTTON_W, BUTTON_H, ILI9341_WHITE, buttoncolors[4], ILI9341_WHITE,
                  buttonlabels[4], BUTTON_TEXTSIZE); 
    buttons[4].drawButton();
  }
  tft.setTextSize(1);
}
