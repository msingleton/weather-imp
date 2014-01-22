#include <Rainbowduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Stream.h>

void setup()
{
  Rb.init(); //initialize Rainbowduino driver
  Serial.begin(9600);
  Wire.begin(0x53);
  Wire.onReceive(recieveEvent);
}

void loop() {}

void recieveEvent(int howMany) {
  Serial.print("howMany: ");
  Serial.print(howMany);
  
  lightTest();
}

void lightTest() { 
  unsigned int z,x,y;
  unsigned int color = 0x0000FF;
  
  for(x=0;x<4;x++) {
    for(y=0;y<4;y++) {     
      Rb.setPixelZXY(3, x, y, color);
      Rb.setPixelZXY(2, x, y, color);
      Rb.setPixelZXY(1, x, y, color);
      Rb.setPixelZXY(0, x, y, color);
    }
  }
}

