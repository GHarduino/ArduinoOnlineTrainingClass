/*
  GreenHouse is use to measure sensor data and control aircon in DSA

*/

#include <IRremote.h>
IRsend irsend;

void setup()
{
  Serial.begin(9600);
}

void loop() {
  
  int khz = 38; // 38kHz carrier frequency for the NEC protocol
  unsigned int irSignal1[] = {4450, 4450, 550 , 1700 , 550 , 1650, 550, 1700 , 500, 600, 550, 600 , 500, 550, 550, 600, 500, 600, 500, 1700, 550 , 1700, 500, 1700, 550, 600, 500, 600, 500, 600, 500, 600, 550, 550, 550, 1700 , 500, 1700, 550, 1650, 550, 600, 500, 600, 550 , 550, 550, 600, 500, 600, 500, 600, 550, 550 , 550, 600, 500 , 1700 , 500, 1700 , 550, 1700, 500, 1700, 550 , 1650, 550 };
  unsigned int irSignal2[] = {4500, 4450, 550 , 1700, 500, 1700, 550, 1650, 550, 600, 500, 600, 550, 600, 500, 600, 500, 600, 500, 1700 , 550, 1700, 500 , 1700, 550 , 550 , 550, 600, 500, 600, 500 , 600, 550, 550, 550, 1700, 500, 1700, 550, 600, 500, 1700, 500, 600, 550, 550, 550 , 550, 550, 600, 500 , 600 , 550 , 550, 550, 1650, 550, 600, 500 , 1700, 550, 1700, 500, 1700, 550, 1650, 550 };
  unsigned int irPower[] = {700, 3550, 800, 3400, 800, 3400, 800, 3400, 850, 1350, 800 , 1350, 850, 3400, 800, 1350, 850 , 1400, 800, 1350, 800, 1350, 850, 1350 , 850, 3350 , 850, 3400, 800, 1350, 800, 3400, 950, 3400, 800, 3400, 800, 1350, 800, 1400, 800, 3400, 800, 3400, 850, 3400, 800, 3400, 850, 1350, 850, 1350, 800, 3400, 800, 3400, 850, 1300, 850, 1350, 850, 1350, 800 , 1350, 850, 1400, 800 , 3400, 800, 1350, 850, 3350 , 850, 1350, 850, 3350, 850, 1350, 800, 1350, 850, 3400, 850, 1350, 800, 3400 , 850 , 1350, 800, 3400, 800 , 1400, 800 , 3400, 800 , 3400, 800};
  unsigned int irDown[] = {650, 3550, 800, 3400, 800, 3400 , 850, 3400 , 800, 1350 , 800 , 1400, 800, 3400 , 800 , 1350, 850, 1400, 800, 1350, 800 , 1400 , 800, 1350 , 850, 3350, 850, 3400, 800, 1350, 800, 3400, 950, 3400, 800 , 3400, 800 , 1350 , 800, 1400, 800, 3400, 800, 3400, 850, 1350, 800, 1350, 850, 1400, 800, 1350, 800, 3400, 850, 3700 , 800 , 1350, 850 , 1350, 850, 3400, 800, 3400, 850, 1350, 850, 3400, 800, 1350, 800, 3400, 800, 1350 , 850, 3400, 850, 1350, 800 , 1350, 850 , 3400, 850, 1350, 800, 3400, 800, 1350, 850, 3400 , 800 , 1350, 850, 3400 , 800, 3400, 800};
  unsigned int irUp[] = {700, 3500 , 850, 3400 , 800 , 3400, 850, 3350, 850 , 1300, 900, 1300 , 850, 3350, 850, 1350, 900, 1300, 850, 1350 , 850, 1300, 850, 1300, 900, 3350 , 850, 3350, 850 , 1350, 800, 3400, 950, 3350, 850, 3350, 850, 1350, 850, 1300, 900, 3350, 850, 3350, 850, 3350, 850, 3400, 850, 1350, 850, 1300, 850 , 3400, 850, 3350, 850, 1300, 850, 1350, 850, 1300, 850, 1350, 900, 1300, 850, 3400, 800, 1350, 800, 3400, 850, 1300, 850, 3400, 800, 1350, 850, 1350, 900, 3350, 850, 1350 , 800 , 3400, 800, 1350, 850 , 3400, 800, 1350, 800 , 3400, 850 , 3400, 750};

  /*

    for (i = 0; i < 10; i++)
    {
      irsend.sendRaw(irPower, sizeof(irPower) / sizeof(irPower[0]), khz); //Note the approach used to automatically calculate the size of the array.
      delay(1000); //In this example, the signal will be repeated every 5 seconds, approximately.

      for (counter = 0; counter < 10; counter++)
      {
        irsend.sendRaw(irDown, sizeof(irDown) / sizeof(irDown[0]), khz); //Note the approach used to automatically calculate the size of the array.
        delay(5000); //In this example, the signal will be repeated every 5 seconds, approximately.
      }

      for (counter = 0; counter < 10; counter++)
      {
        irsend.sendRaw(irUp, sizeof(irUp) / sizeof(irUp[0]), khz); //Note the approach used to automatically calculate the size of the array.
        delay(5000); //In this example, the signal will be repeated every 5 seconds, approximately.
      }
    }
  */
  Serial.println("up ");
  irsend.sendRaw(irSignal1, sizeof(irSignal1) / sizeof(irSignal1[0]), khz); //Note the approach used to automatically calculate the size of the array.
  delay(2000); //In this example, the signal will be repeated every 5 seconds, approximately.
}
