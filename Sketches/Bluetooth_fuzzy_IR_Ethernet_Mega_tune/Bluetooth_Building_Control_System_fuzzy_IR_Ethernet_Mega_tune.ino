/*
   2017 05 13  adding ethernet shield
   temperature and humidity min and max limit checking
   by Dr. Aung Win Htut
*/
#include<SoftwareSerial.h>  //for bluetooth
#include <dht.h> //for DHT22
#include <IRremote.h>//for IR control //Control pin must be digital pin (3)!!!!!
#include <LiquidCrystal_I2C.h>
//for ethernet shield
#include <SPI.h>


//unsigned int irPower[]        = {9000, 4450, 550, 550, 600, 550, 600, 550, 550, 550, 550, 550, 600, 550, 600, 550, 550, 550, 550, 1700, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 550, 600, 600, 500, 600, 1650, 550, 1750, 550, 1650, 550, 600, 600, 550, 550, 550, 550, 1700, 600, 1650, 550, 550, 600, 550, 600, 550, 600, 1600, 600, 1700, 600, 1600, 600 };
//unsigned int irCool[]         = {8900, 4500, 600, 550, 550, 550, 550, 550, 600, 550, 600, 550, 600, 500, 600, 500, 600, 550, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 550, 1750, 550, 1650, 550, 1750, 550, 1650, 550, 600, 600, 550, 600, 500, 600, 500, 600, 1700, 600, 500, 600, 500, 600, 550, 600, 1650, 600, 1650, 700, 1600, 550, 1650, 600, 550, 600, 1650, 550, 1700, 600, 1650, 600 };
//signed int irHumidifier[]     = {8900, 4500, 500, 650, 550, 550, 550, 550, 550, 550, 550, 650, 550, 550, 550, 550, 550, 550, 600, 1700, 600, 1650, 550, 1750, 500, 1700, 550, 1750, 550, 1650, 550, 1750, 500, 1700, 550, 600, 500, 650, 500, 600, 550, 550, 550, 1750, 550, 550, 600, 550, 550, 600, 500, 1700, 600, 1700, 500, 1700, 550, 1750, 500, 600, 550, 1750, 500, 1700, 600, 1700, 500 };
//signed int irSwingLeftRight[] = {9000, 4450, 650, 450, 650, 500, 600, 500, 700, 450, 650, 450, 700, 400, 650, 500, 700, 450, 650, 1550, 700, 1600, 650, 1600, 650, 1600, 650, 1600, 700, 1550, 650, 1600, 700, 1550, 650, 1600, 700, 450, 650, 1600, 650, 1600, 650, 1600, 700, 450, 600, 500, 650, 500, 650, 450, 700, 1550, 700, 450, 650, 450, 700, 450, 650, 1600, 650, 1600, 700, 1550, 650 };



//#include <Ethernet.h>

/*
  byte mac[] = {
  0x90, 0xA2, 0xDA, 0x0F, 0x3A, 0xDC
  };
  IPAddress server(192, 168, 1, 100);
  IPAddress ip(192, 168, 1, 5);
  EthernetClient client;
*/
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); //16*4
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4 , 5, 6, 7, 3, POSITIVE); //20*4
//LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 21, 20, 6, 7, 3, POSITIVE); //20*4
//LiquidCrystal_I2C lcd(0x27, 20,4);



//pin configuration
#define DHT22_PIN 12   //pull down 10k digital
#define ldr A0        //pull up 10k analog
#define MQ2 A1        //pull up 10k analog
#define IRtransmitter 9
#define IRreceiver 2
#define Buzzer 11
#define led1 8
#define Relay1 10
#define Relay2 3
#define Relay3 14
#define Relay4 15
#define LM35 A2


//Config values
#define maxgas   2000
#define mingas   0


//flags and key parameters
static int sgas = 0;
static int stemperature = 3; // 1-very cold <10  2-cold <20  3-normal 20-30 4-hot 30-35 5-very hot >35
static int shumidity = 3; //  5-very humid >60  4-humid 50-60 3-normal 40-50 2-dry 40-30 1-very dry <30
static int tflag[5] = {0, 0, 0, 0, 0}; //flag =3 trigger
static int hflag[5] = {0, 0, 0, 0, 0}; //flag =3 trigger

static String l, t, t1, h, g;
static String st, sh;

static int iShot = 0;

//IR object declare
IRsend irsend;

