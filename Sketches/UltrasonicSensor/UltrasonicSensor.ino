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
  delayMicroseconds(50);
  digitalWrite(6,LOW);

  duration = pulseIn(3,HIGH);
  //Serial.println("Duration ");
  Serial.println(duration);
  if(duration>2000) duration = 0;
    distance = (duration/2) /29.1;

    if(distance >= 200 || distance <=0){
        Serial.print("Out of range   ");   
        //Serial.println(duration); 
        
    }
    else{
        Serial.print(distance);
        Serial.println(" cm");
    } 
    delay(100);
  
}
