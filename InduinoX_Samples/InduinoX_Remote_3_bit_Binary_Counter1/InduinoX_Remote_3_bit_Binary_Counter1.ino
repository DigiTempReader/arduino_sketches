
/* 
 
 This sketch increases a 3 bit number every time '+' button is pressed and decreases the value when '-' button is pressed on the remote.It shows the output on 3 LEDs in Binary Format 
 
 */

#include <IRremote.h>

int RECV_PIN = 15;

IRrecv irrecv(RECV_PIN);

decode_results results;

int i = 0;

void setup()
{
  pinMode(11,OUTPUT);     // declare LED pins as output pins
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);

  pinMode(7,INPUT);// Declare the 7th pin as a input pin. We will use the button on the 7th pin
  digitalWrite(7,HIGH);

  irrecv.enableIRIn(); // Start the Remote receiver
  Serial.begin(9600);
}

void loop()
{
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    if(results.value==1168)   // if the '+' button is pressed
    {
      if(i<7)               // if counter value is less than 7 or 3 bits
        i++;                // increment counter value
      else                  
        i=0;                // reset counter to 0

    }
    if(results.value==3216)   // if the '-' button is pressed
    {
      if(i>0)               // if counter value is greater than 0 or 3 bits
        i--;                // decrement counter value
      else                  
        i=7;                // reset counter to 7
    }
      int a=i%2;            // calculate LSB 
      int b=i/2 %2;         // calculate middle bit
      int c=i/4 %2;         // calculate MSB 

      digitalWrite(11,c);   // write MSB
      digitalWrite(12,b);   // write middle bit
      digitalWrite(13,a);   // write LSB
      while(digitalRead(7)==0);   // wait till button is released to avoid incrementing the counter again
      delay(300);                 // small delay to avoid debounce
      irrecv.resume(); // Receive the next value
    }
   
  }



