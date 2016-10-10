/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include "aungwinhtut.h"
#define ONE 16738455
#define TWO 16750695
#define THREE 16756815
#define FOUR 16724175
#define FIVE 16718055


const int led1=8;
const int led2=9;
const int led3=10;
const int led4=11;
const int led5=12;

int RECV_PIN = 2;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(led5,OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Waiting IR signals !!!");
}

void loop() {
  if (irrecv.decode(&results)) {
    //Serial.println(results.value, HEX);
    Serial.println(results.value);
    irrecv.resume(); // Receive the next value

    switch(results.value)
    {
      case ONE: 
                funOne();break;
      case TWO: 
                digitalWrite(led1,LOW);break;
      case THREE: break;
      case FOUR: break;
      case FIVE: break;
      default: ;
     
    }
   
  }
  delay(100);
}


void funOne()
{
  digitalWrite(led1,HIGH);
}

