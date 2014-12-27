#include <PinChangeInt.h>
//
#include <PinChangeIntConfig.h>

int encoderPin1 = 2;//to be inverted later
int encoderPin2 = 3;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

void setup() {
  Serial.begin (9600);


  pinMode(encoderPin1, INPUT); 
  pinMode(encoderPin2, INPUT);
  pinMode(7
  , OUTPUT);  
  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);

}

void loop() 
{
  digitalWrite(7, HIGH);   // set the LED on
  delay(1000);              // wait for a second
  digitalWrite(7, LOW);    // set the LED off
  delay(1000);              // wait for a second
}


void updateEncoder()
{
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit
  //inversino of lsb
  if(LSB==0) 
      LSB=1;
  else 
    LSB=0;
  int encoded = (MSB << 1)|LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
    
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;
   
  lastEncoded = encoded; //store this value for next time
  Serial.println(encoderValue);
}
