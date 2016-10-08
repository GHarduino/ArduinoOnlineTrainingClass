void setup() {  
  Serial.begin(115200);
  pinMode(6,OUTPUT);
  pinMode(3,INPUT);  
}
void loop() {
  float duration, distance;
  digitalWrite(6,LOW);
  delayMicroseconds(2);
  digitalWrite(6,HIGH);
  delayMicroseconds(10);
  digitalWrite(6,LOW);
  duration = pulseIn(3,HIGH);
  
  distance = (duration/2) /28.57;

  if(distance >= 200 || distance <=0)
  {
        Serial.print("Out of range   ");   
  }
  else{
        Serial.print(distance);
        Serial.println(" cm");
  } 
  delay(100);
}
