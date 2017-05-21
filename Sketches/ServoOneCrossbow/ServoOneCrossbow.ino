/*
  SparkFun Inventor's Kit
  Example sketch 10

  SINGLE SERVO

  Sweep a servo back and forth through its full range of motion.

  This sketch was written by SparkFun Electronics,
  with lots of help from the Arduino community.
  This code is completely free for any use.
  Visit http://learn.sparkfun.com/products/2 for SIK information.
  Visit http://www.arduino.cc to learn more about Arduino.
*/

//include the servo library
#include <Servo.h>
#include<SoftwareSerial.h>  //for bluetooth
//create a servo object called servo1
Servo servo1;
SoftwareSerial BlueTooth(10, 11);

void setup()
{
  //attach servo1 to pin 9 on the Arduino 101

  BlueTooth.begin(9600);
}


void loop()
{
  char c;
  if (BlueTooth.available()) {
    c = BlueTooth.read();
    switch (c)
    {
      case 'f': funFire(); break;
      case 'r': funReload(); break;

    }
  }
}

void funFire()
{
  servo1.attach(9);
  servo1.write(0);
  delay(500);
  servo1.write(30);
  delay(500);
  servo1.detach();
}

void funReload()
{
  
}

