#include <SoftwareSerial.h>

//SoftwareSerial Serial1(14, 14); // RX | TX

void setup()

{

  Serial.begin(115200);
  
  Serial1.begin(9600); //Default Baud for comm, it may be different for your Module. Serial.println("The bluetooth gates are open.\n Connect to HC-05 from any other bluetooth device with 1234 as pairing key!.");

}

void loop()

{int i;

  // Feed any data from bluetooth to Terminal.
  if (Serial1.available())
    i=Serial1.read();
    Serial.println(i);
    delay(1000);

  // Feed all data from termial to bluetooth
  //if (Serial.available())
  //  Serial1.write(Serial.read());

}
