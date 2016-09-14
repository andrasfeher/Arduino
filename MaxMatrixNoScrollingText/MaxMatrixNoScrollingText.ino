#include "LedControl.h"
 
LedControl lc=LedControl(12,11,10,2);  // Pins: DIN,CLK,CS, # of Display connected
 
unsigned long delayTime=200;  // Delay between Frames
 
// Put values in arrays
byte invader1a[] =
{
   B00011000,  // First frame of invader #1
   B00111100,
   B01111110,
   B11011011,
   B11111111,
   B00100100,
   B01011010,
   B10100101
};
 
unsigned char charBitmapTable[][8] = {

   B00010000,  
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
  
   B00011000,  
   B00111100,
   B01011010,
   B10011001,
   B00011000,
   B00011000,
   B00011000,
   B00011000,

   B00001000,  
   B00000100,
   B00000010,
   B11111111,
   B11111111,
   B00000010,
   B00000100,
   B00001000   
};

 
void setup()
{
  Serial.begin(9600);
  lc.shutdown(0,false);  // Wake up displays
  lc.shutdown(1,false);
  lc.setIntensity(0,1);  // Set intensity levels
  lc.setIntensity(1,1);
  lc.clearDisplay(0);  // Clear Displays
  lc.clearDisplay(1);
  displayChar(0);
}


/*
 * Transposed row = column bitmap
 * Transposed column = row 7 - bitmap
 */

unsigned char* transpose(unsigned char* bitmap){

  unsigned char buffer[8] = {0,0,0,0,0,0,0,0};

  for( unsigned char bitmapRowNr = 0; bitmapRowNr < 8; bitmapRowNr++){

    for (unsigned char bitmapColumnNr = 0; bitmapColumnNr < 8; bitmapColumnNr++){

      if (bitRead(bitmap[bitmapRowNr], bitmapColumnNr) == 1){

        Serial.println(bitmapRowNr);
        Serial.println(bitmapColumnNr);
        Serial.println("---------------");
        
        bitSet(buffer[bitmapColumnNr], 7 - bitmapRowNr);
        
      }

    }
    
  }

  // bitSet(buffer[0], 0);

  return buffer;
   
  
}


 
void displayChar(char c){

  unsigned char* buffer = transpose(charBitmapTable[c]);


  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(0,i,buffer[i]);
  }
  
}
 
void loop()
{
 
}
