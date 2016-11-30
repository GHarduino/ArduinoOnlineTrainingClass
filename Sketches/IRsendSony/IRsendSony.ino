#include <IRremote.h>

//IR LED on D3
String readString;
IRsend irsend;

void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
}

void loop() {

  //irsend.sendNEC(0xFF7887, 32);
  for (int i = 0; i < 3; i++)
  {
    irsend.sendSony(0xa90, 12); // Sony TV power code
    delay(40);
  }
  digitalWrite(2, HIGH);
  delay(100);
  digitalWrite(2, LOW);
  delay(7500);


}
