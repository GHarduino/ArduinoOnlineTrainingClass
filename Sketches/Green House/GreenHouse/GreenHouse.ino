/*
  GreenHouse is use to measure sensor data and control aircon in DSA

*/

#include<SoftwareSerial.h>
#include <IRremote.h>
#include <dht.h>
#define DHT22_PIN 4
#define LDR_PIN A0
#define MQ7A_PIN A1
#define MQ7D_PIN 5

dht DHT;
SoftwareSerial BlueTooth(11, 10);       //TXD11  RXD12

float temp;
float temp1;
float light;
float humidity;
float gas;
int limit;

struct
{
  uint32_t total;
  uint32_t ok;
  uint32_t crc_error;
  uint32_t time_out;
  uint32_t connect;
  uint32_t ack_l;
  uint32_t ack_h;
  uint32_t unknown;
} stat = { 0, 0, 0, 0, 0, 0, 0, 0};
IRsend irsend;

void setup()
{
  Serial.begin(9600);
  Serial.println("Green House system is Activated...");
  BlueTooth.begin(9600);
  delay(500);
}

void loop() {
  int khz = 38; // 38kHz carrier frequency for the NEC protocol
  unsigned int irSignal1[] = {4450, 4450, 550 , 1700 , 550 , 1650, 550, 1700 , 500, 600, 550, 600 , 500, 550, 550, 600, 500, 600, 500, 1700, 550 , 1700, 500, 1700, 550, 600, 500, 600, 500, 600, 500, 600, 550, 550, 550, 1700 , 500, 1700, 550, 1650, 550, 600, 500, 600, 550 , 550, 550, 600, 500, 600, 500, 600, 550, 550 , 550, 600, 500 , 1700 , 500, 1700 , 550, 1700, 500, 1700, 550 , 1650, 550 };
  unsigned int irSignal2[] = {4500, 4450, 550 , 1700, 500, 1700, 550, 1650, 550, 600, 500, 600, 550, 600, 500, 600, 500, 600, 500, 1700 , 550, 1700, 500 , 1700, 550 , 550 , 550, 600, 500, 600, 500 , 600, 550, 550, 550, 1700, 500, 1700, 550, 600, 500, 1700, 500, 600, 550, 550, 550 , 550, 550, 600, 500 , 600 , 550 , 550, 550, 1650, 550, 600, 500 , 1700, 550, 1700, 500, 1700, 550, 1650, 550 };

  int chk = DHT.read22(DHT22_PIN);
  switch (chk)
  {
    case DHTLIB_OK:
      stat.ok++;
      Serial.println("OK,\t");
      break;
    case DHTLIB_ERROR_CHECKSUM:
      stat.crc_error++;
      Serial.println("Checksum error,\t");
      break;
    case DHTLIB_ERROR_TIMEOUT:
      stat.time_out++;
      Serial.println("Time out error,\t");
      break;
    case DHTLIB_ERROR_CONNECT:
      stat.connect++;
      Serial.println("Connect error,\t");
      break;
    case DHTLIB_ERROR_ACK_L:
      stat.ack_l++;
      Serial.println("Ack Low error,\t");
      break;
    case DHTLIB_ERROR_ACK_H:
      stat.ack_h++;
      Serial.println("Ack High error,\t");
      break;
    default:
      stat.unknown++;
      Serial.println("Unknown error,\t");
      break;
  }

  humidity = DHT.humidity;
  temp1 = DHT.temperature;
  light = analogRead(LDR_PIN);
  gas = analogRead(MQ7A_PIN);
  limit = digitalRead(MQ7D_PIN);


  Serial.print("Temp(DHT22)");
  Serial.print(",\t");
  Serial.print("Humidity");
  Serial.print(",\t");
  Serial.print("light");
  Serial.print(",\t");
  Serial.print("gas");
  Serial.print(",\t");
  Serial.println("limit");
  Serial.print(temp1);
  Serial.print(",\t");
  Serial.print(",\t");
  Serial.print(humidity);
  Serial.print(",\t");
  Serial.print(",\t");
  Serial.print(light);
  Serial.print(",\t");
  Serial.print(",\t");
  Serial.print(gas);
  Serial.print(",\t");
  Serial.print(",\t");
  Serial.print(limit);
  Serial.println("");

  String t, h, l, g;
  t = String(temp1);
  h = String(humidity);
  l = String(light);
  g = String(gas);
  BlueTooth.println(l + '@' + t + '@' + g + '@' + h );
  Serial.println(l + '@' + t + '@' + g + '@' + h );

  delay(300);
  //irsend.sendRaw(irSignal1, sizeof(irSignal1) / sizeof(irSignal1[0]), khz); //Note the approach used to automatically calculate the size of the array.

  // delay(5000); //In this example, the signal will be repeated every 5 seconds, approximately.

  //irsend.sendRaw(irSignal2, sizeof(irSignal2) / sizeof(irSignal2[0]), khz); //Note the approach used to automatically calculate the size of the array.
  // delay(5000); //In this example, the signal will be repeated every 5 seconds, approximately.
}
