//http://www.instructables.com/id/Arduino-Android-Bluetooth-Car/
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX
char myChar = 'a';
String string;

int led13 = 13;
int led12 = 12;
int led11 = 11;
int led10 = 10;
int led9 = 9;
int led8 = 8;
int led7 = 7;
int led6 = 6;
int led5 = 5;
int led4 = 4;
int led3 = 3;

void setup()
{
  //pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(led5,OUTPUT);
  pinMode(led6,OUTPUT);
  pinMode(led7,OUTPUT);
  pinMode(led8,OUTPUT);
  pinMode(led9,OUTPUT);
  pinMode(led10,OUTPUT);
  pinMode(led11,OUTPUT);
  pinMode(led12,OUTPUT);
  pinMode(led13,OUTPUT);
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  mySerial.begin(9600);
  Serial.println("Starting");
  
}
void loop() // run over and over
{
  Serial.println("Looping");
  string = "";
  while (true) {
    myChar = mySerial.read();
    //Serial.println(myChar);
    if (32 <= myChar & myChar <= 127) {
      string += myChar;
    }
    if (myChar == ':') {
      break;
    }
    delay(10);
  }

  Serial.println(string);
  if (string == "on11:") {
    digitalWrite(led11, HIGH);
    Serial.print("on11");
    //delay(2000);
  }
  if (string == "off11:") {
    digitalWrite(led11, LOW);
    Serial.print("off11");
    //delay(2000);
  }

  if (string == "on12:") {
    digitalWrite(led12, HIGH);
    Serial.print("on12");
    //delay(2000);
  }
  if (string == "off12:") {
    digitalWrite(led12, LOW);
    Serial.print("off12");
    //delay(2000);
  }
   if (string == "on13:") {
    digitalWrite(led13, HIGH);
  }
  if (string == "off13:") {
    digitalWrite(led13, LOW);
  }
  
  if (string == "on3:") {
    digitalWrite(led3, HIGH);

  }
  if (string == "off3:") {
    digitalWrite(led3, LOW);
  }

  if (string == "on4:") {
    digitalWrite(led4, HIGH);
  }
  if (string == "off4:") {
    digitalWrite(led4, LOW);
  }
  if (string == "on5:") {
    digitalWrite(led5, HIGH);

  }
  if (string == "off5:") {
    digitalWrite(led5, LOW);
  }

  if (string == "on6:") {
    digitalWrite(led6, HIGH);
  }
  if (string == "off6:") {
    digitalWrite(led6, LOW);
  }
  if (string == "on7:") {
    digitalWrite(led7, HIGH);

  }
  if (string == "off7:") {
    digitalWrite(led7, LOW);
  }

  if (string == "on8:") {
    digitalWrite(led8, HIGH);
  }
  if (string == "off8:") {
    digitalWrite(led8, LOW);
  }
  if (string == "on9:") {
    digitalWrite(led9, HIGH);

  }
  if (string == "off9:") {
    digitalWrite(led9, LOW);
  }

  if (string == "on10:") {
    digitalWrite(led10, HIGH);
  }
  if (string == "off10:") {
    digitalWrite(led10, LOW);
  }
}//Loop End
