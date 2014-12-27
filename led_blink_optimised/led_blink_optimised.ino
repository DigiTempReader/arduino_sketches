#include <digitalWriteFast.h>
#include <util/delay.h>
const int led = 13;
void setup() 
{                
  pinModeFast(led, OUTPUT);     
}

void loop() 
{
  digitalWriteFast(led, HIGH);   
  _delay_ms(100);
  digitalWriteFast(led, LOW);
  _delay_ms(100);
  
}
