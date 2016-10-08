 
/* 
Arduino Based Digital Thermometer
Tested By Amol Shah from DNA Technology : http://www.dnatechindia.com/
For https://makeelectronicprojects.blogspot.in

To wire your LCD screen to your Arduino, connect the following pins: 
LCD Pin 6 to digital pin 12 
LCD Pin 4 to digital pin 11 
LCD Pin 11 to digital pin 5 
LCD Pin 12 to digital pin 4 
LCD Pin 13 to digital pin 3 
LCD Pin 14 to digital pin 2 
Additionally, wire a 10K pot to +5V and GND, with it's wiper (output) to LCD screens VO pin (pin3). 

 
 */
#include<LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);
const int inPin = 0;
void setup()
{
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("  Thermometer");  
}
void loop()
{
  int value = analogRead(inPin);
  float millivolts = (value / 1024.0) * 5000;
  float celsius = millivolts / 10;

  lcd.setCursor(0,1);
  lcd.print(celsius);
  lcd.write(0xdf);
  lcd.print("C  ");
  lcd.print((celsius * 9)/5 + 32);
  lcd.write(0xdf);
  lcd.print("F");
  delay(1000);
}
