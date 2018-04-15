#include <Wire.h>
byte send = 0;
void setup() {
  // put your setup code here, to run once:
  Wire.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  SetSend(1,0,0,0,0,0);
  Send();
  delay(300);
  SetSend(1,0,1,1,0,0);
  Send();
  delay(300);
  SetSend(0,1,1,0,1,1);
  Send();
  delay(300);
  SetSend(1,1,1,1,1,1);
  Send();
  delay(300);
  SetSend(0,0,0,0,0,0);
  Send();
  delay(300);

}

void SetSend(bool one, bool two, bool three, bool four, bool five, bool six){
  if(one){
    send |= 1;
  }
  else{
    send |= ~1;
  }
  if(two){
    send |= 1<<1;
  }
  else{
    send |= ~(1<<1);
  }
  if(three){
    send |= 1<<2;
  }
  else{
    send |= ~(1<<2);
  }
    if(four){
    send |= 1<<3;
  }
  else{
    send |= ~(1<<3);
  }
    if(five){
    send |= 1<<4;
  }
  else{
    send |= ~(1<<4);
  }
    if(six){
    send |= 1<<5;
  }
  else{
    send |= ~(1<<5);
  }
}
void Send(){
  Wire.beginTransmission(8);
  Wire.write(send);
  Wire.endTransmission();
}

