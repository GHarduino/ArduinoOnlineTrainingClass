/*
  RC PulseIn Joystick
  By: Nick Poole
  SparkFun Electronics
  Date: 5
  License: CC-BY SA 3.0 - Creative commons share-alike 3.0
  use this code however you'd like, just keep this license and
  attribute. Let me know if you make hugely, awesome, great changes.
*/
#include<Servo.h>
int ch1=0; // Here's where we'll keep our channel values
int ch2=0;
int ch3=0;
int ch4=0;
int ch5=0;
int ch6=0;
int i1=0;
Servo servo;

void setup() {

  pinMode(2, INPUT); // Set our input pins as such
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT); // Set our input pins as such
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600); // Pour a bowl of Serial
 
}

void loop() {

  ch1 = pulseIn(2, HIGH, 25000); // Read the pulse width of
  //ch2 = pulseIn(3, HIGH, 25000); // each channel
  //ch3 = pulseIn(4, HIGH, 25000);
  //ch4 = pulseIn(5, HIGH, 25000);
  //ch5 = pulseIn(6, HIGH, 25000);
  //ch6 = pulseIn(7, HIGH, 25000);

  i1=map(ch1,1000,2000,1,180);

  
  //delay(2000);

if(ch1>1500)
{
  servo.attach(13);
  delay(3000);
  servo.write(180);
  Serial.println(ch1);
  servo.detach(); 
  
}
else if(ch1>1000&&ch1<2000)
{
  servo.attach(13);
  delay(3000);
  servo.write(0);
  Serial.println(ch1);
  servo.detach(); 
  
}
  
  delay(100);// I put this here just to make the terminal
  // window happier
}

