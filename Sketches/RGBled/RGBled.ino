/*
SparkFun Inventor's Kit 
Example sketch 03

RGB LED

Make an RGB LED display a rainbow of colors!


This sketch was written by SparkFun Electronics,
with lots of help from the Arduino community.
Visit http://learn.sparkfun.com/products/2 for SIK information.
Visit http://www.arduino.cc to learn about the Arduino.
*/

//create variables for pin numbers. We are making them constants here, because they       //never change. 
const int RED_PIN = 5;
const int GREEN_PIN = 6;
const int BLUE_PIN = 9;

// How fast we plan to cycle through colors in milliseconds
int DISPLAY_TIME = 10;  


void setup()
{
//set the three pin variables as outputs
pinMode(RED_PIN, OUTPUT);
pinMode(GREEN_PIN, OUTPUT);
pinMode(BLUE_PIN, OUTPUT);
}


void loop()
{
// We've written a custom function called mainColors() that steps
// through all eight of these colors. We're only "calling" the
// function here (telling it to run). The actual function code
// is further down in the sketch.
mainColors();


}


// Here's the mainColors() custom function we've written.
void mainColors()
{
// Off (all LEDs off):
digitalWrite(RED_PIN, LOW);
digitalWrite(GREEN_PIN, LOW);
digitalWrite(BLUE_PIN, LOW);

//wait 1 second
delay(1000);

// Red (turn just the red LED on):
digitalWrite(RED_PIN, HIGH);
digitalWrite(GREEN_PIN, LOW);
digitalWrite(BLUE_PIN, LOW);

//wait 1 seconds
delay(1000);

// Green (turn just the green LED on):
digitalWrite(RED_PIN, LOW);
digitalWrite(GREEN_PIN, HIGH);
digitalWrite(BLUE_PIN, LOW);

//wait 1 second
delay(1000);

// Blue (turn just the blue LED on):
digitalWrite(RED_PIN, LOW);
digitalWrite(GREEN_PIN, LOW);
digitalWrite(BLUE_PIN, HIGH);

//wait 1 second
delay(1000);

// Yellow (turn red and green on):
digitalWrite(RED_PIN, HIGH);
digitalWrite(GREEN_PIN, HIGH);
digitalWrite(BLUE_PIN, LOW);

//wait 1 second
delay(1000);

// Cyan (turn green and blue on):
digitalWrite(RED_PIN, LOW);
digitalWrite(GREEN_PIN, HIGH);
digitalWrite(BLUE_PIN, HIGH);

//wait 1 second
delay(1000);

// Purple (turn red and blue on):
digitalWrite(RED_PIN, HIGH);
digitalWrite(GREEN_PIN, LOW);
digitalWrite(BLUE_PIN, HIGH);

//wait 1 second
delay(1000);

// White (turn all the LEDs on):
digitalWrite(RED_PIN, HIGH);
digitalWrite(GREEN_PIN, HIGH);
digitalWrite(BLUE_PIN, HIGH);

//wait 1 second
delay(1000);
}

