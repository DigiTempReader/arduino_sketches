
int i=0;


void setup()
{
//pinMode(9,OUTPUT);
//pinMode(10,OUTPUT);
DDRB = 0xff;
//DigitalWrite(10,HIGH);

}


void loop()
{
  
for(i=0;i<4000;i++)
  {
//    digitalWrite(9,HIGH);
    PORTB = 0xff;
    delayMicroseconds(30);
    //delay(1);
    PORTB = 0x00;
  //  digitalWrite(9,LOW);
    delayMicroseconds(30);
    //delay(1);
    delayMicroseconds(2940);
  }
  
 // delay(3000);
}
