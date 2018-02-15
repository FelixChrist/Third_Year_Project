/*
 * This code uses I2C to read a distance from a factory setting MTCH112 chip. 
 * 
 * MTCH112 default I2C address is 0xE6 this needs to be right shifted for the arduino library
*/
#include <Wire.h>
void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600); 
  Serial.print("Initialising...\n");
  
}

void loop() {
  int distance = 0;
  //Send I^2C frame to device
  Wire.beginTransmission(115);
  //This indicates which register to read
  Wire.write(0x80);
  Wire.endTransmission();
  delay(100);
  //Read back the data sent by the MTCH112
  Wire.requestFrom(115,2,1);
  if (2 <= Wire.available()) { // Wait till 2 bytes are ready.
    //Receive the two bytes and shift them accordingly
    distance = Wire.read(); 
    distance = distance << 8;
    distance |= Wire.read();
    //print the distance
    Serial.print(distance);
            // print the byte
  }
  Serial.print("\n");
  //Wait before reading a new value
  delay(300);
  

}
