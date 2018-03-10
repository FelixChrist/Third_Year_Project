#include <Arduino.h>
#include "avdweb_SAMDtimer.h"
volatile int count=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  Serial.print("Initialising...\n");
  delay(50);
  pinMode(10, OUTPUT);
  
  SAMDtimer myTimer = SAMDtimer(4, PWMFunction, 1000);
  delay(1000);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(count);
  Serial.print("\n");
  if(count >50){
    digitalWrite(10,HIGH);
  }
  else{
    digitalWrite(10,LOW);
  }
  delay(100);
}

void PWMFunction(struct tc_module *const module_inst) {

  
  count = count + 1;
  if (count == 50)
  {
    //Serial.print("Here");
    //delay(50);
    count = 0;
  }
}