//creating dht and blueooth objects
dht DHT;
SoftwareSerial BlueTooth(6, 7);       //TXD11  RXD12

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
  lcd.begin(20, 4);
  lcd.backlight();
  lcd.setCursor(0, 1);
  lcd.print("     Welcome to     ");
  lcd.setCursor(0, 2);
  lcd.print("   Control Center   ");

  //pinmode settings
  pinMode(led1, OUTPUT);
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);
  pinMode(Buzzer, OUTPUT);

  Serial.println("Hello,Green Hackers!"); //$
  BlueTooth.begin(9600);
  //Serial.println("try to connect router...");
  /*
    //Ethernet.begin(mac, ip);
    //Serial.println(Ethernet.localIP());
    //Serial.println("connecting...");
    if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
    }
    Serial.println(Ethernet.localIP());
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
  randomSeed(analogRead(A3));
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

  //if you want to read lm35 temperature sensor
  //Serial.print("Reading Temp");
  //temp = analogRead(lm35);
  //temp = temp * 0.48828125;

  //Reading Light value (10kOhm pull up)
  light = analogRead(ldr);

  //Reading Gas vlue (10kOhm pull up)
  gas = analogRead(MQ2);
  Serial.println(gas);

  if ((gas > mingas) && (gas < maxgas))
  {
    sgas = gas;
  }
  Serial.println(sgas);

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
  //tune
  temp = random(1, 6);
  temp1 = temp1 - temp;
  //tune end
  //temp = analogRead(LM35);
  //temp=(29*temp)/198;
  //temp1=(temp1+temp)/2;

  Serial.print("temp");
  Serial.println(temp1);
  Serial.print("humidity");
  Serial.println(humidity);
  delay(1000);
  //sending to serial port //$
  Serial.print("Light");
  Serial.print(",\t");
  Serial.print(",\t");
  Serial.print("GAS");
  Serial.print(",\t");
  Serial.print("Temp(DHT22)");
  Serial.print(",\t");
  Serial.println("Humidity");
  Serial.print(light);
  Serial.print(",\t");
  Serial.print(",\t");
  Serial.print(sgas);
  Serial.print(",\t");
  Serial.print(",\t");
  Serial.print(temp1);
  Serial.print(",\t");
  Serial.print(",\t");
  Serial.print(humidity);
  Serial.println("");
  //sending serial data end here

  //copying measured variables
  int L = light;
  int T = temp;
  int T1 = temp1;
  int H = humidity;
  int G = sgas;

  //Checking fuzzy levels for temperature
  //Call funShowFuzzyResult onlyif the result actually change 3 times
  if (T1 < 10)
  {
    for (int i = 1; i < 5; i++)
    {
      tflag[i] = 0;
    }
    tflag[0]++;
    if (tflag[0] == 3)
    {
      stemperature = 1;
      funShowFuzzyResult();
    }
  }
  else if ((T1 >= 10) && (T1 < 20))
  {
    tflag[0] = 0;
    tflag[2] = 0;
    tflag[3] = 0;
    tflag[4] = 0;

    tflag[1]++;
    if (tflag[1] == 3)
    {
      stemperature = 2;
      funShowFuzzyResult();
    }
  }
  else if ((T1 >= 20) && (T1 < 28))
  {
    tflag[0] = 0;
    tflag[1] = 0;
    tflag[3] = 0;
    tflag[4] = 0;

    tflag[2]++;
    if (tflag[2] == 3)
    {
      stemperature = 3;
      funShowFuzzyResult();
    }
  }
  else if ((T1 >= 28) && (T1 <= 32))
  {
    tflag[0] = 0;
    tflag[1] = 0;
    tflag[2] = 0;
    tflag[4] = 0;

    tflag[3]++;
    if (tflag[3] == 3)
    {
      stemperature = 4;
      funShowFuzzyResult();
    }
  }
  else if (T1 > 32)
  {
    tflag[0] = 0;
    tflag[1] = 0;
    tflag[2] = 0;
    tflag[3] = 0;

    tflag[4]++;
    if (tflag[4] == 3)
    {
      stemperature = 5;
      funShowFuzzyResult();
    }
  }

  //Checking fuzzy levels for humidity
  if (H > 60)
  {
    for (int i = 1; i < 5; i++)
    {
      hflag[i] = 0;
    }
    hflag[0]++;
    if (hflag[0] == 3)
    {
      shumidity = 1;
      funShowFuzzyResult();
    }
  }
  else if ((H >= 45) && (H < 60))
  {
    hflag[0] = 0;
    hflag[2] = 0;
    hflag[3] = 0;
    hflag[4] = 0;

    hflag[1]++;
    if (hflag[1] == 3)
    {
      shumidity = 2;
      funShowFuzzyResult();
    }
  }
  else if ((H >= 35) && (H < 45))
  {
    hflag[0] = 0;
    hflag[1] = 0;
    hflag[3] = 0;
    hflag[4] = 0;

    hflag[2]++;
    if (hflag[2] == 3)
    {
      shumidity = 3;
      funShowFuzzyResult();
    }
  }
  else if ((H >= 30) && (H <= 35))
  {
    hflag[0] = 0;
    hflag[1] = 0;
    hflag[2] = 0;
    hflag[4] = 0;

    hflag[3]++;
    if (hflag[3] == 3)
    {
      shumidity = 4;
      funShowFuzzyResult();
    }
  }
  else if (H < 30)
  {
    hflag[0] = 0;
    hflag[1] = 0;
    hflag[2] = 0;
    hflag[3] = 0;

    hflag[4]++;
    if (hflag[4] == 3)
    {
      shumidity = 5;
      funShowFuzzyResult();
    }
  }

  //Checking light value whether dark and switch led on buzzer on
  //Call funShowFuzzyResult onlyif the result actually change 3 times
  if (L > 400)
  {
    digitalWrite(led1, LOW);
  }
  else
  {
    funBuzzerLed(); //calling buzzer on led on function
  }

  //Must change int to string to send by bluetooth and serial


  //change integer to string
  l = String(L);
  t = String(T);
  t1 = String(T1);
  h = String(H);
  g = String(G);
  st = String(stemperature);
  sh = String(shumidity);

  //Sending Serial again //$
  Serial.print(L);
  Serial.print(",\t");
  Serial.print(",\t");
  Serial.print(T);
  Serial.print(",\t");
  Serial.print(",\t");
  Serial.print(T1);
  Serial.print(",\t");
  Serial.print(",\t");
  Serial.println(H);
  Serial.println(t1 + '@' + h + '@' + l + '@' + g );
  //Sending Serial End here

  //Sending to bluetooth , separating by special @ char
  BlueTooth.println(t1 + '@' + t1 + '@' + h + '@' + l + '@' + g + '@' + st + '@' + sh );
  //Sending to bluetooth end here

  //LCD print out start here
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp       ");
  lcd.print(t1);
  lcd.setCursor(0, 1);
  lcd.print("Humidity   ");
  lcd.print(h);
  lcd.setCursor(0, 2);
  lcd.print("Light      ");
  lcd.print(l);
  lcd.setCursor(0, 3);
  lcd.print("GAS        ");
  lcd.print(g);
  //LCD print out end here
}
//Function for Reading Sensor value end here
////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Showing FUZZY results on LCD
void funShowFuzzyResult()
{
  lcd.clear();
  switch (stemperature)
  {
    case 1: lcd.setCursor(0, 0); lcd.print("Temp:     Very Cold");   break;
    case 2: lcd.setCursor(0, 0); lcd.print("Temp:     Cold");        break;
    case 3: lcd.setCursor(0, 0); lcd.print("Temp:     Normal");      break;
    case 4: lcd.setCursor(0, 0); lcd.print("Temp:     Hot");         break;
    case 5: lcd.setCursor(0, 0); lcd.print("Temp:     Very Hot");   break;
  }
  lcd.setCursor(0, 1); lcd.print(t1); lcd.print(" *C");
  switch (shumidity)
  {
    case 1: lcd.setCursor(0, 2); lcd.print("Humidity: Very Humid");    break;
    case 2: lcd.setCursor(0, 2); lcd.print("Humidity: Humid");         break;
    case 3: lcd.setCursor(0, 2); lcd.print("Humidity: Normal");        break;
    case 4: lcd.setCursor(0, 2); lcd.print("Humidity: Dry");           break;
    case 5: lcd.setCursor(0, 2); lcd.print("Humidity: Very Dry");      break;
  }


  switch (stemperature + shumidity)
  {

    case 7:     funRelay(1);    break;
    case 8:     funRelay(2);    break;
    case 9:     funRelay(3);    break;
    case 10:    funRelay(4);    break;
    default:    funRelay(0);    break;
  }

  lcd.setCursor(0, 3); lcd.print(h); lcd.print(" %");
  funFuzzyControlAircon(stemperature + shumidity);
  funBuzzerLed();

  delay(5000);
}
//function End here
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////
//function for buzzer on led on
void funBuzzerLed()
{
  digitalWrite(led1, HIGH);
  digitalWrite(Buzzer, HIGH);
  delay(1000);
  digitalWrite(Buzzer, LOW);
  digitalWrite(led1, LOW);
  delay(100);
}
//function end here
/////////////////////////////////////



void funFuzzyControlAircon(int iFuzzy)
{
  //IRcodes
  int khz = 38; // 38kHz carrier frequency for the NEC protocol
  unsigned int irSignal1[] = {4450, 4450, 550 , 1700 , 550 , 1650, 550, 1700 , 500, 600, 550, 600 , 500, 550, 550, 600, 500, 600, 500, 1700, 550 , 1700, 500, 1700, 550, 600, 500, 600, 500, 600, 500, 600, 550, 550, 550, 1700 , 500, 1700, 550, 1650, 550, 600, 500, 600, 550 , 550, 550, 600, 500, 600, 500, 600, 550, 550 , 550, 600, 500 , 1700 , 500, 1700 , 550, 1700, 500, 1700, 550 , 1650, 550 };
  unsigned int irSignal2[] = {4500, 4450, 550 , 1700, 500, 1700, 550, 1650, 550, 600, 500, 600, 550, 600, 500, 600, 500, 600, 500, 1700 , 550, 1700, 500 , 1700, 550 , 550 , 550, 600, 500, 600, 500 , 600, 550, 550, 550, 1700, 500, 1700, 550, 600, 500, 1700, 500, 600, 550, 550, 550 , 550, 550, 600, 500 , 600 , 550 , 550, 550, 1650, 550, 600, 500 , 1700, 550, 1700, 500, 1700, 550, 1650, 550 };
  unsigned int irPower[] = {700, 3550, 800, 3400, 800, 3400, 800, 3400, 850, 1350, 800 , 1350, 850, 3400, 800, 1350, 850 , 1400, 800, 1350, 800, 1350, 850, 1350 , 850, 3350 , 850, 3400, 800, 1350, 800, 3400, 950, 3400, 800, 3400, 800, 1350, 800, 1400, 800, 3400, 800, 3400, 850, 3400, 800, 3400, 850, 1350, 850, 1350, 800, 3400, 800, 3400, 850, 1300, 850, 1350, 850, 1350, 800 , 1350, 850, 1400, 800 , 3400, 800, 1350, 850, 3350 , 850, 1350, 850, 3350, 850, 1350, 800, 1350, 850, 3400, 850, 1350, 800, 3400 , 850 , 1350, 800, 3400, 800 , 1400, 800 , 3400, 800 , 3400, 800};
  unsigned int irDown[] = {650, 3550, 800, 3400, 800, 3400 , 850, 3400 , 800, 1350 , 800 , 1400, 800, 3400 , 800 , 1350, 850, 1400, 800, 1350, 800 , 1400 , 800, 1350 , 850, 3350, 850, 3400, 800, 1350, 800, 3400, 950, 3400, 800 , 3400, 800 , 1350 , 800, 1400, 800, 3400, 800, 3400, 850, 1350, 800, 1350, 850, 1400, 800, 1350, 800, 3400, 850, 3700 , 800 , 1350, 850 , 1350, 850, 3400, 800, 3400, 850, 1350, 850, 3400, 800, 1350, 800, 3400, 800, 1350 , 850, 3400, 850, 1350, 800 , 1350, 850 , 3400, 850, 1350, 800, 3400, 800, 1350, 850, 3400 , 800 , 1350, 850, 3400 , 800, 3400, 800};
  unsigned int irUp[] = {700, 3500 , 850, 3400 , 800 , 3400, 850, 3350, 850 , 1300, 900, 1300 , 850, 3350, 850, 1350, 900, 1300, 850, 1350 , 850, 1300, 850, 1300, 900, 3350 , 850, 3350, 850 , 1350, 800, 3400, 950, 3350, 850, 3350, 850, 1350, 850, 1300, 900, 3350, 850, 3350, 850, 3350, 850, 3400, 850, 1350, 850, 1300, 850 , 3400, 850, 3350, 850, 1300, 850, 1350, 850, 1300, 850, 1350, 900, 1300, 850, 3400, 800, 1350, 800, 3400, 850, 1300, 850, 3400, 800, 1350, 850, 1350, 900, 3350, 850, 1350 , 800 , 3400, 800, 1350, 850 , 3400, 800, 1350, 800 , 3400, 850 , 3400, 750};



  //  unsigned int irPower[]        = {9000, 4450, 550, 550, 600, 550, 600, 550, 550, 550, 550, 550, 600, 550, 600, 550, 550, 550, 550, 1700, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 550, 600, 600, 500, 600, 1650, 550, 1750, 550, 1650, 550, 600, 600, 550, 550, 550, 550, 1700, 600, 1650, 550, 550, 600, 550, 600, 550, 600, 1600, 600, 1700, 600, 1600, 600 };
  unsigned int irCool[]         = {8900, 4500, 600, 550, 550, 550, 550, 550, 600, 550, 600, 550, 600, 500, 600, 500, 600, 550, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 550, 1750, 550, 1650, 550, 1750, 550, 1650, 550, 600, 600, 550, 600, 500, 600, 500, 600, 1700, 600, 500, 600, 500, 600, 550, 600, 1650, 600, 1650, 700, 1600, 550, 1650, 600, 550, 600, 1650, 550, 1700, 600, 1650, 600 };
  signed int irHumidifier[]     = {8900, 4500, 500, 650, 550, 550, 550, 550, 550, 550, 550, 650, 550, 550, 550, 550, 550, 550, 600, 1700, 600, 1650, 550, 1750, 500, 1700, 550, 1750, 550, 1650, 550, 1750, 500, 1700, 550, 600, 500, 650, 500, 600, 550, 550, 550, 1750, 550, 550, 600, 550, 550, 600, 500, 1700, 600, 1700, 500, 1700, 550, 1750, 500, 600, 550, 1750, 500, 1700, 600, 1700, 500 };
  signed int irSwingLeftRight[] = {9000, 4450, 650, 450, 650, 500, 600, 500, 700, 450, 650, 450, 700, 400, 650, 500, 700, 450, 650, 1550, 700, 1600, 650, 1600, 650, 1600, 650, 1600, 700, 1550, 650, 1600, 700, 1550, 650, 1600, 700, 450, 650, 1600, 650, 1600, 650, 1600, 700, 450, 600, 500, 650, 500, 650, 450, 700, 1550, 700, 450, 650, 450, 700, 450, 650, 1600, 650, 1600, 700, 1550, 650 };


  /*
     FF38C7 Power
    Decoded NEC: FF38C7 (32 bits)
    Raw (68): 9000 -4450 550 -550 600 -550 600 -550 550 -550 550 -550 600 -550 600 -550 550 -550 550 -1700 600 -1650 600 -1650 600 -1650 600 -1650 600 -1650 600 -1650 600 -1650 550 -600 600 -500 600 -1650 550 -1750 550 -1650 550 -600 600 -550 550 -550 550 -1700 600 -1650 550 -550 600 -550 600 -550 600 -1600 600 -1700 600 -1600 600
    unsigned int irPower[] = {9000, -4450, 550, -550, 600, -550, 600, -550, 550, -550, 550, -550, 600, -550, 600, -550, 550, -550, 550, -1700, 600, -1650, 600, -1650, 600, -1650, 600, -1650, 600, -1650, 600, -1650, 600, -1650, 550, -600, 600, -500, 600, -1650, 550, -1750, 550, -1650, 550, -600, 600, -550, 550, -550, 550, -1700, 600, -1650, 550, -550, 600, -550, 600, -550, 600, -1600, 600, -1700, 600, -1600, 600 );

    FF887 cool

    unsigned int irCool[] = {8900, -4500, 600, -550, 550, -550, 550, -550, 600, -550, 600, -550, 600, -500, 600, -500, 600, -550, 600, -1650, 600, -1650, 600, -1650, 600, -1650, 550, -1750, 550, -1650, 550, -1750, 550, -1650, 550, -600, 600, -550, 600, -500, 600, -500, 600, -1700, 600, -500, 600, -500, 600, -550, 600, -1650, 600, -1650, 700, -1600, 550, -1650, 600, -550, 600, -1650, 550, -1700, 600, -1650, 600 };
    FF08F7
    Decoded NEC: FF08F7 (32 bits)
    Raw (68): 8900 -4500 600 -550 550 -550 550 -550 600 -550 600 -550 600 -500 600 -500 600 -550 600 -1650 600 -1650 600 -1650 600 -1650 550 -1750 550 -1650 550 -1750 550 -1650 550 -600 600 -550 600 -500 600 -500 600 -1700 600 -500 600 -500 600 -550 600 -1650 600 -1650 700 -1600 550 -1650 600 -550 600 -1650 550 -1700 600 -1650 600


    45473C1B humidifier
    Unknown encoding: 45473C1B (32 bits)
    Raw (68): 8900 -4500 500 -650 550 -550 550 -550 550 -550 550 -650 550 -550 550 -550 550 -550 600 -1700 600 -1650 550 -1750 500 -1700 550 -1750 550 -1650 550 -1750 500 -1700 550 -600 500 -650 500 -600 550 -550 550 -1750 550 -550 600 -550 550 -600 500 -1700 600 -1700 500 -1700 550 -1750 500 -600 550 -1750 500 -1700 600 -1700 500
    unsigned int irHumidifier[] = {8900, -4500, 500, -650, 550, -550, 550, -550, 550, -550, 550, -650, 550, -550, 550, -550, 550, -550, 600, -1700, 600, -1650, 550, -1750, 500, -1700, 550, -1750, 550, -1650, 550, -1750, 500, -1700, 550, -600, 500, -650, 500, -600, 550, -550, 550, -1750, 550, -550, 600, -550, 550, -600, 500, -1700, 600, -1700, 500, -1700, 550, -1750, 500, -600, 550, -1750, 500, -1700, 600, -1700, 500 };

    FFB847 SwingLeftRight
    Decoded NEC: FFB847 (32 bits)
    Raw (68): 9000 -4450 650 -450 650 -500 600 -500 700 -450 650 -450 700 -400 650 -500 700 -450 650 -1550 700 -1600 650 -1600 650 -1600 650 -1600 700 -1550 650 -1600 700 -1550 650 -1600 700 -450 650 -1600 650 -1600 650 -1600 700 -450 600 -500 650 -500 650 -450 700 -1550 700 -450 650 -450 700 -450 650 -1600 650 -1600 700 -1550 650
    unsigned int irSwingLeftRight[] = {9000, -4450, 650, -450, 650, -500, 600, -500, 700, -450, 650, -450, 700, -400, 650, -500, 700, -450, 650, -1550, 700, -1600, 650, -1600, 650, -1600, 650, -1600, 700, -1550, 650, -1600, 700, -1550, 650, -1600, 700, -450, 650, -1600, 650, -1600, 650, -1600, 700, -450, 600, -500, 650, -500, 650, -450, 700, -1550, 700, -450, 650, -450, 700, -450, 650,-1600, 650, -1600, 700, -1550, 650 };




  */


  int iCount = iFuzzy - 6;
  iShot = iShot + 1;
  Serial.println(iShot);
  Serial.print("Count = "); Serial.print(iCount);
  if (iCount > 0)
  {
    for (int i = 0; i < iCount; i++)
    {
      //need to down temp more T
      irsend.sendRaw(irSignal2, sizeof(irSignal2) / sizeof(irSignal2[0]), khz);
      delay(300);
      irsend.sendRaw(irDown, sizeof(irDown) / sizeof(irDown[0]), 0);
      delay(300);
    }
  }
  else if (iCount < 0)
  {
    iCount = abs(iCount);
    for (int i = 0; i < iCount; i++)
    {
      //need to up temp
      irsend.sendRaw(irSignal1, sizeof(irSignal1) / sizeof(irSignal1[0]), khz);
      delay(300);
      irsend.sendRaw(irUp, sizeof(irUp) / sizeof(irUp[0]), 0);
      delay(300);
    }
  }

}




