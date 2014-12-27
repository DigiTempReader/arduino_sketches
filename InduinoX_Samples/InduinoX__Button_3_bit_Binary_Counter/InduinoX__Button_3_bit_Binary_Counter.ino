/* 

This sketch increases a 3 bit number every time a button is pressed by the user and shows the output on 3 LEDs 

*/

int i = 0;

void setup()
{
  pinMode(11,OUTPUT);     // declare LED pins as output pins
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  
  pinMode(7,INPUT);// Declare the 7th pin as a input pin. We will use the button on the 7th pin
  digitalWrite(7,HIGH);
}

void loop()
{
  if(digitalRead(7)==0)   // if the button is pressed
  {
    if(i<7)               // if counter value is less than 7 or 3 bits
      i++;                // increment counter value
    else                  
      i=0;                // reset counter to 0
      
    int a=i%2;            // calculate LSB 
    int b=i/2 %2;         // calculate middle bit
    int c=i/4 %2;         // calculate MSB 
    
    digitalWrite(11,c);   // write MSB
    digitalWrite(12,b);   // write middle bit
    digitalWrite(13,a);   // write LSB
    while(digitalRead(7)==0);   // wait till button is released to avoid incrementing the counter again
    delay(100);                 // small delay to avoid debounce
  }
}
