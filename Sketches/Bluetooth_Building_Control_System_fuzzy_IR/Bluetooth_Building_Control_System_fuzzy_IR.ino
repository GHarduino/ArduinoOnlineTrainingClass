/*
   2017 05 10  update sensor reading time tuning
   temperature and humidity min and max limit checking
   by Dr. Aung Win Htut
*/
#include<SoftwareSerial.h>
#include <dht.h>
#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); //16*4
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); //20*4
#define DHT22_PIN 4
#define ldr A0
#define MQ2 A1
#define IRtransmitter 3
#define IRreceiver 2
#define Buzzer 11
#define led1 8
#define led2 9
#define led3 10
#define maxgas 200
#define mingas 20


static int sgas = 0;
static int stemperature = 3; // 1-very cold <10  2-cold <20  3-normal 20-30 4-hot 30-35 5-very hot >35
static int shumidity = 3; //  1-very humid >60  2-humid 50-60 3-normal 40-50 4-dry 40-30 5-very dry <30
static int tflag[5] = {0, 0, 0, 0, 0}; //flag =3 trigger
static int hflag[5] = {0, 0, 0, 0, 0}; //flag =3 trigger


dht DHT;
SoftwareSerial BlueTooth(6, 7);       //TXD11  RXD12
int status = 1;
int show = 0;
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


void setup() {
  Serial.begin(9600);
  lcd.begin(20, 4);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Weather Station");
  lcd.setCursor(0, 1);
  lcd.print("Welcome!");
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(Buzzer, OUTPUT);

  Serial.println("Goodnight moon!");
  BlueTooth.begin(9600);
  delay(500);
}


void loop() {
  Serial.println("Loop Started");
  funReadSensor();
  delay(1000);

  if (BlueTooth.available()) {
    Serial.write(BlueTooth.read());
  }
  if (Serial.available() > 0)
  {
    int incomingByte = Serial.read();

  }
}

void funReadSensor()
{
  float temp = 0;
  float temp1;
  float light;
  float humidity;
  float gas;



  //Serial.print("Reading Temp");
  //temp = analogRead(lm35);
  //temp = temp * 0.48828125;

  light = analogRead(ldr);
  gas = analogRead(MQ2);

  if ((gas > mingas) && (gas < maxgas))
  {
    sgas = gas;
  }

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



  Serial.print("Light");
  Serial.print(",\t");
  Serial.print(",\t");
  Serial.print("GAS");
  Serial.print(",\t");
  Serial.print("Temp(DHT22)");
  Serial.print(",\t");
  Serial.println("Humidity");
  //Serial.print(",\t");
  //Serial.println("CO");
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
  //Serial.print(",\t");
  //Serial.print(",\t");
  //Serial.println(co);
  Serial.println("");

  int L = light;
  int T = temp;
  int T1 = temp1;
  int H = humidity;
  int G = sgas;





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
      funShowResult();
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
      funShowResult();
    }
  }
  else if ((T1 >= 20) && (T1 < 30))
  {
    tflag[0] = 0;
    tflag[1] = 0;
    tflag[3] = 0;
    tflag[4] = 0;

    tflag[2]++;
    if (tflag[2] == 3)
    {
      stemperature = 3;
      funShowResult();
    }
  }
  else if ((T1 >= 30) && (T1 <= 35))
  {
    tflag[0] = 0;
    tflag[1] = 0;
    tflag[2] = 0;
    tflag[4] = 0;

    tflag[3]++;
    if (tflag[3] == 3)
    {
      stemperature = 4;
      funShowResult();
    }
  }
  else if (T1 > 35)
  {
    tflag[0] = 0;
    tflag[1] = 0;
    tflag[2] = 0;
    tflag[3] = 0;

    tflag[4]++;
    if (tflag[4] == 3)
    {
      stemperature = 5;
      funShowResult();
    }
  }


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
      funShowResult();
    }
  }
  else if ((H >= 50) && (H < 60))
  {
    hflag[0] = 0;
    hflag[2] = 0;
    hflag[3] = 0;
    hflag[4] = 0;

    hflag[1]++;
    if (hflag[1] == 3)
    {
      shumidity = 2;
      funShowResult();
    }
  }
  else if ((H >= 40) && (H < 50))
  {
    hflag[0] = 0;
    hflag[1] = 0;
    hflag[3] = 0;
    hflag[4] = 0;

    hflag[2]++;
    if (hflag[2] == 3)
    {
      shumidity = 3;
      funShowResult();
    }
  }
  else if ((H >= 30) && (H <= 40))
  {
    hflag[0] = 0;
    hflag[1] = 0;
    hflag[2] = 0;
    hflag[4] = 0;

    hflag[3]++;
    if (hflag[3] == 3)
    {
      shumidity = 4;
      funShowResult();
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
      funShowResult();
    }
  }



  if (L > 400)
  {
    digitalWrite(led1, LOW);
  }
  else
  {
    funBuzzerLed();
  }

  String l, t, t1, h, g;
  String st,sh;
  //change integer to string
  //to send by serial
  l = String(L);
  t = String(T);
  t1 = String(T1);
  h = String(H);
  g = String(G);
  st = String(stemperature);
  sh = String(shumidity);

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

  BlueTooth.println(t1 + '@' + t1 + '@' + h + '@' + l + '@' + g + '@' + st + '@' + sh );
  //Serial.println(l + '@' + g + '@' + t1 + '@' + h );
  Serial.println(t1 + '@' + h + '@' + l + '@' + g );

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp ");
  lcd.print(t1);
  lcd.setCursor(0, 1);
  lcd.print("Humidity  ");
  lcd.print(h);
  lcd.setCursor(0, 2);
  lcd.print("Light  ");
  lcd.print(l);
  lcd.setCursor(0, 3);
  lcd.print("GAS  ");
  lcd.print(g);
}



