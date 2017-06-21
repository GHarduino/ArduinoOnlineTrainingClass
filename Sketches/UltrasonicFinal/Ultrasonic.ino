int trigPin = 6;
int echoPin =  3;
int ledPin = 7;
int buzzer = 2;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  float duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  //Serial.print(duration);
  //Serial.print(" - ");
  distance = (duration / 2) / 28.57;
  if ((distance >= 200) ||  (distance <= 0))
  {
    Serial.println("out of range ");
  }
  else {
    Serial.println(distance);
  }
  if (distance <= 8 && distance >= 2)
  {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzer, HIGH);
  }
  else
  {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzer, LOW);
  }

  delay(200);
}


