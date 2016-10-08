#include <SoftwareSerial.h>
//http://www.instructables.com/id/Arduino-Android-Bluetooth-Car/
SoftwareSerial mySerial(10, 11); // RX, TX
int led = 13;
int led2 = 12;
char myChar = 'a';
String string;
char LorR;
int enA = 3;
int in1 = 4;
int in2 = 5;
int enB = 6;
int in3 = 7;
int in4 = 8;
void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.println("Goodnight moon!");
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}
void loop() // run over and over
{
  string = "";
  //Add to string
  while (true) {
    myChar = mySerial.read();
    if (32 <= myChar & myChar <= 127) {
      string += myChar;
    }
    if (myChar == ':') {
      break;
    }
    delay(10);
  }// While End
  //Analyse string
  Serial.println(string);
  /*
  if (string != "off3:" && string != "on3:" && string != "off13:" && string != "on13:") {
    if (string != "L0:" && string != "R0:") {
      //code for setting motor left or right
      if (string[0] == 'L') {
        LorR = 'L';
      } else {
        LorR = 'R';
      }
      string.remove(0, 1);
      //code for putting it in reverse
      if (string[0] == '-') {
        string.remove(0, 1);
        string.remove((string.length() - 1), 1);
        Serial.println(string);
        if (LorR == 'L') {
          digitalWrite(in1, HIGH);
          digitalWrite(in2, LOW);
          analogWrite(enA, string.toInt());
        } else {
          digitalWrite(in3, LOW);
          digitalWrite(in4, HIGH);
          analogWrite(enB, string.toInt());
        }
      } else {
        string.remove((string.length() - 1), 1);
        Serial.println(string);
        if (LorR == 'L') {
          digitalWrite(in1, LOW);
          digitalWrite(in2, HIGH);
          analogWrite(enA, string.toInt());
        } else {
          digitalWrite(in3, HIGH);
          digitalWrite(in4, LOW);
          analogWrite(enB, string.toInt());
        }
      }
    } else {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
    }
  }//End of long if statment
*/
  
  if (string == "on13:") {
    digitalWrite(led, HIGH);
    Serial.print("on13");
    delay(2000);
  }
  if (string == "off13:") {
    digitalWrite(led, LOW);
    Serial.print("off13");
    delay(2000);
  }

  if (string == "on3:") {
    digitalWrite(led2, HIGH);
     Serial.print("on3");
    delay(2000);
  }
  if (string == "off3:") {
    digitalWrite(led2, LOW);
    delay(2000);
  }
}//Loop End
