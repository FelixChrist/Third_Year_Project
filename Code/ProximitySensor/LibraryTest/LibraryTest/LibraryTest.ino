#include <MTCH112.h>
#include <Wire.h>

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("Beginning");
  Wire.begin();
  MTCH112 proxSensor(115);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(proxSensor.GetValue());

}
