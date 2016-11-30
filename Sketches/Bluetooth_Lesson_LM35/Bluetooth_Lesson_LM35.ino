#include<SoftwareSerial.h>
SoftwareSerial mySerial(11, 12);       //TXD11  RXD12
float temp;
int tempPin = 0; // analog input pin
int sampleTime = 1000; // 1 second dafault
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("Goodnight moon!");
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
}
void loop() {
  funMeasureTemp();
}

void funMeasureTemp()
{
  //gets and prints the raw data from the lm35
  temp = analogRead(tempPin);
  Serial.print("RAW DATA: ");
  Serial.print (temp);
  Serial.println(" ");
 
  
 
  //converts raw data into degrees celsius and prints
  //it out
  // 500mV/1024=.48828125
  temp = temp * 0.48828125;
  Serial.print("CELSIUS: ");
  Serial.print(temp);
  mySerial.print(temp);
  Serial.println("*C ");
  //converts celsius into fahrenheit
  temp = temp * 9 / 5;
  temp = temp + 32;
  Serial.print("FAHRENHEIT: ");
  Serial.print(temp);
  Serial.println("*F");
  Serial.println("");
  delay(sampleTime);
}

