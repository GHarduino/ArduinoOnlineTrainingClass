/* SparkFun Inventor's Kit 
Example sketch 02

POTENTIOMETER

  Measure the position of a potentiometer and use it to
  control the blink rate of an LED. Turn the knob to make
  it blink faster or slower!

This sketch was written by SparkFun Electronics,
with lots of help from the Arduino community.
This code is completely free for any use.
Visit http://learn.sparkfun.com/products/2 for SIK information.
Visit http://www.arduino.cc to learn about Arduino.
*/



//Create global variables (variables that can be used anywhere in our sketch)

// Here we're creating a variable called "sensorPin" of type "int"
// and initializing it to have the value "0," which is the analog input pin the pot is     //conected to.
int sensorPin = 0;    

// Variable for storing the pin number that the LED is connected to                 
int ledPin = 13;      

// this function runs once when the sketch starts up
void setup() 
{
  //set ledPin (13) as an OUTPUT
  pinMode(ledPin, OUTPUT);
}

// this function runs repeatedly after setup() finishes
void loop() 
{

  //create a local variable (variable that can only be used inside of loop() to store       //a sensor value called sensorValue
  int sensorValue;

  //use the analogRead() function to read sensorPin and store the value in sensorValue
  sensorValue = analogRead(sensorPin);    

  // Turn the LED on
  digitalWrite(ledPin, HIGH);     


  delay(sensorValue);             

  // Turn the LED off
  digitalWrite(ledPin, LOW);      

 //delay for the value of sensorValue
  delay(sensorValue);             

  //loop back to the top
}

