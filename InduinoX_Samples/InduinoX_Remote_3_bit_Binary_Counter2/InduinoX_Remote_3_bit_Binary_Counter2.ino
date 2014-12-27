
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
    switch(results.value)   // if the '+' button is pressed
    {
      case 2320: i=0; break;// 2320 is the value for '0'
      case 16: i=1; break;// 16 is the value for '1'
      case 2064: i=2; break;// 2064 is the value for '2'
      case 1040: i=3; break;// 1040 is the value for '3'
      case 3088: i=4; break;// 3088 is the value for '4'
      case 528: i=5; break;// 528 is the value for '5'
      case 2576: i=6; break;// 2576 is the value for '6'
      case 1552: i=7; break;// 1552 is the value for '7'

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



