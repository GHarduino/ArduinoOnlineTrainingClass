#include <IRremote.h>

#define ONE 3772784863
#define TWO 3772817503
#define THREE 3772801183
#define FOUR 3772780783
#define FIVE 3772813423
#define SIX 3772797103
#define SEVEN 3772788943
#define EIGHT 3772821583


const int LED1 = 8;
const int LED2 = 9;
const int LED3 = 10;

int RECV_PIN = 2;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() {
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  irrecv.enableIRIn(); // Start the receiver
}


void loop() {

  if (irrecv.decode(&results)) {
    //Serial.println(results.value, HEX);  // to show hex
    Serial.println(results.value);         //to show integer
    irrecv.resume(); // Receive the next value

    switch (results.value)
    {
      case ONE:
        funOne(); break;
      case TWO:
        funTwo(); break;
      case THREE:
        funThree(); break;
      case FOUR:
        funFour(); break;
      case FIVE:
        funFive(); break;
      case SIX:
        funSix(); break;
      case SEVEN:
        funSeven(); break;
      case EIGHT:
        funEight(); break;
 
      default:;
    }
  }
  delay(100);
}
void funOne()
{
  digitalWrite(LED1, HIGH);
}

void funTwo()
{
  digitalWrite(LED2, HIGH);
}

void funThree()
{
  digitalWrite(LED3, HIGH);
}
void funFour()
{
  digitalWrite(LED1, LOW);
}
void funFive()
{
  digitalWrite(LED2, LOW);
}
void funSix()
{
  digitalWrite(LED3, LOW);
}
void funSeven()
{
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
}
void funEight()
{
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
}
