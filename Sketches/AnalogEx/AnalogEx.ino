int PWMpin = 6;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PWMpin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<255;i++)
  {
    analogWrite(PWMpin,i);
    Serial.print("Analog 0: ");
    int analogReading = analogRead(A0);
    Serial.println(analogReading);
    delay(1000);
  }
  
}
