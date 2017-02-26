void setup() {
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);

}

void loop() {
  
  digitalWrite(3, HIGH);
  delay(2000);
  digitalWrite(3, LOW);
  
  digitalWrite(4, HIGH);
  delay(2000);
  digitalWrite(4, LOW);
  
  digitalWrite(5, HIGH);
  delay(2000);
  digitalWrite(5, LOW);

}
