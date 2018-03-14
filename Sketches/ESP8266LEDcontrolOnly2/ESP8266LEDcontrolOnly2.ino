#include <Arduino.h>
#include<ESP8266WiFi.h>
#include<ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti WiFiMulti;
//WiFi Definitions
const char WiFiSSID[] = "es";
const char WiFiPSK[] = "asdfghjkl";

//pin definition



const int LED_PIN = D2; //D2
const int ANALOG_PIN = A0;
const int DIGITAL_PIN = D2;

WiFiServer server(80);

String IPaddress;
int lightval0=0;
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
  delay(4000);
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
  pinMode(16,OUTPUT);
  digitalWrite(16,LOW);
  pinMode(5,OUTPUT);
  digitalWrite(5,LOW);
  pinMode(0,OUTPUT);
  digitalWrite(0,LOW);
  pinMode(2,OUTPUT);
  digitalWrite(2,LOW);
  pinMode(14,OUTPUT);
  digitalWrite(14,LOW);
  pinMode(12,OUTPUT);
  digitalWrite(12,LOW);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  pinMode(16,OUTPUT);
  digitalWrite(16,LOW);
  
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

  //light= String(analogRead(ANALOG_PIN));
  //Serial.print("light : ");
  //Serial.println(light);
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
  int val0 = -1; //we'll use val0 to keep track of both read/set and val0ue if set
  int val1 = -1; //we'll use val0 to keep track of both read/set and val0ue if set
  int val2 = -1; //we'll use val0 to keep track of both read/set and val0ue if set
  if (req.indexOf("/led0/0")!=-1)
  {
    val0 =0; //led off
    Serial.println(req.indexOf("/led0/0"));    
  }
  else if(req.indexOf("/led0/1")!=-1)
  {
    val0 =1; //led on
    Serial.println(req.indexOf("/led0/1"));
  }
  
  else if (req.indexOf("/led1/0")!=-1)
  {
    val1 =0; //led off
    Serial.println(req.indexOf("/led1/0"));    
  }
  else if(req.indexOf("/led1/1")!=-1)
  {
    val1 =1; //led on
    Serial.println(req.indexOf("/led1/1"));
  }
  
  else if (req.indexOf("/led2/0")!=-1)
  {
    val2 =0; //led off
    Serial.println(req.indexOf("/led2/0"));    
  }
  else if(req.indexOf("/led2/1")!=-1)
  {
    val2 =1; //led on
    Serial.println(req.indexOf("/led2/1"));
  }
  else if(req.indexOf("/read")!=-1)
  {
    val0 =-2;//will print pin reads
    lightval0=analogRead(ANALOG_PIN);
  }
  //Otherwise request will be inval0id. we'll say as much in html
  else if(req.indexOf("/ip")!=-1)
  {
     val0 = -3; //will print ip address
     Serial.println("IP address: ");    
     Serial.println(ipToString());
  }
  //Set GPIO5 according to the request
  if(val0>=0)
  {
    digitalWrite(D2,val0);
  }
   if(val1>=0)
  {
    digitalWrite(D0,val1);
  }
   if(val2>=0)
  {
    digitalWrite(D1,val2);
  }
  client.flush();

  // Prepare the response. Start with the common header
  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  // If we're setting the LED, print out a message saying we did
  if(val0 >=0)
  {
    s += "LED is now ";
    s +=(val0)?"on":"off";
    Serial.println(s);
  }
  else if(val0 == -2)
  {
    //If we're reading pins, print out those val0ues;
    s += "Analog Pin = ";
    s += String(analogRead(ANALOG_PIN));
    s += "<br>";
    s += "Digital Pin 12 = ";
    s += String(digitalRead(DIGITAL_PIN));
    s += "<br>";
    s += "IP Address = ";
    s += ipToString();
    s += "<br>"; 
   //  s += "Light val0ue = ";
   // s += String(lightval0);
   // s += "<br>"; 

    Serial.println("Reading val0ues");
    Serial.print("LED status : ");
    Serial.println(digitalRead(DIGITAL_PIN));
   
  
  }
  else if(val0 == -3)
  {
    s += "IP Address = ";
    s += ipToString();
    s += "<br>";  

    Serial.print("IP address : ");
    Serial.println(ipToString());
  
  }
  else
  {
    s +=req;
    s +="\n\n";
    s +="Inval0id Request.<br> Try /led/1 or /led/0 or /read.";

    Serial.print("Inval0id request!!! ");
  }

  s+="</html\n";

  //Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disconnected");
  // the client will actually be disconnected
  //when the function returns and client object is destroyed  
}


