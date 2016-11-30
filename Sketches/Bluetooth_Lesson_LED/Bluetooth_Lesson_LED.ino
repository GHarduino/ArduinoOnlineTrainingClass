#include<SoftwareSerial.h>
SoftwareSerial mySerial(11, 12);       //TXD11  RXD12
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  pinMode(9,OUTPUT);
  Serial.println("Goodnight moon!");
  mySerial.begin(38400);
  mySerial.println("Hello, world?");
}
void loop() {
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available() > 0)
  {
    int incomingByte = Serial.read();
    switch (incomingByte)
    {
      case'0'://48
        digitalWrite(9,HIGH);
        Serial.println("LED ON");
        break;
      case'1'://49
       digitalWrite(9,LOW);
        Serial.println("LED OFF");
        break;     
    }
  }
}

