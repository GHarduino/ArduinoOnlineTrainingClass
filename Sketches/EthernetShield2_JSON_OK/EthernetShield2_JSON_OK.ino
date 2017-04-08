/*
  Web client

  This sketch connects to a website (http://192.168.1.100)
  using an Arduino Wiznet Ethernet shield.

  Circuit:
   Ethernet shield attached to pins 10, 11, 12, 13

  created 18 Dec 2009
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe, based on work by Adrian McEwen

  modified 8 Apr 2017
  by Dr. Aung Win Htut (Green Hackers) 
  Add simple JSON parsing

*/

#include <SPI.h>
#include <Ethernet.h>


// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {
  0x90, 0xA2, 0xDA, 0x0F, 0x3A, 0xDC
};
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
IPAddress server(192, 168, 1, 100); // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 1, 105);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:

    client.println("GET /GHinsertdata.php?l1=222&t1=2222&c1=222&h1=222 HTTP/1.1");
    client.println("Host: 192.168.1.100");
    client.println("Connection: close");
    client.println();
  }
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop()
{
  String response = "";
  bool begin = false;
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available() || !begin)
  {
    char c = client.read(); //read one char 
    Serial.print(c);
    if (c == '{')           //if start then begin 
    {
      begin = true;
    }

    if (c == '}')           //if end then exit
    {
      break;
    }

    if (begin && c != '{')   //if begin record all char except { 
    {
      response += (c);
    }
    delay(1);  //need a little delay to process
  }
  Serial.println();
  Serial.println();
  Serial.println(response);
  Serial.println();
  delay(1000);
  int start = response.indexOf("Success\":\"") + 11;  //find Success: location index
  int end = start + 1;
  String nodeId = response.substring(start, end);     //extract one character after start location
  Serial.println(nodeId);
  delay(5000);
  const char* command = "1";
  if (nodeId == "1")              //determine command here
  {

    Serial.println("One");        //do something according to command
    delay(10000);

  }


  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
}
