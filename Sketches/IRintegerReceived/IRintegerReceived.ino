/*
   IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
   An IR detector/demodulator must be connected to the input RECV_PIN.
   Version 0.1 July, 2009
   Copyright 2009 Ken Shirriff
   http://arcfn.com
*/

#include <IRremote.h>
#define one     3772784863
#define two     3772817503
#define three   3772801183
#define four    3772780783 //4120482440
#define five    3772813423
#define six     3772797103
#define seven   3772788943
#define eight   3772821583
#define nine    3772805263
#define zero    3772811383


int RECV_PIN = 2;
int led = 3;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
   
   
    
    switch (results.value)
    {
      case one      : funOne(); break;
      case two      : funTwo(); break;
      case three    : funThree(); break;
      case four     : funFour(); break;
      case five     : funFive(); break;
      case six      : funSix(); break;
      case seven    : funSeven(); break;
      case eight    : funEight(); break;
      case nine     : funNine(); break;
      case zero     : funZero(); break;
      default:  Serial.println(results.value);
    }
     irrecv.resume(); // Receive the next value
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
  }
  delay(100);
}



void funOne()
{
  Serial.println("funOne");
}
void funTwo()
{
  Serial.println("funTwo");
}
void funThree()
{
  Serial.println("funThree");
}
void funFour()
{
  Serial.println("funFour");
}
void funFive()
{
  Serial.println("funFive");
}
void funSix()
{
  Serial.println("funSix");
}
void funSeven()
{
  Serial.println("funSeven");
}
void funEight()
{
  Serial.println("funEight");
}
void funNine()
{
  Serial.println("funNine");
}
void funZero()
{
  Serial.println("funZero");
}
