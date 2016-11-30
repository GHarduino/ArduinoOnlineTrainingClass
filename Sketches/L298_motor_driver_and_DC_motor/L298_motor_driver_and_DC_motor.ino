
int const In1=8;
int const In2=9;
int const In3=10;
int const In4=11;
int const EnA=3;
int const EnB=5;
int const Speed=255;

void setup() {

  pinMode(In1,OUTPUT);
  pinMode(In2,OUTPUT);
  pinMode(In3,OUTPUT);
  pinMode(In4,OUTPUT);
  pinMode(EnA,OUTPUT);
  pinMode(EnB,OUTPUT);
  
}

void loop() {
  ForwardA(Speed);
  delay(1000);
  StopA();
  delay(1000);
  BackwardA(Speed);
  delay(1000);
  StopA();
  delay(1000);

  ForwardB(Speed);
  delay(1000);
  StopB();
  delay(1000);
  BackwardB(Speed);
  delay(1000);
  StopB();
  delay(1000);

  ForwardA(Speed);
  ForwardB(Speed);
  delay(1000);
  StopA();
  StopB();
  delay(1000);
  BackwardA(Speed);
  BackwardB(Speed);
  delay(1000);
  StopA();
  StopB();
  delay(1000);
  
  

}


void ForwardA(int s)
{
  digitalWrite(In1,HIGH);
  digitalWrite(In2,LOW);
  analogWrite(EnA,s);
}
void BackwardA(int s)
{
  digitalWrite(In1,LOW);
  digitalWrite(In2,HIGH);
  analogWrite(EnA,s);
}
void StopA()
{
  analogWrite(EnA,0);
}
void ForwardB(int s)
{
  digitalWrite(In3,HIGH);
  digitalWrite(In4,LOW);
  analogWrite(EnB,s);
}
void BackwardB(int s)
{
  digitalWrite(In3,LOW);
  digitalWrite(In4,HIGH);
  analogWrite(EnB,s);
}
void StopB()
{
  analogWrite(EnB,0);
}

