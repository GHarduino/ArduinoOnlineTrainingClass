#include<SoftwareSerial.h>
SoftwareSerial mySerial(11, 12);       //TXD11  RXD12
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("I AM HC-05!");
  mySerial.begin(9600);
  mySerial.println("Hello, world? I AM HC-05");
}
void loop() {
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}

