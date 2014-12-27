#include <PinChangeInt.h>
////////odometer///////////////////////

int left1=8;//to be inverted later
int left2=9;
int right1=10;
int right2=11;

volatile int leftlastEncoded = 0;
volatile long leftencoderValue = 0;
long leftlastencoderValue = 0;
//int leftlastMSB = 0;
//int leftlastLSB = 0;

volatile int rightlastEncoded = 0;
volatile long rightencoderValue = 0;
long rightlastencoderValue = 0;
//int rightlastMSB = 0;
//int rightlastLSB = 0;
/////////////////////////////////////////
void setup()
{
  
  leftencoderValue=0;
  rightencoderValue=0;
  Serial.begin (9600);
   pinMode(7, OUTPUT);
  pinMode(left1, INPUT); 
  pinMode(left2, INPUT);
  pinMode(right1, INPUT); 
  pinMode(right2, INPUT);
  
  digitalWrite(left1, HIGH); //turn pullup resistor on
  digitalWrite(left2, HIGH); //turn pullup resistor on
  digitalWrite(right1, HIGH); //turn pullup resistor on
  digitalWrite(right2, HIGH); //turn pullup resistor on
  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 

  PCintPort::attachInterrupt(left1,left_updateencoder,CHANGE); 
  PCintPort::attachInterrupt(left2,left_updateencoder,CHANGE);
  PCintPort::attachInterrupt(right1,right_updateencoder,CHANGE); 
  PCintPort::attachInterrupt(right2,right_updateencoder,CHANGE); 


}
void loop()
{
  digitalWrite(7, HIGH);   // set the LED on
  delay(100);              // wait for a second
  digitalWrite(7, LOW);    // set the LED off
  delay(100);              // wait for a second
  
//  
//  Serial.print(leftencoderValue);
//  
//  Serial.print("\t\t");
//  Serial.println(rightencoderValue);
}



void left_updateencoder()
{
  int leftMSB = digitalRead(left1); //MSB = most significant bit
  int leftLSB = digitalRead(left2); //LSB = least significant bit
  if(leftMSB==0) 
        leftMSB=1;
    else 
      leftMSB=0;
    


  int leftencoded = (leftMSB << 1) |leftLSB; //converting the 2 pin value to single number
  int leftsum  = (leftlastEncoded << 2) | leftencoded; //adding it to the previous encoded value

  if(leftsum == 0b1101 || leftsum == 0b0100 || leftsum == 0b0010 || leftsum == 0b1011) 
     leftencoderValue ++;
  if(leftsum == 0b1110 || leftsum == 0b0111 || leftsum == 0b0001 || leftsum == 0b1000) 
     leftencoderValue --;


  leftlastEncoded = leftencoded; //store this value for next time
  
  Serial.print("\n");
 Serial.print(leftencoderValue);
  
}
void right_updateencoder()
{
  int rightMSB = digitalRead(right1); //rightMSB = most significant bit
  int rightLSB = digitalRead(right2); //rightLSB = least significant bit

  int rightencoded = (rightMSB << 1) |rightLSB; //converting the 2 pin value to single number
  int rightsum  = (rightlastEncoded << 2) | rightencoded; //adding it to the previous encoded value

  if(rightsum == 0b1101 || rightsum == 0b0100 || rightsum == 0b0010 || rightsum == 0b1011) rightencoderValue ++;
  if(rightsum == 0b1110 || rightsum == 0b0111 || rightsum == 0b0001 || rightsum == 0b1000) rightencoderValue --;

  rightlastEncoded = rightencoded; //store this value for next time
  Serial.print("\t\t");
  Serial.println(rightencoderValue);
}
