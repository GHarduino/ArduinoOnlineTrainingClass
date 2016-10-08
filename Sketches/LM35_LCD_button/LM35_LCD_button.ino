/*
 * http://www.instructables.com/id/Arduino-and-LM35-Temperature-Measurement/
 Demonstrates the use ADC and 16x2 LCD display

 The Arduino circuit connection for LCD:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 6
 * LCD D4 pin digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 *
 *  LM35 is connected with A0 ADC pin
 * Push button is connected with D8 analog pin

 Name:- M.Pugazhendi
 Date:-  08thJul2016
 Version:- V0.1
 e-mail:- muthuswamy.pugazhendi@gmail.com
 */

// include the library code:
#include  <LiquidCrystal.h>

int analogPin1 = 0;     // LM35 temperature sensor connected to analog pin 2
int val = 0;           // variable to store the value read

//initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7,6,5,4,3,2);

// this constant won't change:
const int  buttonPin = 8;    // the pin that the pushbutton is attached to

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

void setup() 
{
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  analogReference(INTERNAL);
  
  // Print a message to the LCD
  lcd.print("Start");
 
}

void loop() 
{

  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) 
  {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) 
    {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter++;
      
      // (note: line 0 is the first row, since counting begins with 0):
      lcd.setCursor(0, 0);
      lcd.print("                "); //Print blanks to clear the row
      lcd.setCursor(0, 0);
      switch(buttonPushCounter)
      {
        case 1:
          lcd.print("Celsius");
          break;
        case 2:
          lcd.print("Farenheit");
          break;
        case 3:
          lcd.print("Kelvin");
          break;
        case 4:
          lcd.print("Rankine");
          break;                              
        default:
         buttonPushCounter = 1;
         lcd.print("Celsius");
        break;      
      }            
    } 
    
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;

  // Resets the buttonPushCounter to zero once every four button pushes.    
  //if (buttonPushCounter  == 5) 
  //{
  //  buttonPushCounter = 0;
  //}

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(12, 1);
  lcd.print("     "); //Print blanks to clear the row
  lcd.setCursor(0, 1);
  
  val = analogRead(analogPin1);    // read the LM35 sensor input pin

  float converted = fmap(val, 0, 1023, 0.0, 110.0);
 
  
      switch(buttonPushCounter)
      {
        case 1:
           //Celsius
            lcd.print("TEMP = ");
            lcd.print(converted);             // ADC value
            lcd.print("\337C");
          break;
        case 2:
            //Fahrenheit
            //T(°F) = T(°C) × 9/5 + 32
            converted = ( converted * 1.8 ) + 32;          
            lcd.print("TEMP = ");
            lcd.print(converted);             // ADC value
            lcd.print("\337F");
          break;
        case 3:
          //Kelvin
          //T(K) = T(°C) + 273.15          
          converted = converted + 273.15;          
          lcd.print("TEMP = ");
          lcd.print(converted);             // ADC value
          lcd.print("K");
          break;
        case 4:
          //Rankine
          //T(°R) = (T(°C) + 273.15) × 9/5          
          converted = converted + 273.15;
          converted = (converted * 1.8);          
          lcd.print("TEMP = ");
          lcd.print(converted);             // ADC value
          lcd.print("\337R");
          break;                              
        default:
         break;      
      }

  //One second delay between readings                  
  delay(1000);       
}

//Float interpolation function, for mapping the ADC reading
float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
