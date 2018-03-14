/*
 ESP8266 --> ThingSpeak Channel via MKR1000 Wi-Fi
 
 This sketch sends the Wi-Fi Signal Strength (RSSI) of an ESP8266 to a ThingSpeak
 channel using the ThingSpeak API (https://www.mathworks.com/help/thingspeak).
 
 Requirements:
 
   * ESP8266 Wi-Fi Device
   * Arduino 1.6.9+ IDE
   * Additional Boards URL: http://arduino.esp8266.com/stable/package_esp8266com_index.json
   * Library: esp8266 by ESP8266 Community
 
 ThingSpeak Setup:
 
   * Sign Up for New User Account - https://thingspeak.com/users/sign_up
   * Create a new Channel by selecting Channels, My Channels, and then New Channel
   * Enable one field
   * Note the Channel ID and Write API Key
    
 Setup Wi-Fi:
  * Enter SSID
  * Enter Password
  
 Tutorial: http://nothans.com/measure-wi-fi-signal-levels-with-the-esp8266-and-thingspeak
   
 Created: Feb 1, 2017 by Hans Scharler (http://nothans.com)
*/

#include <ESP8266WiFi.h>

// Wi-Fi Settings
const char* ssid = "awh"; // your wireless network name (SSID)
const char* password = "asdfghjkl"; // your Wi-Fi network password

WiFiClient client;

// ThingSpeak Settings
const int channelID = 215495;
String writeAPIKey = "6LX2PUKIJKBQGTFZ"; // write API key for your ThingSpeak Channel
const char* server = "api.thingspeak.com";
const int postingInterval = 20 * 1000; // post data every 20 seconds

void setup() {

  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
   pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
   pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
   pinMode(D7,OUTPUT);
  pinMode(D8,OUTPUT);
   
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conntcted!!!");
}

void loop() {
  digitalWrite(D1,HIGH);
  delay(100);
  digitalWrite(D2,HIGH);
  delay(100);
  digitalWrite(D3,HIGH);
  delay(100);
  digitalWrite(D4,HIGH);
  delay(100);
  digitalWrite(D5,HIGH);
  delay(100);
  digitalWrite(D6,HIGH);
  delay(100);
  digitalWrite(D7,HIGH);
  delay(100);
  digitalWrite(D8,HIGH);
  delay(100);

  
  digitalWrite(D1,LOW);
  delay(100);
  digitalWrite(D2,LOW);
  delay(100);
  digitalWrite(D3,LOW);
  delay(100);
  digitalWrite(D4,LOW);
  delay(100);
  digitalWrite(D5,LOW);
  delay(100);
  digitalWrite(D6,LOW);
  delay(100);
  digitalWrite(D7,LOW);
  delay(100);
  digitalWrite(D8,LOW);
  delay(100);

  
  if (client.connect(server, 80)) {
    Serial.println("Server Connected!!!");
    // Measure Signal Strength (RSSI) of Wi-Fi connection
    long rssi = WiFi.RSSI();

    // Construct API request body
    String body = "field1=";
           body += String(rssi);
    
    Serial.print("RSSI: ");
    Serial.println(rssi); 

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
