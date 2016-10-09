/*
   IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
   An IR detector/demodulator must be connected to the input RECV_PIN.
   Version 0.1 July, 2009
   Copyright 2009 Ken Shirriff
   http://arcfn.com
*/

#include "IRremote1.h"

//#define ONE FF9897
//#define TWO FFB06F
#define ONE 16738455
#define TWO 16750695
#define POWER 551489775
#define SOURCE 551538735

const int RECV_PIN = 2;
const int led1 = 11;
const int led2 = 12;
int led1status = 0;
int led2status = 0;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    Serial.println(results.value);
    irrecv.resume(); // Receive the next value
    switch (results.value)
    {
      case POWER:
      case ONE:
        if (led1status == 0)
        {
          digitalWrite(led1, HIGH);
          Serial.println("LED1 ON");
          led1status = 1;
        }
        else
        {
          digitalWrite(led1, LOW);
          Serial.println("LED1 OFF");
          led1status = 0;
        }
        break;
      case SOURCE:
      case TWO:    if (led2status == 0)
        {
          digitalWrite(led2, HIGH);
          Serial.println("LED2 ON");
          led2status = 1;
        }
        else
        {
          digitalWrite(led2, LOW);
          Serial.println("LED2 OFF");
          led2status = 0;
        } break;
      // case POWER: digitalWrite(led1, HIGH);
      //  Serial.println("LED1 ON"); break;
      // case SOURCE: digitalWrite(led1, LOW);
      //  Serial.println("LED1 OFF"); break;

      default: Serial.println("error code"); break;
    }
  }
  delay(100);
}
