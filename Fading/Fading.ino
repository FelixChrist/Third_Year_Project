/*
  Fading

  This code allows for an EL lamp to fade using SuperTex HV852 driver chip.


  It is adapted from example code created by Tom Igoe.

*/

int ledPin = 13;    // LED connected to digital pin 13
int frequency_Hz = 100;
int wavelength_ms = 1000/frequency_Hz;
void setup() {
  //Nothing happens in setup
}

void loop() {

  //Fade in from min to max
  for (int fadeValue = 0 ; fadeValue <= wavelength_ms; fadeValue += 1) {
    //Stay in each PWM cycle for a set number of wavelengths
    for(int i=0; i<50; i++){
      //set the pin high
      digitalWrite(ledPin, HIGH);
      //wait for the fade value
      delay(fadeValue);
      //set the pin low
      digitalWrite(ledPin, LOW);
      //wait for the difference between the wavelength and the fade value
      delay(wavelength_ms-fadeValue);
    }
  }

  //Fade out from max to min
  for (int fadeValue = wavelength_ms ; fadeValue >= 0; fadeValue -= 1) {
    // stay in each PWM cycle for a set number of wavelengths
    for(int i=0; i<50; i++){
      //set the pin high
      digitalWrite(ledPin, HIGH);
      //wait for the fade value
      delay(fadeValue);
      //set the pin low
      digitalWrite(ledPin, LOW);
      //wait for the difference between the wavelength and the fade value
      delay(wavelength_ms-fadeValue);
    }
  }
}
