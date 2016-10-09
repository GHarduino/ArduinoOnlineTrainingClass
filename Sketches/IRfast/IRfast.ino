#include <IRremote.h>
#include <IRremoteTools.h>
#include <ArduinoRobot.h>
#include <Wire.h>
int RECV_PIN = 2;     //IR Received Pin

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);

  irrecv.enableIRIn();
}

void loop() {
  // put your main code here, to run repeatedly:

}
