const int sensorPin1 = 0;
const int sensorPin2 = 1;
const int ledPin1 = 2;
const int ledPin2 = 4;
const int fanPin1 = 3;
// We'll also set up some global variables for the light level a calibration value and     //and a raw light value
int lightCal1;
int lightVal1;
int lightCal2;
int lightVal2;
/////////////////
float temp;
float tempC;
int tempPin = 2; // analog input pin
///////////////
void setup()
{
  
  // We'll set up the LED pin to be an output.
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  Serial.begin(9600);
  lightCal1 = analogRead(sensorPin1);
  lightCal2 = analogRead(sensorPin2);
  //we will take a single reading from the light sensor and store it in the lightCal        //variable. This will give us a prelinary value to compare against in the loop
}


void loop()
{

  //////////
  //temperature//
  temp = analogRead(tempPin);
  Serial.print("RAW DATA: ");
  Serial.print (temp);
  Serial.println(" ");
  //converts raw data into degrees celsius and prints
  //it out
  // 500mV/1024=.48828125
  temp = temp * 0.48828125;
  tempC = temp;
  Serial.print("CELSIUS: ");
  Serial.print(temp);
  Serial.println("*C ");
  //converts celsius into fahrenheit 
  temp = temp *9 / 5;
  temp = temp + 32;
  
  Serial.print("FAHRENHEIT: ");
  Serial.print(temp);
  Serial.println("*F");
  delay(1000);
  if(tempC>40)
  {
    digitalWrite(fanPin1,HIGH);
    Serial.println("");
    Serial.println("fan on");
  }
  else
  {
    digitalWrite(fanPin1,LOW);
     Serial.println("");
    Serial.println("fan off");
  }
  
  //////////////////
  
  //Take a reading using analogRead() on sensor pin and store it in lightVal
  lightVal1 = analogRead(sensorPin1);
  //delay(300);
  lightVal2 = analogRead(sensorPin2);

  //if lightVal is less than our initial reading (lightCal) minus 50 it is dark and         //turn pin 9 HIGH. The (-50) part of the statement sets the sensitivity. The smaller       //the number the more sensitive the circuit will be to variances in light.
  if(lightVal1 < lightCal1 - 50)
  {
    digitalWrite(ledPin1,HIGH);
  }

  //else, it is bright, turn pin 9 LOW
  else
  {
    digitalWrite(ledPin1,LOW);
  }

   if(lightVal2 < lightCal2 - 50)
  {
    digitalWrite(ledPin2,HIGH);
  }

  //else, it is bright, turn pin 9 LOW
  else
  {
    digitalWrite(ledPin2,LOW);
  }

}
