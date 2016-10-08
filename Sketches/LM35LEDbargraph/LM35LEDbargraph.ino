//theorycircuit.com
//temperature sensor (LM35) controlled LED output with buzzer
int tempsensor = 0;
int firstled = 8;
int secondled = 9;
int thirdled = 10;
int fourthled = 11;
int fifthled = 12;
int buzzerpin = 7;
void setup()
{
Serial.begin(9600);
pinMode(firstled,OUTPUT);
pinMode(secondled,OUTPUT);
pinMode(thirdled,OUTPUT);
pinMode(fourthled,OUTPUT);
pinMode(fifthled,OUTPUT);
pinMode(buzzerpin,OUTPUT);
}
void loop()
{
tempsensor=analogRead(0);
if(tempsensor<=129)
{
digitalWrite(firstled,HIGH);
digitalWrite(secondled,LOW);
digitalWrite(thirdled,LOW);
digitalWrite(fourthled,LOW);
digitalWrite(fifthled,LOW);
digitalWrite(buzzerpin,LOW);
}
else if(tempsensor>=130&&tempsensor<155)
{
digitalWrite(firstled,LOW);
digitalWrite(secondled,HIGH);
digitalWrite(thirdled,LOW);
digitalWrite(fourthled,LOW);
digitalWrite(fifthled,LOW);
digitalWrite(buzzerpin,LOW);
}
else if(tempsensor>=155&&tempsensor<165)
{
digitalWrite(firstled,LOW);
digitalWrite(secondled,LOW);
digitalWrite(thirdled,HIGH);
digitalWrite(fourthled,LOW);
digitalWrite(fifthled,LOW);
digitalWrite(buzzerpin,LOW);
}
else if(tempsensor>=165&&tempsensor<180)
{
digitalWrite(firstled,LOW);
digitalWrite(secondled,LOW);
digitalWrite(thirdled,LOW);
digitalWrite(fourthled,HIGH);
digitalWrite(fifthled,LOW);
digitalWrite(buzzerpin,LOW);
}
else if(tempsensor>=180&&tempsensor<200)
{
digitalWrite(firstled,LOW);
digitalWrite(secondled,LOW);
digitalWrite(thirdled,LOW);
digitalWrite(fourthled,LOW);
digitalWrite(fifthled,HIGH);
digitalWrite(buzzerpin,LOW);
}
else if(tempsensor>200)
{
digitalWrite(firstled,HIGH);
digitalWrite(secondled,HIGH);
digitalWrite(thirdled,HIGH);
digitalWrite(fourthled,HIGH);
digitalWrite(fifthled,HIGH);
digitalWrite(buzzerpin,HIGH);
}
Serial.println(tempsensor);
delay(150);
}
LM35 Pinout
