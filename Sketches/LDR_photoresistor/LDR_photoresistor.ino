/*
SparkFun Inventor's Kit 
Example sketch 07

PHOTORESISTOR

  Read a photoresistor (light sensor) to detect "darkness" and turn on an LED when it is "dark" and turn back off again when it is "bright."

This sketch was written by SparkFun Electronics,
with lots of help from the Arduino community.
This code is completely free for any use.
Visit http://learn.sparkfun.com/products/2 for SIK information.
Visit http://www.arduino.cc to learn more about Arduino.
*/


// As usual, we'll create constants to name the pins we're using.
// This will make it easier to follow the code below.

const int sensorPin = 0;
const int ledPin = 13;

// We'll also set up some global variables for the light level a calibration value and     //and a raw light value
int lightCal;
int lightVal;


void setup()
{
  Serial.begin(9600);
  // We'll set up the LED pin to be an output.
  pinMode(ledPin, OUTPUT);
  lightCal = analogRead(sensorPin);
  //we will take a single reading from the light sensor and store it in the lightCal        //variable. This will give us a prelinary value to compare against in the loop
}


void loop()
{
  //Take a reading using analogRead() on sensor pin and store it in lightVal
  lightVal = analogRead(sensorPin);
  
  Serial.println(lightVal);
  delay(200);
  //if lightVal is less than our initial reading (lightCal) minus 50 it is dark and         //turn pin 9 HIGH. The (-50) part of the statement sets the sensitivity. The smaller       //the number the more sensitive the circuit will be to variances in light.
  if(lightVal < lightCal - 50)
  {
    digitalWrite(13,HIGH);
  }

  //else, it is bright, turn pin 9 LOW
  else
  {
    digitalWrite(13,LOW);
  }

}
