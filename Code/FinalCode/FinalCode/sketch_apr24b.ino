// Set timer TC4 to call the TC4_Handler every second
#include <Wire.h>
int x = 0;
byte send;
bool outer=0, inner=0, speak=0, el=0, prox=0, thermo=0;
void setup() {
  Serial.begin(9600);
   Wire.begin();
  Serial.println("Starting");
  // Set up the generic clock (GCLK4) used to clock timers
  REG_GCLK_GENDIV = GCLK_GENDIV_DIV(1) |          // Divide the 48MHz clock source by divisor 1: 48MHz/1=48MHz
                    GCLK_GENDIV_ID(4);            // Select Generic Clock (GCLK) 4
  while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization

  REG_GCLK_GENCTRL = GCLK_GENCTRL_IDC |           // Set the duty cycle to 50/50 HIGH/LOW
                     GCLK_GENCTRL_GENEN |         // Enable GCLK4
                     GCLK_GENCTRL_SRC_DFLL48M |   // Set the 48MHz clock source
                     GCLK_GENCTRL_ID(4);          // Select GCLK4
  while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization

  // Feed GCLK4 to TC4 and TC5
  REG_GCLK_CLKCTRL = GCLK_CLKCTRL_CLKEN |         // Enable GCLK4 to TC4 and TC5
                     GCLK_CLKCTRL_GEN_GCLK4 |     // Select GCLK4
                     GCLK_CLKCTRL_ID_TC4_TC5;     // Feed the GCLK4 to TC4 and TC5
  while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization
 
  REG_TC4_COUNT16_CC0 = 0x01D4;                   // Set the TC4 CC0 register as the TOP value in match frequency mode
  while (TC4->COUNT16.STATUS.bit.SYNCBUSY);       // Wait for synchronization

  //NVIC_DisableIRQ(TC4_IRQn);
  //NVIC_ClearPendingIRQ(TC4_IRQn);
  NVIC_SetPriority(TC4_IRQn, 0);    // Set the Nested Vector Interrupt Controller (NVIC) priority for TC4 to 0 (highest)
  NVIC_EnableIRQ(TC4_IRQn);         // Connect TC4 to Nested Vector Interrupt Controller (NVIC)

  REG_TC4_INTFLAG |= TC_INTFLAG_OVF;              // Clear the interrupt flags
  REG_TC4_INTENSET = TC_INTENSET_OVF;             // Enable TC4 interrupts
  // REG_TC4_INTENCLR = TC_INTENCLR_OVF;          // Disable TC4 interrupts
 
  REG_TC4_CTRLA |= TC_CTRLA_PRESCALER_DIV1024 |   // Set prescaler to 1024, 48MHz/1024 = 46.875kHz
                   TC_CTRLA_WAVEGEN_MFRQ |        // Put the timer TC4 into match frequency (MFRQ) mode 
                   TC_CTRLA_ENABLE;               // Enable TC4
  while (TC4->COUNT16.STATUS.bit.SYNCBUSY);       // Wait for synchronization
}

void loop() {
  //Serial.println(x);
  delay(500);
  }

void TC4_Handler()                              // Interrupt Service Routine (ISR) for timer TC4
{     
  // Check for overflow (OVF) interrupt
  if (TC4->COUNT16.INTFLAG.bit.OVF && TC4->COUNT16.INTENSET.bit.OVF)             
  {
    // Put your timer overflow (OVF) code here:     
    // ...
    //x=x+1;
    //Serial.println(x);
         if(GetValue(2)>1400){
        // if(1){
    inner = true;
  }
  //else if(GetValue(2)>1000){
  else if(1){
    outer=true;
  }
  else{
    inner=false;
    outer=false;
  }
  SetSend(outer, inner,speak, el, prox, thermo );
  Send();
   
    REG_TC4_INTFLAG = TC_INTFLAG_OVF;         // Clear the OVF interrupt flag
  }
}
int GetValue(int address){
  //return the value in register 0x80
  return ReadRegister(0x80,2,address);
}
int ReadRegister(int reg, int numOfBytes, int address){
  Serial.println("Here");
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
  if (numOfBytes <= Wire.available())
  for(int i = 0; i< numOfBytes; i++){
    
    //Shift the value one byte along
    value = value << 8;
    //Put the least significat bits in
    value |= Wire.read(); 
  }
  //return the value
  return value;
  
}
void Send(){
  Wire.beginTransmission(8);
  Serial.println(send);
  Wire.write(send);
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
  Serial.println(send);

}
