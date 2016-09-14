/*
  Button
 
 Turns on and off a light emitting diode(LED) connected to digital  
 pin 13, when pressing a pushbutton attached to pin 2. 
 
 
 The circuit:
 * LED attached from pin 13 to ground 
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground
 
 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.
 
 
 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/Button
 */

#define BUTTON_PIN 12
#define LED_PIN 13

int buttonState = 0;
int prevButtonState = 0;

void setup() {
  
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);  
  
  // initialize the LED pin as an output:
  pinMode(LED_PIN, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(BUTTON_PIN, INPUT);  
  
//  digitalWrite(LED_PIN, LOW);  

}

void loop(){
  
  if (isButtonPressed()){
    Serial.println("pressed");
  }

  
}

boolean isButtonPressed(){
  
  buttonState = digitalRead(BUTTON_PIN);
  
  if (buttonState != prevButtonState){
    
    prevButtonState = buttonState;
    
    if (buttonState == HIGH){
      return true;
    }
    
  }
  
  return false;
  
}
