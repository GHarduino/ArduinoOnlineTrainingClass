#include<SoftwareSerial.h>

SoftwareSerial Bluetooth(7, 6);       //TXD11  RXD12

void setup() {
  Serial.begin(9600);
  Bluetooth.begin(9600);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  

}
void loop() {
  char ch;
  if (Bluetooth.available()) {
    ch = Bluetooth.read();
    Serial.write(ch);

    if(ch=='1')
    {
      digitalWrite(9,HIGH);
    }
     if(ch=='2')
    {
      digitalWrite(10,HIGH);
    }
     if(ch=='3')
    {
      digitalWrite(11,HIGH);
    }
    
    if(ch=='4')
    {
      digitalWrite(9,LOW);
    }
     if(ch=='5')
    {
      digitalWrite(10,LOW);
    }
     if(ch=='6')
    {
      digitalWrite(11,LOW);
    }
    

    
  }
  
}

