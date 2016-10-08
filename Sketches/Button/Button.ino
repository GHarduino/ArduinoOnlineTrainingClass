/*
SparkFun Inventor's Kit 
Example sketch 05

PUSH BUTTONS

  Use pushbuttons for digital input

This sketch was written by SparkFun Electronics,
with lots of help from the Arduino community.
This code is completely free for any use.
Visit http://learn.sparkfun.com/products/2 for SIK information.
Visit http://www.arduino.cc to learn about the Arduino.

*/


// First we'll set up constants for the pin numbers.
// This will make it easier to follow the code below.

 // pushbutton pin
 const int buttonPin = 2;

 //RGB LED pins
 const int redPin = 13;    
 


//create a variable to store a counter and set it to 0

void setup()
{
  // Set up the pushbutton pins to be an input:
  pinMode(buttonPin, INPUT);

  // Set up the RGB pins to be an outputs:
  pinMode(redPin, OUTPUT);  
  Serial.begin(9600);
}


void loop()
{
 // local variable to hold the pushbutton states
  int buttonState;  

  //read the digital state of buttonPin with digitalRead() function and store the           //value in buttonState variable
  buttonState = digitalRead(buttonPin);
 Serial.println(buttonState);
  //if the button is pressed increment counter and wait a tiny bit to give us some          //time to release the button
  if (buttonState == LOW) // light the LED
  {    
    delay(150);
    buttonState=HIGH;
    digitalWrite(redPin,HIGH);
  }
  else
  {
   buttonState=LOW; 
   digitalWrite(redPin,LOW);
  
  }

  
}

