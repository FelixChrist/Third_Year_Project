/*
This code allows an LED to turn on or off using an interrupt.

The interrupt should be connected to pin 10 and the LED connected to pin 13.
 */

byte ledPin = 13;
byte interruptPin = 10;
//Set the state of the output, this is volatile so it can change in interrupts
volatile byte state = LOW;
void setup() {
  //Set the pin modes
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  //Attach the interrupt to the interrupt pin
  attachInterrupt(digitalPinToInterrupt(interruptPin), Change, RISING);
}

void loop() {
  //Constantly write the state of the pin 
  digitalWrite(ledPin, state);
}
void Change(){
  //If any change occurs in the proximity sensor change the state of the LED
  state=!state;
}

