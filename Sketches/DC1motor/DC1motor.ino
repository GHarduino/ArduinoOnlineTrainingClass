/*
   MotorKnob

   A stepper motor follows the turns of a potentiometer
   (or other sensor) on analog input 0.

   http://www.arduino.cc/en/Reference/Stepper
   This example code is in the public domain.
*/
#define in1 3
#define in2 4
#define ena 10
#define in3 5
#define in4 6
#define enb 11

#define ir 2



void setup() {
  // set the speed of the motor to 30 RPMs
  pinMode(in1, OUTPUT); //1,1 0,0    stop
  pinMode(in2, OUTPUT); //1,0 or 0,1 dir
  pinMode(in3, OUTPUT); //1,1 0,0    stop
  pinMode(in4, OUTPUT); //1,0 or 0,1 dir
  carForward(125);
  delay(1000);
  carStop();
  delay(1000);
  carBackward(125);
  delay(1000);
  carStop();
  carForwardLeft(50);
  delay(1000);
  carBackward(125);
  delay(1000);
  carForwardRight(50);
  delay(1000);
  carForward(125);
  delay(1000);
  carStop;
}

void loop() {


}


void carForward(int speed)
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(ena, speed);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ena, speed);
}
void carBackward(int speed)
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(ena, speed);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ena, speed);
}
void carStop()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void carForwardLeft(int speed)
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(ena, speed);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ena, speed);
}
void carForwardRight(int speed)
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(ena, speed);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ena, speed);
}

