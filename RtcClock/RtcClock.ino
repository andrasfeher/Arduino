/*
  
  digit selector pins: 11, 10, 9, 8
  segment pins: 1..7 -> G..A, 0: DP

*/
#include <Time.h> 

/* index of decimal point in the character map; the numbers indexes are the same as the numbers */
#define DP 10
#define M  11
#define I  12
#define Y  13
#define D  14
#define H  15
#define R  16


/*
 * mode constants
 */
#define MODE_DISPLAY_HOUR 0
#define MODE_SET_YEAR     1
#define MODE_SET_MONTH    2
#define MODE_SET_DAY      3
#define MODE_SET_HOUR     4
#define MODE_SET_MINUTE   5


#define CHANGE_MODE_BUTTON_PIN 12
#define SET_BUTTON_PIN 13


int digitSelectorPins[] = {11, 10, 9, 8};
int charMap[17][8] = {
//  A  B  C  D  E  F  G  H
  { 7, 6, 5, 4, 3, 2,-1,-1}, // 0
  {-1, 6, 5,-1,-1,-1,-1,-1}, // 1
  { 7, 6,-1, 4, 3,-1, 1,-1}, // 2
  { 7, 6, 5, 4,-1,-1, 1,-1}, // 3
  {-1, 6, 5,-1,-1, 2, 1,-1}, // 4
  { 7,-1, 5, 4,-1, 2, 1,-1}, // 5
  { 7,-1, 5, 4, 3, 2, 1,-1}, // 6
  { 7, 6, 5,-1,-1,-1,-1,-1}, // 7
  { 7, 6, 5, 4, 3, 2, 1,-1}, // 8
  { 7, 6, 5, 4,-1, 2, 1,-1}, // 9
  {-1,-1,-1,-1,-1,-1,-1, 0}, // DP
  { 7,-1, 5,-1, 3,-1,-1,-1}, // M (month, minute)
  {-1,-1,-1,-1, 3, 2,-1,-1}, // I
  {-1, 6, 5, 4,-1, 2, 1,-1}, // Y
  {-1, 6, 5, 4, 3,-1, 1,-1}, // D
  {-1, 6, 5,-1, 3, 2, 1,-1}, // H
  {-1,-1,-1,-1, 3,-1, 1,-1}, // R
  
};

int changeModeButtonState = LOW;
int setButtonState        = LOW;
byte currentMode = MODE_DISPLAY_HOUR;


void showDigit(int segment, int charMapIndex){
  
  digitalWrite(digitSelectorPins[segment], LOW);
  
  for (int i = 0; i < 8; i++){
    if (charMap[charMapIndex][i] > -1){
      digitalWrite(charMap[charMapIndex][i], LOW);
      digitalWrite(charMap[charMapIndex][i], HIGH);
    }
  }
  

  digitalWrite(digitSelectorPins[segment], HIGH);

}


void setup() {

  // initialize serial communications at 9600 bps:
  // Serial.begin(9600);  
  
  // digit selector pins
  for (int i = 0; i < 4; i++){
    pinMode(digitSelectorPins[i], OUTPUT);   
    digitalWrite(digitSelectorPins[i], HIGH);
  }
  
  // segment pins
  for (int i = 0; i < 8; i++){
    pinMode(i, OUTPUT);   
    digitalWrite(i, HIGH);
  }

  pinMode(CHANGE_MODE_BUTTON_PIN, INPUT);
  pinMode(SET_BUTTON_PIN, INPUT);

  setTime(11,24,0,1,1,2016);

}


int getFirstDigit(int twoDigitInt){
  
  if (twoDigitInt == 0 || twoDigitInt < 10){
    return 0;
  } else {
    return (int) twoDigitInt/10;
  }  
}


int getSecondDigit(int twoDigitInt){
  
  if (twoDigitInt == 0){
    return 0;
  } else if (twoDigitInt < 10){
    return twoDigitInt;
  } else {
    return twoDigitInt - ((int) twoDigitInt/10) * 10;
  }  
}



void show(int charCode1, int charCode2, int charCode3, int charCode4, bool showDP){

  // do not show leading zero at first digit
  if (charCode1 != 0){
    showDigit(0, charCode1);
  }

  showDigit(1, charCode2);
  showDigit(2, charCode3);
  showDigit(3, charCode4);    

  if (showDP){
    showDigit(1, DP);
  }
  
}

bool isChangeModeButtonPressed(){

  bool result = false;

  if (digitalRead(CHANGE_MODE_BUTTON_PIN) == HIGH && changeModeButtonState == LOW){
    
    changeModeButtonState = HIGH;

    result = true;
    
  } else if (digitalRead(CHANGE_MODE_BUTTON_PIN) == LOW && changeModeButtonState == HIGH){
    
    changeModeButtonState = LOW;
   
  } 

  return result;
}


bool isSetButtonPressed(){

  bool result = false;

  if (digitalRead(SET_BUTTON_PIN) == HIGH && setButtonState == LOW){
    
    setButtonState = HIGH;

    result = true;
    
  } else if (digitalRead(SET_BUTTON_PIN) == LOW && setButtonState == HIGH){
    
    setButtonState = LOW;
   
  } 

  return result;
}


void changeCurrentMode(){

  if (currentMode == MODE_SET_MINUTE){
    currentMode = MODE_DISPLAY_HOUR;
  } else {
    currentMode++;
  }

}


void loop(){

   show(
      getFirstDigit(hour()), 
      getSecondDigit(hour()), 
      getFirstDigit(minute()), 
      getSecondDigit(minute()),
      true
   );


  if (isChangeModeButtonPressed()){

    changeCurrentMode();
    
  }

  switch (currentMode){

    case MODE_DISPLAY_HOUR:
      show(
        getFirstDigit(hour()), 
        getSecondDigit(hour()), 
        getFirstDigit(minute()), 
        getSecondDigit(minute()),
        true
       );
       break;

    case MODE_SET_YEAR:
      show(Y, R, getFirstDigit(year() - 2000), getSecondDigit(year() - 2000) , false);
      break;
      
    case MODE_SET_MONTH:
      show(M, 0, getFirstDigit(month()), getSecondDigit(month()), false);
      break;
      
    case MODE_SET_DAY:
      show(D, Y, getFirstDigit(day()), getSecondDigit(day()), false);
      break;     
    
    case MODE_SET_HOUR:
      show(H, R, getFirstDigit(hour()), getSecondDigit(hour()), false);
      break;    
    
    case MODE_SET_MINUTE:
      show(M, I, getFirstDigit(minute()), getSecondDigit(minute()), false);
    
  }

  if (isSetButtonPressed() && currentMode != MODE_DISPLAY_HOUR){

    // Serial.println("set button pressed");

    switch (currentMode){
  
      case MODE_SET_YEAR:
        setTime(hour(),minute(),second(),day(),month(),year() + 1);
        break;
        
      case MODE_SET_MONTH:
        setTime(hour(),minute(),second(),day(),month() + 1,year());
        break;
        
      case MODE_SET_DAY:
        setTime(hour(),minute(),second(),day() + 1,month(),year());
        break;     
      
      case MODE_SET_HOUR:
        setTime(hour() + 1,minute(),second(),day(),month(),year());
        break;    
      
      case MODE_SET_MINUTE:
        setTime(hour(),minute() + 1 ,second(),day(),month(),year());
      
    }
    
  }

}
