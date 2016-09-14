/*
 * connecting potenciometer:
 * left pin: GND
 * center pin: A0
 * right pin: VCC
 */

int analogPin0 = 0; 

void setup() {
  Serial.begin(9600);

}

void loop() {

  Serial.println(analogRead(analogPin0));

}
