#include <IRremote.h>

//IR LED on D3
String readString;
IRsend irsend;

void setup()
{
  Serial.begin(9600);
}

void loop() {
  while (Serial.available()) {
    delay(3);  
    char c = Serial.read();
    readString += c; 
  } 
  if (readString.length() >0) {
    Serial.println(readString);
    if (readString == "on")     //Text from android
    {
      irsend.sendSony(0xFD08F7, 32);
    }
    if (readString == "off")    //Text from android
    {
      irsend.sendNEC(0xFD08F7, 32);
    }
    if (readString == "volup")   //Text from android  
    {
      irsend.sendNEC(0xFDDA25, 32);
    }
    if (readString == "voldown")  //Text from android
    {
      irsend.sendNEC(0xFD7887, 32);
    }
    if (readString == "mute")     //Text from android
    {
      irsend.sendNEC(0xFDAA55, 32);
    }
    readString="";
  }
}
