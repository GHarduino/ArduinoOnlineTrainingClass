/*
  ESP8266 --> ThingSpeak Channel via MKR1000 Wi-Fi

  This sketch sends the Wi-Fi Signal Strength (RSSI) of an ESP8266 to a ThingSpeak
  channel using the ThingSpeak API (https://www.mathworks.com/help/thingspeak).

  Requirements:

     ESP8266 Wi-Fi Device
     Arduino 1.6.9+ IDE
     Additional Boards URL: http://arduino.esp8266.com/stable/package_esp8266com_index.json
     Library: esp8266 by ESP8266 Community

  ThingSpeak Setup:

     Sign Up for New User Account - https://thingspeak.com/users/sign_up
     Create a new Channel by selecting Channels, My Channels, and then New Channel
     Enable one field
     Note the Channel ID and Write API Key

  Setup Wi-Fi:
    Enter SSID
    Enter Password

  Tutorial: http://nothans.com/measure-wi-fi-signal-levels-with-the-esp8266-and-thingspeak

  Created: Feb 1, 2017 by Hans Scharler (http://nothans.com)
*/

#include <ESP8266WiFi.h>
#include "PietteTech_DHT.h"

// system defines
#define DHTTYPE  DHT22           // Sensor type DHT11/21/22/AM2301/AM2302
#define DHTPIN   2              // Digital pin for communications

#define REPORT_INTERVAL 5000 // in msec must > 2000

// to check dht
unsigned long startMills;
float t, h, d;
int acquireresult;
int acquirestatus;

//declaration
void dht_wrapper(); // must be declared before the lib initialization

// Lib instantiate
PietteTech_DHT DHT(DHTPIN, DHTTYPE, dht_wrapper);

// globals
bool bDHTstarted;       // flag to indicate we started acquisition

// This wrapper is in charge of calling
// must be defined like this for the lib work
void dht_wrapper() {
  DHT.isrCallback();
}


// Wi-Fi Settings
const char* ssid = "awh"; // your wireless network name (SSID)
const char* password = "asdfghjkl"; // your Wi-Fi network password

WiFiClient client;

// ThingSpeak Settings
const int channelID = 316734;
String writeAPIKey = "WK254MP0GR4ZKNM0"; // write API key for your ThingSpeak Channel
const char* server = "api.thingspeak.com";
const int postingInterval = 20 * 1000; // post data every 20 seconds

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conntcted!!!");
  Serial.begin(115200);
  startMills = millis();
  Serial.begin(115200);

  /*
    while (!Serial) {
    yield(); // wait for serial port to connect.
    }
  */

  Serial.println("");
  Serial.println("DHT Example program using DHT.acquire and DHT.acquireAndWait");
  Serial.println("");

  // delay 2 sec before start acquire
  while ( (millis() - startMills) < 2000 ) {
    yield();
  }

  // blocking method
  acquirestatus = 0;
  acquireresult = DHT.acquireAndWait(1000);
  if ( acquireresult == 0 ) {
    t = DHT.getCelsius();
    h = DHT.getHumidity();
    d = DHT.getDewPoint();
  } else {
    t = h = d = 0;
  }
}

void loop() {
  if (client.connect(server, 80)) {
    Serial.println("Server Connected!!!");
    // Measure Signal Strength (RSSI) of Wi-Fi connection
    long rssi = WiFi.RSSI();
    
    // READ DATA
     if (bDHTstarted) {
    acquirestatus = DHT.acquiring();
    if (!acquirestatus) {
      acquireresult = DHT.getStatus();
      if ( acquireresult == 0 ) {
        t = DHT.getCelsius();
        h = DHT.getHumidity();
        d = DHT.getDewPoint();
      }
      bDHTstarted = false;
    }
  }

  if ((millis() - startMills) > REPORT_INTERVAL) {
    if ( acquireresult == 0 ) {
      Serial.println("");

      Serial.print("Humidity (%): ");
      Serial.println(h);

      Serial.print("Temperature (oC): ");
      Serial.println(t);

      Serial.print("Dew Point (oC): ");
      Serial.println(d);

    } else {
      Serial.println("Is dht22 connected");
    }
    startMills = millis();

    // to remove lock
    if (acquirestatus == 1) {
      DHT.reset();
    }

    if (!bDHTstarted) {
      // non blocking method
      DHT.acquire();
      bDHTstarted = true;
    }
  }

    // Construct API request body
    String body = "field1=";
    body += String(t);



    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + writeAPIKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(body.length());
    client.print("\n\n");
    client.print(body);
    client.print("\n\n");

  }
  else
  {
    Serial.println("Cannot conntcted!!!");
  }
  client.stop();

  // wait and then post again
  delay(postingInterval);
}
