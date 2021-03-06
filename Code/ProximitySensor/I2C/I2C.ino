/*
 * This code uses I2C to read a distance from a factory setting MTCH112 chip. 
 * 
 * MTCH112 default I2C address is 0xE6 this needs to be right shifted for the arduino library
*/
#include <Wire.h>
#define DEFAULT_ADDRESS 115
#define ADDRESS 2
void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600); 
  Serial.println("Initialising MTCH112...");
  WriteAddress();
  Serial.println("Address: ");
  ReadRegister(0x0B);
  WriteRegister(0x07,150);
  Serial.println("Prox threshold: ");
  ReadRegister(0x07);
  Serial.println("Timeout high: ");
  ReadRegister(0x0A);
  Serial.println("Timeout low: ");
  ReadRegister(0x09);

}

void loop() {
  int distance = 0;
  //Send I^2C frame to device
  Wire.beginTransmission(ADDRESS);
  //This indicates which register to read
  Wire.write(0x80);
  Wire.endTransmission();
  delay(50);
  //Read back the data sent by the MTCH112
  Wire.requestFrom(ADDRESS,2,1);
  if (2 <= Wire.available()) { // Wait till 2 bytes are ready.
    //Receive the two bytes and shift them accordingly
    distance = Wire.read(); 
    distance = distance << 8;
    distance |= Wire.read();
    //print the distance
    Serial.print(distance);
    //Serial.println("Here");
            // print the byte
  }
  Serial.print("\n");
  //Wait before reading a new value
  delay(100);
  

}

/*
 * This function allows you to write the value of a given register
 */
 
void WriteRegister(int reg, int value){
  //Open writing I2C to device with ADDRESS
  Wire.beginTransmission(ADDRESS);
  //0x55 and 0xAA Sent as write protection
  Wire.write(0x55);
  Wire.write(0xAA);
  //Queue the location of the register
  Wire.write(reg);
  //Queue the new value for the register
  Wire.write(value);
  //Queue a checksum (Xor of all bytes sent except address)
  Wire.write(0x55^0xAA^reg^value);
  //Send all queued bytes
  Wire.endTransmission();
  //Wait before reading or writing again
  delay(50);
}

/*
 * This function allows you to read the value fo a given register
 */

void ReadRegister(int reg){
  //Open writing I2C to device with ADDRESS  
  Wire.beginTransmission(ADDRESS);
  //Queue location of register to be read
  Wire.write(reg);
  //Send all queued bytes
  Wire.endTransmission();
  //Open reading I2C to device with ADDRESS
  Wire.requestFrom(ADDRESS,1);
  //Print the sent byte
  Serial.print(Wire.read());
  Serial.print("\n");
  //Wait before reading or writing again
  delay(50);
}
void WriteAddress(){
  //Open writing I2C to device with ADDRESS
  Wire.beginTransmission(DEFAULT_ADDRESS);
  //0x55 and 0xAA Sent as write protection
  Wire.write(0x55);
  Wire.write(0xAA);
  //Queue the location of the register
  Wire.write(0x0B);
  //Queue the new value for the register
  Wire.write(ADDRESS<<1);
  //Queue a checksum (Xor of all bytes sent except address)
  Wire.write(0x55^0xAA^0x0B^(ADDRESS<<1));
  //Send all queued bytes
  Wire.endTransmission();
  //Wait before reading or writing again
  delay(50);
}
