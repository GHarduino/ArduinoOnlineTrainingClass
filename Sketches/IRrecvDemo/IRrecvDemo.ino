/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h> //1



IRrecv irrecv(2); //2

decode_results results; //3

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver //4
}

void loop() {
  if (irrecv.decode(&results)) {                         //5
    Serial.println(results.value);                  //6
    irrecv.resume(); // Receive the next value           //7
  }
  delay(100);
}