void funRelay(int i)
{
  switch (i)
  {
    case 1: digitalWrite(Relay1, HIGH);  digitalWrite(Relay2, LOW); digitalWrite(Relay3, LOW); digitalWrite(Relay4, LOW);
      Serial.println("Relay 1 ON"); funAirCooler(1); break;
    case 2: digitalWrite(Relay1, HIGH);  digitalWrite(Relay2, HIGH); digitalWrite(Relay3, LOW); digitalWrite(Relay4, LOW);
      Serial.println("Relay 1,2 ON"); funAirCooler(1); break;
    case 3: digitalWrite(Relay1, HIGH);  digitalWrite(Relay2, HIGH); digitalWrite(Relay3, HIGH); digitalWrite(Relay4, LOW);
      Serial.println("Relay 1,2,3 ON"); funAirCooler(2); break;
    case 4: digitalWrite(Relay1, HIGH);  digitalWrite(Relay2, HIGH); digitalWrite(Relay3, HIGH); digitalWrite(Relay4, HIGH);
      Serial.println("Relay 1,2,3,4 ON"); funAirCooler(3); break;
    default: digitalWrite(Relay1, LOW);  digitalWrite(Relay2, LOW); digitalWrite(Relay3, LOW); digitalWrite(Relay4, LOW);
      Serial.println("ALL Relay OFF"); break;
  }

}


