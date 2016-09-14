int analogPin0 = 0;     // potentiometer wiper (middle terminal) connected to analog pin 3
int analogPin1 = 1;
                       // outside leads to ground and +5V

int val0 = 0;           // variable to store the value read
int val1 = 0;           // variable to store the value read



void setup()
{

  Serial.begin(9600);          //  setup serial

}


void loop()
{

  val0 = analogRead(analogPin0);    // read the input pin
  val1 = analogRead(analogPin1);    // read the input pin

  Serial.println(val0);             // debug value
  Serial.println(val1);             // debug value
}
