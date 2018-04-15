#include <Wire.h>
void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  Wire.begin(8);
  Wire.onReceive(SetLights);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);

}

void SetLights(int howMany){
  int received;
  received = Wire.read();
  if(received%2){
    digitalWrite(2,HIGH);
  }
  else{
    digitalWrite(2,LOW);
  }
    if((received>>1)%2){
    digitalWrite(3,HIGH);
  }
  else{
    digitalWrite(3,LOW);
  }
    if((received>>2)%2){
    digitalWrite(4,HIGH);
  }
  else{
    digitalWrite(4,LOW);
  }
    if((received>>3)%2){
    digitalWrite(5,HIGH);
  }
  else{
    digitalWrite(5,LOW);
  }
    if((received>>4)%2){
    digitalWrite(6,HIGH);
  }
  else{
    digitalWrite(6,LOW);
  }
    if((received>>5)%2){
    digitalWrite(7,HIGH);
  }
  else{
    digitalWrite(7,LOW);
  }
  
}

