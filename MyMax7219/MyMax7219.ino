#include "LedControl.h" //  need the library
LedControl lc=LedControl(12,11,10,1); // lc is our object
// pin 12 is connected to the MAX7219 pin 1
// pin 11 is connected to the CLK pin 13
// pin 10 is connected to LOAD pin 12
// 1 as we are only using 1 MAX7219

int theNumber = 0;
int digitOne = 0;
int digitTwo = 0;
int intensity = 0;
int intensityInterval = 0;

void setup()
{
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0,false);// turn off power saving, enables display
  lc.setIntensity(0,intensity);// sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  
}


void loop()
{

   lc.setDigit(0,0,8,true);
   delay(1000);

   lc.setIntensity(0,intensity);  
   intensity++;

   if( intensity == 16){
    intensity = 0; 
   }

      
/*
    if (theNumber < 0)
      theNumber = 99;
      
    if (theNumber > 9)
    {
      float result = theNumber / 10;  //s/b 4.2 resulting in 4
      digitTwo = result; 
      digitOne = theNumber % 10;  //this gets the remainder of 42/10 or 2
    }
    else
    {
      digitTwo = 0;
      digitOne = theNumber;  
    }
    lc.setDigit(0,0,digitOne,false);  
    // lc.setDigit(0,1,digitTwo,false);
    delay(1000);
    theNumber --;//count down!!
  */ 
}

