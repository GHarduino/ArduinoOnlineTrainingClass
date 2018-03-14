/*
   2017 05 13  adding ethernet shield
   temperature and humidity min and max limit checking
   by Dr. Aung Win Htut
*/
#include<SoftwareSerial.h>  //for bluetooth
#include <dht.h> //for DHT22


//pin configuration
#define DHT22_PIN 12

static int stemperature = 3; // 1-very cold <10  2-cold <20  3-normal 20-30 4-hot 30-35 5-very hot >35
static int shumidity = 3; //  5-very humid >60  4-humid 50-60 3-normal 40-50 2-dry 40-30 1-very dry <30

//creating dht and blueooth objects
dht DHT;
SoftwareSerial BlueTooth(10, 11);       //TXD11  RXD12



//creating structure for dht22
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


//Setting up for the very first time and once only
void setup() {
  Serial.begin(9600);

  Serial.println("Hello,Green Hackers!"); //$
  BlueTooth.begin(9600);
  /*
    if (Ethernet.begin(mac) == 0) {
      Serial.println("Failed to configure Ethernet using DHCP");
      // no point in carrying on, so do nothing forevermore:
      // try to congifure using IP address instead of DHCP:
      Ethernet.begin(mac, ip);
    }
    Serial.println("connecting...");

    // if you get a connection, report back via serial:
    if (client.connect(server, 80)) {
      Serial.println("connected");
    }
    else
    {
      Serial.println("cannot connect");
    }
  */
  delay(500);
}

////////////////////////////////////////
//Main Loop Start Here
void loop() {
  Serial.println("Loop Started");//$

  funReadSensor(); //calling fun to read sensor values
  delay(1000);

  if (BlueTooth.available()) {
    Serial.write(BlueTooth.read());
  }
  if (Serial.available() > 0)
  {
    int incomingByte = Serial.read();
  }
}
//Main Loop End Here
//////////////////////////////////////////


//////////////////////////////////////////////
//Function for Reading Sensor value start here
void funReadSensor()
{
  //sensor variables
  float temp = 0;
  float temp1;
  float light;
  float humidity;
  float gas;

  

 
  //Read DHT sensor to measure Temperature and Humidity
  //(10kOhm pull down)
  //checking error!
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

  //if no error read humidity and temperature
  humidity = DHT.humidity;
  temp1 = DHT.temperature;


 
  int T1 = temp1;
  int H = humidity;



  //Must change int to string to send by bluetooth and serial
  String l, t, t1, h, g;
  String st, sh;

  //change integer to string
  t1 = String(T1);
  h = String(H);


  //Sending to bluetooth , separating by special @ char
  BlueTooth.println(t1 + '@' + t1 + '@' + h );
  //Sending to bluetooth end here

 
}
//Function for Reading Sensor value end here
////////////////////////////////////////////////


