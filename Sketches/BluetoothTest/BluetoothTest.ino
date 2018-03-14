#include<SoftwareSerial.h>
SoftwareSerial BT(11,10);
#define led 8

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  pinMode(led,OUTPUT);

}

void loop() {
  char ch;
  if(BT.available())
  {
    ch=BT.read();
    Serial.println(ch);
    if(ch=='1')
    {
      digitalWrite(led,HIGH);
    }
    if(ch=='2')
    {
      digitalWrite(led,LOW);
    }
  }
}
