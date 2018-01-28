
#include<SoftwareSerial.h>
SoftwareSerial Bluetooth(10,11);
void setup() {
  Bluetooth.begin(9600);
  pinMode(5,OUTPUT);
  digitalWrite(5,LOW);
}

void loop() {
  int in;
  if(Bluetooth.available())
  {
    in = Bluetooth.read();
    switch(in)
    {
      case '1': Bluetooth.println("You Send me one"); digitalWrite(5,HIGH); break;
      case '2': Bluetooth.println("You Send me two"); digitalWrite(5,LOW); break;
      default:Bluetooth.println("Unknown command");break;
    }
  } 
}
