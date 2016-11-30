
#define in1 3
#define in2 4
#define ena 5
void setup() {
  // put your setup code here, to run once:
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

void loop() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(ena, 120);
  delay(3000);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(3000);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(ena, 120);
  delay(3000);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(3000);
  for (int i = 0; i < 255; i++)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(ena, i);
    delay(30);
  }
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(3000);
  for (int i = 255; i > 0; i--)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(ena, i);
    delay(30);
  }


}
