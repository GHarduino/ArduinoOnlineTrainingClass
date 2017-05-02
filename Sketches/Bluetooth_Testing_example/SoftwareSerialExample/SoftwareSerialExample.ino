/*
  This program is to communicate with bluetooth
  and android mobile phone
  by Dr. Aung Win Htut

 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10); // RX, TX
char ch;
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
}

void loop() { // run over and over
  
  if (mySerial.available()) {
    //Serial.println("bluetooth sending");
    ch=mySerial.read();
    Serial.println(ch);
    if(ch=='1')
    {
      funForward();
    }
    else if(ch=='2')
    {
      funBackward();
    }
    else if(ch=='3')
    {
      funTurnLeft();
    }
    else if(ch=='4')
    {
      funTrunRight();
    }
    else if(ch=='5')
    {
      funLoopLeft();
    }
    else if(ch=='6')
    {
      funLoopRight();
    }
    else if(ch=='7')
    {
      funStop();
    }
    else if(ch=='8')
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
  Serial.println("Forward");
}
void funBackward()
{
    Serial.println("funBackward");
}
void funTurnLeft()
{
    Serial.println("funTurnLeft");
}
void funTrunRight()
{
    Serial.println("funTrunRight");
}
void funLoopLeft()
{
    Serial.println("funTurnLeft");
}
void funLoopRight()
{
    Serial.println("funTrunRight");
}
void funStop()
{
    Serial.println("Stop");
}


