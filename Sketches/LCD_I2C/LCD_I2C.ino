
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
//int inputpin = A1;
int i = 0;
void setup()
{
  Serial.begin(9600);  // Used to type in characters
  pinMode(13, OUTPUT);
  lcd.begin(20, 4);  
  lcd.backlight();
  lcd.setCursor(0, 0); //Start at character 4 on line 0
  lcd.print("Hello, world!");
  delay(1000);
}


void loop()
{

 

}



