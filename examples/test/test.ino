#include <TimerOne.h>
#include <EncoderCtl.h>

// Note: to word reliably, we need a timer interrupt
// source, so include the TimerOne library.
EncoderCtl encoder(3);

void setup(){
// Initialise a timer interrupt every 5ms
  Timer1.initialize(5000L);
// Attach our own funtion to it
// Can't attach the EncoderCtl library funcion directly
// as it's not a true C function.
  Timer1.attachInterrupt(isr);
  Serial.begin(9600);
  while(!Serial);
// Set the encoder to return values between 10 and 30
// (inclusive), and set a starting value of 20.
  encoder.set(20, 10, 30);
}

void loop() {
  int encoderS;

// Get and display the current encoder value.  
  encoderS = encoder.get();
  Serial.println(encoderS);

  delay(500);
}

// Function that is attached to the timer interrupt.
// From this, we call the <instance>.update() function
// for each instance, i.e. for each encoder we use.
void isr() {
  encoder.update();
}

