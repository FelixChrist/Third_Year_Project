#include <SD.h>
#include <ArduinoSound.h>
#include <Wire.h>
#include "avdweb_SAMDtimer.h"
SDWaveFile audio;
byte send;
bool outer=0, inner=0, speak=0, el=0, prox=0, thermo=0;
void setup() {
  // Set up serial
  pinMode(10, OUTPUT);
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Initializing SD card...");
  //Initialise the SD Card
  if (!SD.begin()) {
    //If the SD card cannot initialise (incorrect wiring, incorrectly formatted, etc.), stop the program 
    Serial.println("initialization failed!");
    while(1);
  }
  Serial.println("initialization done.");
  SAMDtimer myTimer = SAMDtimer(4, ELChange, 100);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(GetValue(1)>1500){
    Presentation();
  }

}

void Presentation(){
  audio = SDWaveFile("intro.wav");
  Serial.println("Playing audio...");
  //Play the audio
  AudioOutI2S.play(audio);
  while(AudioOutI2S.isPlaying());
  speak=1;
  delay(100);
  audio = SDWaveFile("speaker.wav");
  while(AudioOutI2S.isPlaying());
  speak=0;
  el=1;
  delay(100);
  audio = SDWaveFile("elLamp.wav");
  while(AudioOutI2S.isPlaying());
  el=0;
  prox=1;
  delay(100);
  audio = SDWaveFile("proxSensor.wav");
  while(AudioOutI2S.isPlaying());
  prox = 0;
  thermo=1;
  audio = SDWaveFile("thermochromic.wav");
  while(AudioOutI2S.isPlaying());
  thermo = 0;
  delay(100);
  digitalWrite(10,HIGH);
}

int ReadRegister(int reg, int numOfBytes, int address){

  int value = 0;
  //Wait before reading
  delay(50);
  //Open writing I2C to the device  
  Wire.beginTransmission(address);
  //Queue location of register to be read
  Wire.write(reg);
  //Send all queued bytes
  Wire.endTransmission();
  //Open reading I2C to the device
  Wire.requestFrom(address,numOfBytes);
  //Wait until all bytes are available
  while(numOfBytes > Wire.available()); 
  for(int i = 0; i< numOfBytes; i++){
    //Shift the value one byte along
    value = value << 8;
    //Put the least significat bits in
    value |= Wire.read(); 
  }
  //return the value
  return value;
  
}
void WriteRegister(int reg, int value, int address){
  //Wait before writing
  delay(50);
  //Open writing I2C to device with ADDRESS
  Wire.beginTransmission(address);
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

}
void SetSend(bool one, bool two, bool three, bool four, bool five, bool six){
  send = 0;
  if(one){
    send += 1;
  }

  if(two){
    send += 1<<1;
  }

  if(three){
    send += 1<<2;
  }

    if(four){
    send += 1<<3;
  }

    if(five){
    send += 1<<4;
  }

    if(six){
    send += 1<<5;
  }


}
void Send(){
  Wire.beginTransmission(8);
    Serial.println(send);
  Wire.write(send);
  Wire.endTransmission();
}
int GetValue(int address){
  //return the value in register 0x80
  return ReadRegister(0x80,2,address);
}
void ELChange(struct tc_module *const module_inst){
  if(GetValue(2)>1600){
    inner = true;
  }
  else if(GetValue(2)>1400){
    outer=true;
  }
  else{
    inner=false;
    outer=false;
  }
  SetSend(speak, el, prox, thermo, outer, inner);
  Send();
}

