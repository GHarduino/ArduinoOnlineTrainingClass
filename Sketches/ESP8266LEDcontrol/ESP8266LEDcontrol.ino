#include <Arduino.h>
#include<ESP8266WiFi.h>
#include<ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti WiFiMulti;
//WiFi Definitions
const char WiFiSSID[] = "es";
const char WiFiPSK[] = "asdfghjkl";

const int LED_PIN = 7;
const int ANALOG_PIN = A0;
const int DIGITAL_PIN = 7;

WiFiServer server(80);

String IPaddress;
int lightVal=0;
String light;

void connectWiFi()
{
  byte ledStatus = LOW;
  Serial.println();
  Serial.println("Connecting to: " +String(WiFiSSID));
  // Set WiFi mode to station (as opposed to ap or ap_sta)
  WiFi.mode(WIFI_STA);

  //WIFI.begin([ssid],[passkey]) initiates a WIFI connection to the stated
  //[ssid], using the [passkey] as a WPA, WPA2, or WEP passphrase.
  WiFi.begin(WiFiSSID,WiFiPSK);

  //USE the wifi.status() function to check if esp connected to wifi
  while(WiFi.status() != WL_CONNECTED)
  {
    //Blink led
    digitalWrite(LED_PIN,ledStatus);// blink
    ledStatus = (ledStatus == HIGH)? LOW : HIGH;
    //Delay esp to perform critical tasks
    //defined outside the sketch. setup, maintaining, a wifi
    delay(100);
    //Potentially infinite loops are generally dangerous.
    //add delays -- allowing the processor to perform other tasks 
    //wherever possible
  }
  Serial.println("Wifi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(LED_PIN,LOW);
  delay(2000);
  
}

void setupMDNS()
{
  //call mdns.begin(<domian> to set up mdns to point to 
  // <domain>.local
  if(!MDNS.begin("thing"))
  {
    Serial.println("Error setting up MDNS responder!");
    while(1)
    {
      delay(1000);
    }
  }
  Serial.println("mDns responder started");
}

void  initHardWare()
{
  Serial.begin(115200);
  pinMode(DIGITAL_PIN,INPUT_PULLUP);
  pinMode(LED_PIN,OUTPUT);
  digitalWrite(LED_PIN,LOW);
  //Dont need to set analog_pin as input
  
}

String ipToString(){
  String  MyIp;
  MyIp =  String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(WiFi.localIP()[3]);
  return MyIp;
} 
//- See more at: http://www.esp8266.com/viewtopic.php?p=25466#sthash.r0CdIeR0.dpuf


void setup() {
  initHardWare();
  connectWiFi();
  server.begin();
  setupMDNS();
  delay(1000);
}

void loop() {

  light= String(analogRead(ANALOG_PIN));
  Serial.print("light : ");
  Serial.println(light);
  //delay(50);
  
  //Check if a client has connected
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

  //Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  //Match the request
  int val = -1; //we'll use val to keep track of both read/set and value if set
  if (req.indexOf("/led/0")!=-1)
  {
    val =0; //led off
    Serial.println(req.indexOf("/led/0"));
  }
  else if(req.indexOf("/led/1")!=-1)
  {
    val =1; //led on
    Serial.println(req.indexOf("/led/1"));
  }
  else if(req.indexOf("/read")!=-1)
  {
    val =-2;//will print pin reads
    lightVal=analogRead(ANALOG_PIN);
  }
  //Otherwise request will be invalid. we'll say as much in html
  else if(req.indexOf("/ip")!=-1)
  {
     val = -3; //will print ip address
     Serial.println("IP address: ");    
     Serial.println(ipToString());
  }
  //Set GPIO5 according to the request
  if(val>=0)
  {
    digitalWrite(LED_PIN,val);
  }
  client.flush();

  // Prepare the response. Start with the common header
  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  // If we're setting the LED, print out a message saying we did
  if(val >=0)
  {
    s += "LED is now ";
    s +=(val)?"on":"off";
  }
  else if(val == -2)
  {
    //If we're reading pins, print out those values;
    s += "Analog Pin = ";
    s += String(analogRead(ANALOG_PIN));
    s += "<br>";
    s += "Digital Pin 12 = ";
    s += String(digitalRead(DIGITAL_PIN));
    s += "<br>";
    s += "IP Address = ";
    s += ipToString();
    s += "<br>"; 
     s += "Light Value = ";
    s += String(lightVal);
    s += "<br>"; 
  
  }
  else if(val == -3)
  {
    s += "IP Address = ";
    s += ipToString();
    s += "<br>";  
  
  }
  else
  {
    s +=req;
    s +="\n\n";
    s +="Invalid Request.<br> Try /led/1 or /led/0 or /read.";
  }

  s+="</html\n";

  //Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disconnected");
  // the client will actually be disconnected
  //when the function returns and client object is destroyed  
}


