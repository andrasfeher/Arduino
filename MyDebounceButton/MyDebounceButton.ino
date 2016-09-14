#define BUTTON_PIN 12
int buttonState = LOW;
int pressedCount = 0;


void setup() {
  
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
    
  pinMode(BUTTON_PIN, INPUT);

}

void loop() {


  if (digitalRead(BUTTON_PIN) == HIGH && buttonState == LOW){
    
    buttonState = HIGH;
    pressedCount++;
    Serial.println(pressedCount);
    
  } else if (digitalRead(BUTTON_PIN) == LOW && buttonState == HIGH){
    
    buttonState = LOW;
    // Serial.println("released");
   
  }

  


/*
  if (debounceButton(buttonState) == HIGH && buttonState == LOW){
    
    buttonState = HIGH;
    pressedCount++;
    Serial.println(pressedCount);
    
  } else if (debounceButton(buttonState) == LOW && buttonState == HIGH){
    
    buttonState = LOW;
    // Serial.println("released");
   
  }
 */

}


bool debounceButton(bool state){
  
  bool stateNow = digitalRead(BUTTON_PIN);
  
  if (state != stateNow){

    delay(10);
    stateNow = digitalRead(BUTTON_PIN);
    
  }

  return stateNow;
}

