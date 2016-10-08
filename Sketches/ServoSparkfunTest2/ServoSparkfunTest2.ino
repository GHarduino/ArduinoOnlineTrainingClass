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

//create a servo object called servo1 
Servo servo1;  


void setup()
{
  //attach servo1 to pin 9 on the Arduino 101
  servo1.attach(9);
}


void loop()
{ 
  //create a local variable to store the servo's position.
  int position;

  // To control a servo, you give it the angle you'd like it
  // to turn to. Servos cannot turn a full 360 degrees, but you
  // can tell it to move anywhere between 0 and 180 degrees.

  // Change position at full speed:

  for (int i =0; i<180; i++)
  {
  // Tell servo to go to 90 degrees
  servo1.write(90);   

  // Pause to get it time to move
  delay(1000);    
  // Tell servo to go to 90 degrees
  servo1.write(180);   

  // Pause to get it time to move
  delay(1000); 
  // Tell servo to go to 90 degrees
  servo1.write(90);   

  // Pause to get it time to move
  delay(1000); 
  // Tell servo to go to 90 degrees
  servo1.write(0);   

  // Pause to get it time to move
  delay(1000);     
  }
  
}

