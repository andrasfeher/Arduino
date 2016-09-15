#include <dht.h>

dht DHT;

#define DHT22_PIN 7


typedef struct {
  char instruction; // The instruction that arrived by serial connection.
  float argument;   // The argument that came with the instruction.
} Command;

/**
 * ReadCommand sucks down the lastest command from the serial port,
 * returns {'*', 0.0} if no new command is available.
 */
Command ReadCommand() {
  // Not enough bytes for a command, return an empty command.
  if (Serial.available() < 5) {
    return (Command) {'*', 0.0};
  }

  union {
    char b[4];
    float f;
  } ufloat;

  // Read the command identifier and argument from the serial port.
  char c = Serial.read();
  Serial.readBytes(ufloat.b, 4);

  return (Command) {c, ufloat.f};
}


void setup(){
  Serial.begin(9600);
}

void loop()
{

  Command c = ReadCommand();

  if (c.instruction == 'h') {
    int chk = DHT.read(DHT22_PIN);
    
    Serial.print(
      String("<data><Temp>" + String(DHT.temperature) + "</Temp>" + "<Hum>" + String(DHT.humidity) + "</Hum>" +  "</data>" )
     );
  }
  
  
  /*
  Serial.print(',');
  Serial.print(DHT.humidity);
  delay(1000);
  */
  
}