void funAirCooler(int i)
{
  int khz1 = 32;
  unsigned int irPower[]        = {9000, 4450, 550, 550, 600, 550, 600, 550, 550, 550, 550, 550, 600, 550, 600, 550, 550, 550, 550, 1700, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 550, 600, 600, 500, 600, 1650, 550, 1750, 550, 1650, 550, 600, 600, 550, 550, 550, 550, 1700, 600, 1650, 550, 550, 600, 550, 600, 550, 600, 1600, 600, 1700, 600, 1600, 600 };
  unsigned int irCool[]         = {8900, 4500, 600, 550, 550, 550, 550, 550, 600, 550, 600, 550, 600, 500, 600, 500, 600, 550, 600, 1650, 600, 1650, 600, 1650, 600, 1650, 550, 1750, 550, 1650, 550, 1750, 550, 1650, 550, 600, 600, 550, 600, 500, 600, 500, 600, 1700, 600, 500, 600, 500, 600, 550, 600, 1650, 600, 1650, 700, 1600, 550, 1650, 600, 550, 600, 1650, 550, 1700, 600, 1650, 600 };
  signed int irHumidifier[]     = {8900, 4500, 500, 650, 550, 550, 550, 550, 550, 550, 550, 650, 550, 550, 550, 550, 550, 550, 600, 1700, 600, 1650, 550, 1750, 500, 1700, 550, 1750, 550, 1650, 550, 1750, 500, 1700, 550, 600, 500, 650, 500, 600, 550, 550, 550, 1750, 550, 550, 600, 550, 550, 600, 500, 1700, 600, 1700, 500, 1700, 550, 1750, 500, 600, 550, 1750, 500, 1700, 600, 1700, 500 };
  signed int irSwingLeftRight[] = {9000, 4450, 650, 450, 650, 500, 600, 500, 700, 450, 650, 450, 700, 400, 650, 500, 700, 450, 650, 1550, 700, 1600, 650, 1600, 650, 1600, 650, 1600, 700, 1550, 650, 1600, 700, 1550, 650, 1600, 700, 450, 650, 1600, 650, 1600, 650, 1600, 700, 450, 600, 500, 650, 500, 650, 450, 700, 1550, 700, 450, 650, 450, 700, 450, 650, 1600, 650, 1600, 700, 1550, 650 };
  unsigned int  irCool2[67] = {8850, 4550, 550, 550, 600, 550, 550, 550, 550, 600, 550, 550, 600, 550, 550, 550, 600, 550, 550, 1700, 550, 1700, 550, 1700, 550, 1700, 550, 1700, 550, 1700, 650, 1600, 550, 1700, 550, 1700, 550, 600, 550, 550, 550, 600, 550, 1700, 500, 600, 550, 600, 500, 600, 550, 600, 550, 1700, 550, 1700, 550, 1700, 550, 550, 550, 1700, 600, 1650, 550, 1700, 550}; // NEC FF8877


  switch (i)
  {
    case 1: irsend.sendRaw(irCool2, sizeof(irCool2) / sizeof(irCool2[0]), khz1);     Serial.println("Cool signal"); delay(1000); break;
    case 2: irsend.sendRaw(irHumidifier, sizeof(irHumidifier) / sizeof(irHumidifier[0]), khz1);   Serial.println("Humidifier signal");   delay(1000); break;
    case 3: irsend.sendRaw(irSwingLeftRight, sizeof(irSwingLeftRight) / sizeof(irSwingLeftRight[0]), khz1);    Serial.println("SwingLeftRight signal");  delay(1000); break;

  }
}




