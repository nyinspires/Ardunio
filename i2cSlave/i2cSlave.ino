#include <Wire.h>

#define  SLAVE_ADDRESS   0x3c  //slave address,any number from 0x01 to 0x7F
#define  REG_MAP_SIZE    14
#define  MAX_SENT_BYTES  3

/********* Global  Variables  ***********/

byte registerMap[REG_MAP_SIZE - 1];

byte receivedCommands[MAX_SENT_BYTES];


void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("\nI2C Scanner");
  Wire.pins(3, 4); // SDA, SCL
  Wire.begin(SLAVE_ADDRESS);                // join i2c bus with address #8
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}

void loop() {
  delay(100);
}

void requestEvent() {
  Serial.println("Request Event Called");
  Wire.write(registerMap, REG_MAP_SIZE);  //Set the buffer up to send all 14 bytes of data
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int bytesReceived) {
  for (int a = 0; a < bytesReceived; a++)
  {
    if ( a < MAX_SENT_BYTES)
    {
      receivedCommands[a] = Wire.read();
    }
    else
    {
      Wire.read();  // if we receive more data then allowed just throw it away
    }
  }
  if (bytesReceived == 1 && (receivedCommands[0] < REG_MAP_SIZE))
  {
    return;
  }
  if (bytesReceived == 1 && (receivedCommands[0] >= REG_MAP_SIZE))
  {
    receivedCommands[0] = 0x00;
    return;

  }
  switch (receivedCommands[0]) {
    case 0x0B:
      Serial.println("In Loop");
      break;
    default:
      return; // ignore the commands and return
  }


//  Serial.println("Receive Event Called");
//  while (1 < Wire.available()) { // loop through all but the last
//    char c = Wire.read(); // receive byte as a character
//    Serial.print(c);         // print the character
//  }
//  int x = Wire.read();    // receive byte as an integer
//  Serial.println(x);         // print the integer
}
