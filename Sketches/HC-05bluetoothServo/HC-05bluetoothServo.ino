// code begins
#include <SoftwareSerial.h> // TX RX software library for bluetooth
#include <Servo.h> // servo library
Servo myservo; // servo name
int bluetoothTx = 9; // bluetooth tx to 10 pin
int bluetoothRx = 8; // bluetooth rx to 11 pin
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
  myservo.attach(9); // attach servo signal wire to pin 9
  //Setup usb serial connection to computer
  Serial.begin(9600);
  //Setup Bluetooth serial connection to android
  bluetooth.begin(9600);
}
void loop()
{
  //Read from bluetooth and write to usb serial
  if (bluetooth.available() > 0 ) // receive number from bluetooth
  {
    int servopos = bluetooth.read(); // save the received number to servopos
    Serial.println(servopos); // serial print servopos current number received from bluetooth
    //myservo.write(servopos); // roate the servo the angle received from the android app
  }
}
