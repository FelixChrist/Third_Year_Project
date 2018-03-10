#include <SD.h>
#include <ArduinoSound.h>

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing SD card...");
  if (!SD.begin()) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  File textFile = SD.open("text.txt");
  if (textFile) {
    while (textFile.available()) {
      Serial.write(textFile.read());
    }
    textFile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening text");
  }
}



void loop() {
  // put your main code here, to run repeatedly:

}