void funShowResult()
{
  lcd.clear();
  switch (stemperature)
  {
    case 1: lcd.setCursor(0, 0); lcd.print("Temperature is Very Cold"); lcd.setCursor(0, 1); lcd.print("Fuzzy 1"); break;
    case 2: lcd.setCursor(0, 0); lcd.print("Temperature is Cold"); lcd.setCursor(0, 1); lcd.print("Fuzzy 2"); break; break;
    case 3: lcd.setCursor(0, 0); lcd.print("Temperature is Normal"); lcd.setCursor(0, 1); lcd.print("Fuzzy 3"); break; break;
    case 4: lcd.setCursor(0, 0); lcd.print("Temperature is Hot"); lcd.setCursor(0, 1); lcd.print("Fuzzy 4"); break; break;
    case 5: lcd.setCursor(0, 0); lcd.print("Temperature is Very Hot"); lcd.setCursor(0, 1); lcd.print("Fuzzy 5"); break; break;
  }
  switch (shumidity)
  {
    case 1: lcd.setCursor(0, 2); lcd.print("Humidity is Very Humid"); lcd.setCursor(0, 3); lcd.print("Fuzzy 1"); break;
    case 2: lcd.setCursor(0, 2); lcd.print("Humidity is Humid"); lcd.setCursor(0, 3); lcd.print("Fuzzy 2"); break; break;
    case 3: lcd.setCursor(0, 2); lcd.print("Humidity is Normal"); lcd.setCursor(0, 3); lcd.print("Fuzzy 3"); break; break;
    case 4: lcd.setCursor(0, 2); lcd.print("Humidity is Dry"); lcd.setCursor(0, 3); lcd.print("Fuzzy 4"); break; break;
    case 5: lcd.setCursor(0, 2); lcd.print("Humidity is Very Dry"); lcd.setCursor(0, 3); lcd.print("Fuzzy 5"); break; break;
  }
  funBuzzerLed();
  delay(5000);

}

void funBuzzerLed()
{
  digitalWrite(led1, HIGH);
  digitalWrite(Buzzer, HIGH);
  delay(1000);
  digitalWrite(Buzzer, LOW);
  delay(100);
}

