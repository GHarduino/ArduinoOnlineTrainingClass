
#include <Servo.h>  
#define servoPin 9
Servo sv1;
void setup() {
  // put your setup code here, to run once:
  sv1.attach(servoPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<180;i++)
  {
      sv1.write(i);
      delay(10);
  }
  for(int i=180;i>0;i--)
  {
      sv1.write(i);
      delay(10);
  }

}
