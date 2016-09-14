//We always have to include the library
#include "LedControl.h"

#define MODULE_NR 5

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,11,10,MODULE_NR);

/* we always wait a bit between updates of the display */
unsigned long delaytime=2000;

byte bufIndex;
byte buf[MODULE_NR * 8];
byte displayDay = -1;

void setup() {

  Serial.begin(9600);

  for (byte moduleId = 0; moduleId < MODULE_NR; moduleId++){

    lc.shutdown(moduleId,false);
    lc.setIntensity(moduleId,1);
    lc.clearDisplay(moduleId);
  }
  

  
}

void initBuf(){

  bufIndex = 0;

  for (byte i = 0; i < sizeof(buf); i++){

    buf[i] = B00000000;
    
  }
  
}


void addCharToBuf(byte charmap[], byte charmapSize){

  if (bufIndex > 0){

    bufIndex++;
    
  }
  
  for (byte i = 0; i < charmapSize; i++){

    buf[bufIndex] = charmap[i];
    bufIndex++;
    
  }
  
}

void centerStringInBuffer(){

  for (byte i = 0; i < (byte) (MODULE_NR * 8 - bufIndex)/2; i++){
    
  }

}


void displayBuffer(){

  for (int i = 0; i < sizeof(buf); i++){
    
    byte moduleNr = (int) i/8;
    
    lc.setRow(moduleNr, i -(moduleNr * 8), buf[i]);
  }  
  
}

/*
 This method will display the characters for the
 word "Arduino" one after the other on the matrix. 
 (you need at least 5x7 leds to see the whole chars)
 */
void writeArduinoOnMatrix(byte dayToDisplay) {
  /* here is the data for the characters */
  byte a[]       = {B00100000, B01010100, B01010100, B01111000};
  byte aacute[]  = {B00100000, B01010110, B01010101, B01111000}; // á
  byte b[]       = {B01111111, B01000100, B01000100, B00111000};
  byte C[]       = {B00111110, B01000001, B01000001, B00100010};
  byte d[]       = {B00111000, B01000100, B01000100, B01111111};
  byte e[]       = {B00111000, B01010100, B01010100, B00011000};
  byte eacute[]  = {B00111000, B01010110, B01010101, B00011000}; // é
  byte f[]       = {B00000100, B01111110, B00000101};
  byte H[]       = {B01111111, B00001000, B00001000, B01111111};
  byte K[]       = {B01111111, B00001000, B00010100, B01100011};
  byte k[]       = {B01111111, B00010000, B00101000, B01000100};
  byte m[]       = {B01111100, B00000100, B01111100, B00000100, B01111000};
  byte n[]       = {B01111100, B00000100, B00000100, B01111000};
  byte o[]       = {B00111000, B01000100, B01000100, B00111000};
  byte ouml[]    = {B00111000, B01000101, B01000101, B00111000}; // ö
  byte oumla[]   = {B00111000, B01000110, B01000111, B00111001};  // ő
  byte P[]       = {B01111111, B00001001, B00001001, B00000110};
  byte p[]       = {B11111100, B00100100, B00100100, B00011000};
  byte r[]       = {B01111100, B00001000, B00000100, B00000100};
  byte S[]       = {B01000110, B01001001, B01001001, B00110010};
  byte s[]       = {B01001000, B01010100, B01010100, B00100100};
  byte t[]       = {B00000100, B00111111, B01000100};
  byte u[]       = {B00111100, B01000000, B01000000, B01111100}; // ü
  byte uuml[]    = {B00111100, B01000001, B01000001, B01111100}; // ü
  byte V[]       = {B00001111, B00110000, B01000000, B00110000, B00001111};
  byte z[]       = {B01100100, B01010100, B01001100};  
  byte spacer[]  = {B00000000};


  unsigned int string[][9] = {
    {'V','a','s','á','r','n','a','p',' '},
    {'H','é','t','f','ő',' ',' ',' ',' '},
    {'K','e','d','d',' ',' ',' ',' ',' '},
    {'S','z','e','r','d','a',' ',' ',' '},
    {'C','s','ü','t','ö','r','t','ö','k'},
    {'P','é','n','t','e','k',' ',' ',' '},
    {'S','z','o','m','b','a','t',' ',' '}
   };

  
  
  initBuf();

  for (byte i = 0; i < (sizeof(string[0]) / sizeof(unsigned int)); i++){

    switch (string[dayToDisplay][i]){
     case 'a': addCharToBuf(a, sizeof(a)); break;
     case 'b': addCharToBuf(b, sizeof(b)); break;
     case 'C': addCharToBuf(C, sizeof(C)); break;
     case 'd': addCharToBuf(d, sizeof(d)); break;
     case 'e': addCharToBuf(e, sizeof(e)); break;
     case 'f': addCharToBuf(f, sizeof(f)); break;
     case 'H': addCharToBuf(H, sizeof(H)); break;
     case 'K': addCharToBuf(K, sizeof(K)); break;
     case 'k': addCharToBuf(k, sizeof(k)); break;
     case 'm': addCharToBuf(m, sizeof(m)); break;
     case 'n': addCharToBuf(n, sizeof(n)); break;
     case 'o': addCharToBuf(o, sizeof(o)); break;
     case 'P': addCharToBuf(P, sizeof(P)); break;
     case 'p': addCharToBuf(p, sizeof(p)); break;
     case 'r': addCharToBuf(r, sizeof(r)); break;
     case 'S': addCharToBuf(S, sizeof(S)); break;
     case 's': addCharToBuf(s, sizeof(s)); break;
     case 't': addCharToBuf(t, sizeof(t)); break;
     case 'u': addCharToBuf(u, sizeof(u)); break;
     case 'V': addCharToBuf(V, sizeof(V)); break;
     case 'z': addCharToBuf(z, sizeof(z)); break;
     case ' ': addCharToBuf(spacer, sizeof(spacer)); break;
     case 50081: addCharToBuf(aacute, sizeof(aacute)); break; // á
     case 50089: addCharToBuf(eacute, sizeof(eacute)); break; // é
     case 50102: addCharToBuf(ouml,   sizeof(ouml)); break;
     case 50577: addCharToBuf(oumla,  sizeof(oumla)); break;
     case 50108: addCharToBuf(uuml,   sizeof(uuml)); break;        
    }
    
  }


  centerStringInBuffer();
  

  displayBuffer();  
}


void loop() { 

  displayDay++;
  
  if (displayDay == 7) {
    displayDay = 0;
  }
  
  writeArduinoOnMatrix(displayDay);

  delay(2000);


}
