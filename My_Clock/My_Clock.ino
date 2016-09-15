#include <Time.h>
#include <TimeLib.h>

/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

#define SET_BUTTON 1
#define INCREASE_BUTTON 2
#define STATE_DISPLAY_TIME 0
#define STATE_SET_HOUR 1
#define STATE_SET_MINUTE 2


// initialize the library with the numbers of the interface pins
// LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
byte state;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(SET_BUTTON, INPUT);
  pinMode(INCREASE_BUTTON, INPUT);
  
  setTime(1448801160);
  state = STATE_DISPLAY_TIME;

  
  // Print a message to the LCD.
  // lcd.print("12:00");
}

void loop() {

  Serial.println(state);
  
  if (digitalRead(SET_BUTTON)){
    lcd.clear();
    
    if (state == STATE_SET_MINUTE){
      state = STATE_DISPLAY_TIME;
    } else {
      state++;
    }
  }

  if (state == STATE_SET_HOUR){
    displaySetHour();
  } else if (state == STATE_SET_MINUTE){
    displaySetMinute();    
  }else {
     displayTime();
  }

  delay(500);        // delay in between reads for stability

}

void displaySetHour(){
  lcd.setCursor(0, 0);
  lcd.print("Hour :");
  
}

void displaySetMinute(){
  lcd.setCursor(0, 0);
  lcd.print("Minute :");
  
}


void displayTime(){

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(4, 0);
  lcd.print(getTimeString(hour(), minute(), second()));

  lcd.setCursor(0, 1);
  lcd.print(getDateSring(year(), month(), day(), weekday()));
  
}

String getTimeString(int hour, int minute, int second){

  return getFormattedDigit(hour) + ":" + getFormattedDigit(minute) + ":" + getFormattedDigit(second);
  
}

String getDateSring(int year, int month, int day, int weekDay){
  
   return getFormattedDigit(year) + "." + getFormattedDigit(month) + "." + getFormattedDigit(day) + " " + getWeekDayStr(weekDay);
}

String getFormattedDigit(int digit){

  if (digit < 10){
    return (String) "0" + digit;
  } else {
    return (String) "" + digit;
  }
}

String getWeekDayStr(int weekDay){

  char *weekDayList[7] = {
    "Szo", "Vas", "Het", "Kedd", "Sze", "Csut", "Pent" 
  };

  return weekDayList[weekDay];
}


