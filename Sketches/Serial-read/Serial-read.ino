/* Simple Serial ECHO script : Written by ScottC 03/07/2012 */

/* Use a variable called byteRead to temporarily store
   the data coming from the computer */
#define led1 13
#define led2 12
#define led3 11



byte byteRead;

void setup() {                
// Turn the Serial Protocol ON
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  Serial.begin(9600);
}

void loop() {
   /*  check if data has been sent from the computer: */
  if (Serial.available()) {
    /* read the most recent byte */
    byteRead = Serial.read();
    /*ECHO the value that was read, back to the serial port. */
    Serial.write(byteRead);
    Serial.write("---");
    switch(byteRead)
    {
      case '1': digitalWrite(led1,HIGH);break;
      case '2': digitalWrite(led2,HIGH);break;
      case '3': digitalWrite(led3,HIGH);break;
      case '4': digitalWrite(led1,LOW);break;
      case '5': digitalWrite(led2,LOW);break;
      case '6': digitalWrite(led3,LOW);break;
      
    }
    
  }
}
