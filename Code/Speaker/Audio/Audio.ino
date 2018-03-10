#include <SD.h>
#include <ArduinoSound.h>

//Initialise the wave file
SDWaveFile audio;
void setup() {
  // Set up serial
  Serial.begin(9600);
  Serial.println("Initializing SD card...");
  //Initialise the SD Card
  if (!SD.begin()) {
    //If the SD card cannot initialise (incorrect wiring, incorrectly formatted, etc.), stop the program 
    Serial.println("initialization failed!");
    while(1);
  }
  Serial.println("initialization done.");
  //Load the audio file
  audio = SDWaveFile("siren.wav");
  if(!AudioOutI2S.canPlay(audio)){
    //If the audio cannot be played (wrong file type etc.), stop the program
    Serial.println("Unable to play file");
    while(1);
    
  }
  Serial.println("Playing audio...");
  //Play the audio
  AudioOutI2S.play(audio);
}

void loop() {
  // If the audio has finished, stop the program
  if(!AudioOutI2S.isPlaying()){
    Serial.println("Finished!");
    while(1);
  }
}
