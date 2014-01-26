#include <Rainbowduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Stream.h>

boolean hasWeather = false;
unsigned int intensity;
String precipitationType;

void setup()
{
  Rb.init();
  Serial.begin(9600);
  Wire.begin(0x53);
  Wire.onReceive(recieveEvent);  
}

void loop() {
  if(hasWeather) {
    delay(5000);
    turnOff();
  }
}

void turnOff() {
  hasWeather = false;
  Rb.blankDisplay();
}

void recieveEvent(int howMany) {
  String weather = "";
  
  Wire.available(); // Ignore the first one
  while(Wire.available()) {
    char c = Wire.read();
    weather = weather + c;
  }
  
  unsigned int index = weather.indexOf('&');
  precipitationType = weather.substring(0, index);
  intensity = weather.substring(index + 1).toInt();
  hasWeather = true;
  
  if (precipitationType == "rain") {
    showRain(intensity);
  } else if (precipitationType == "snow") {
    showSnow(intensity);
  }

}

void showRain(unsigned int intensity) { 
  unsigned int z,x,y;
  unsigned char RAINRED[64] = {0,0,0};
  unsigned char RAINGREEN[64] = {0,75,150};
  unsigned char RAINBLUE[64] = {255,255,255};
  

    for(z=0;z<intensity;z++) { 
      for(x=0;x<4;x++) {
        for(y=0;y<4;y++) {     
          Rb.setPixelZXY(z,x,y, RAINRED[random(3)], RAINGREEN[random(3)], RAINBLUE[random(3)]);
        }
      }
    }

}

void showSnow(unsigned int intensity) { 
  unsigned int z,x,y;
  unsigned char SNOWRED[64] = {255,255,150};
  unsigned char SNOWGREEN[64] = {255,255,150};
  unsigned char SNOWBLUE[64] = {255,255,255};
  
    for(z=0;z<intensity;z++) { 
      for(x=0;x<4;x++) {
        for(y=0;y<4;y++) {     
          Rb.setPixelZXY(z,x,y, SNOWRED[random(3)], SNOWGREEN[random(3)], SNOWBLUE[random(3)]);
        }
      }
    }
}

