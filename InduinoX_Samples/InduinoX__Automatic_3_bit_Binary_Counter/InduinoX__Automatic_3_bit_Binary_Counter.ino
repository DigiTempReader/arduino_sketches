/* 

This sketch automatically increases a 3 bit number every second
and shows the output on 3 LEDs 

*/


void setup()
{
  pinMode(11,OUTPUT);     // declare LED pins as output pins
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
}

void loop()
{
  for(int i=0;i<8;i++)    // increment automatically from 0 to 7
  {
    int a=i%2;            // calculate LSB 
    int b=i/2 %2;         // calculate middle bit
    int c=i/4 %2;         // calculate MSB 
    
    digitalWrite(11,c);   // write MSB
    digitalWrite(12,b);   // write middle bit
    digitalWrite(13,a);   // write LSB
    delay(1000);          // wait for a second
  }
}
