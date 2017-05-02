/*
  This program is to communicate with bluetooth
  and android mobile phone
  by Dr. Aung Win Htut

*/
#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10); // RX, TX

int in1=2; //Arduino pin 2 connected to L298 pin in1
int in2=3; //Arduino pin 3 connected to L298 pin in2
int in3=4; //Arduino pin 4 connected to L298 pin in3
int in4=5; //Arduino pin 5 connected to L298 pin in4
int ena=6; //Arduino pin 6 connected to L298 pin ena
int enb=7; //Arduino pin 7 connected to L298 pin enb
int d=0; //delay if you need to control speed

char ch;
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);

  Serial.println("Goodnight GreenHackers!, I am your bluetooth car");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
}

void loop() { // run over and over

  if (mySerial.available()) {
    //Serial.println("bluetooth sending");
    ch = mySerial.read();
    Serial.println(ch);
    if (ch == '2')
    {
      funTurnLeft();
    }
    else if (ch == '1')
    {
      funTrunRight();
    }
    else if (ch == '3')
    {
      funForward();
    }
    else if (ch == '4')
    {
      funBackward();
    }
    else if (ch == '5')
    {
      funLoopLeft();
    }
    else if (ch == '6')
    {
      funLoopRight();
    }
    else if (ch == '7')
    {
      funStop();
    }
    else if (ch == '8')
    {
      funStop();
    }

  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}


void funForward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(ena, 255);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enb, 255);
  delay(d);
  //funStop();
  
}
void funBackward()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(ena, 255);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enb, 255);
  delay(d);
  //funStop();
}
void funTurnLeft()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(ena, 255);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enb, 255);
  delay(100);
  funStop();
  
}
void funTrunRight()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(ena, 255);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enb, 255);
  delay(100);
  funStop();
}
void funLoopLeft()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(ena, 255);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enb, 255);
}
void funLoopRight()
{
   digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(ena, 255);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enb, 255);
}
void funStop()
{
  analogWrite(ena,0);
  analogWrite(enb,0);
}


