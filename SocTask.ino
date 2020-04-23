void socTaskFnc(void* arg) {
  //nothing
  //Serial.println("SOC"); // Debug line
  socTaskDataStruct* localDataPtr = arg;
  int* tempData = (*localDataPtr).tempPtr;
  int* termVData = (*localDataPtr).termVPtr;
  int* termIData = (*localDataPtr).termIPtr;
  double* battRData = (*localDataPtr).battRPtr;
  int* socData = (*localDataPtr).socPtr;
  int* testVocData = (*localDataPtr).testVocPtr;

//  double currVoc = (*termVData) + (*battRData)*(*termIData);
  double currVoc = (double) (*testVocData);
  int row = 0;
  int col = 0;
  while(row < 4 - 1) {
    if(socTemp[row] <= *tempData && socTemp[row+1] >= *tempData) {
      break;
    }
    row++;
  }
  while(col < 5 -1) {
    if(Voc[col] <= currVoc && Voc[col+1] >= currVoc) {
      break; 
    }
    col++;
  }

  double tempDiff = *tempData - socTemp[row];
  double tempRange = socTemp[row+1] - socTemp[row];
  double pwrRange1 = battPerc[row][col] - battPerc[row+1][col];
  double value1 = battPerc[row][col] - (pwrRange1 * tempDiff / tempRange);

  double pwrRange2 = battPerc[row][col+1] - battPerc[row+1][col+1];
  double value2 = battPerc[row][col+1] - (pwrRange2 * tempDiff / tempRange);

  double voltageDiff = currVoc - Voc[col];
  double voltageRange = Voc[col+1] - Voc[col];
  double valueRange = value2 - value1;
  double result = value1 + (valueRange * voltageDiff / voltageRange);
  *socData = (int) result;
  //Serial.println(*socData);
}
