#include <Wire.h>
byte send = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  SetSend(1,0,0,0,0,0);
  Send();
  Serial.println("ONE");
  delay(2000);
  SetSend(1,0,1,1,0,0);
  Send();
  Serial.println("TWO");
  delay(2000);
  SetSend(0,1,1,0,1,1);
  Send();
  Serial.println("THREE");
  delay(2000);
  SetSend(1,1,1,1,1,1);
  Send();
  Serial.println("FOUR");
  delay(2000);
  SetSend(0,0,0,0,0,0);
  Send();
  Serial.println("FIVE");
  delay(2000);

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

