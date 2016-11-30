#include<SoftwareSerial.h>
SoftwareSerial mySerial(11, 12);       //TXD11  RXD12
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.println("Goodnight moon!");
  mySerial.begin(38400);
  mySerial.println("Hello, world?");
}
void loop() {
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}

