#include <PinChangeInt.h>

////////odometer///////////////////////

int left1=3;//to be inverted later
int left2=4;
int right1=5;
int right2=6;
volatile int leftlastEncoded = 0;
volatile long leftencoderValue = 0;
long leftlastencoderValue = 0;
volatile int rightlastEncoded = 0;
volatile long rightencoderValue = 0;
long rightlastencoderValue = 0;

volatile int leftRotation = 0;
volatile int rightRotation = 0;
volatile float totalRotation=0;
volatile float theta=0;
int x=0;
int y=0;
volatile float distance=0.0;
int wheelBase=23;
/*****************************************************
**multiplication_factor= 2pi * r / 16

2*3.14*(2*2.54)/16=1.9939

avg_rotation=(left+right)/2
distance=avg rotation * multiplication_factor

or 

distance=total_rotation * new multiplication

 new multiplication_factor=1.9939/2=0.99695
*****************************************************/
const float multiplication_factor=0.99695;
volatile uint8_t rotaryFlag=LOW;//global flag for rotary

//int rightlastMSB = 0;
//int rightlastLSB = 0;
/////////////////////////////////////////

//////////rc ////////////////////////////

int led = 7;
int ch6_pin=17;
int ch5_pin=16;
int ch4_pin=15;
int ch3_pin=14;
int ch2_pin=13;
int ch1_pin=12;


volatile uint16_t ch6_start=0, ch6_global_count=0;
volatile uint16_t ch5_start=0, ch5_global_count=0;
volatile uint16_t ch4_start=0, ch4_global_count=0;
volatile uint16_t ch3_start=0, ch3_global_count=0;
volatile uint16_t ch2_start=0, ch2_global_count=0;
volatile uint16_t ch1_start=0, ch1_global_count=0;

volatile uint8_t flag=LOW;//global flag

volatile uint8_t ch6_global_flag=LOW;//global flag
volatile uint8_t ch5_global_flag=LOW;//global flag
volatile uint8_t ch4_global_flag=LOW;//global flag
volatile uint8_t ch3_global_flag=LOW;//global flag
volatile uint8_t ch2_global_flag=LOW;//global flag
volatile uint8_t ch1_global_flag=LOW;//global flag
//////////////////////////////////////////////////

void setup()
{
    Serial.begin(9600);
    pinMode(led,OUTPUT);
    setup_rotaryEncoder();
    setup_rc();
}

void setup_rotaryEncoder()
{
  leftencoderValue=0;
  rightencoderValue=0;
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

void setup_rc()
{
  PCintPort::attachInterrupt(ch6_pin,ch6_count,CHANGE); 
  PCintPort::attachInterrupt(ch5_pin,ch5_count,CHANGE); 
  PCintPort::attachInterrupt(ch4_pin,ch4_count,CHANGE); 
  PCintPort::attachInterrupt(ch3_pin,ch3_count,CHANGE); 
  PCintPort::attachInterrupt(ch2_pin,ch2_count,CHANGE); 
  PCintPort::attachInterrupt(ch1_pin,ch1_count,CHANGE); 
  Serial.println("press the button");
}

void loop()
{
  volatile static uint8_t update_rotaryFlag;
  
  volatile static uint16_t ch6_static_count;//local count
  volatile static uint16_t ch5_static_count;//local count
  volatile static uint16_t ch4_static_count;//local count
  volatile static uint16_t ch3_static_count;//local count
  volatile static uint16_t ch2_static_count;//local count
  volatile static uint16_t ch1_static_count;//local count
  
  volatile static uint8_t updateflags;//lcoal flag
  volatile static uint8_t ch6_update_flag;//lcoal flag
  volatile static uint8_t ch5_update_flag;//lcoal flag
  volatile static uint8_t ch4_update_flag;//lcoal flag
  volatile static uint8_t ch3_update_flag;//lcoal flag
  volatile static uint8_t ch2_update_flag;//lcoal flag
  volatile static uint8_t ch1_update_flag;//lcoal flag 
  
  if(flag)
        {
          noInterrupts();
          updateflags=flag;
          ch6_update_flag=ch6_global_flag;
          ch5_update_flag=ch5_global_flag;
          ch4_update_flag=ch4_global_flag;
          ch3_update_flag=ch3_global_flag;
          ch2_update_flag=ch2_global_flag;
          ch1_update_flag=ch1_global_flag;
          
          if(ch6_update_flag)
          {    
            ch6_static_count=ch6_global_count;
          }
          if(ch5_update_flag)
          {    
            ch5_static_count=ch5_global_count;
          }
          if(ch4_update_flag)
          {    
            ch4_static_count=ch4_global_count;
          }
          if(ch3_update_flag)
          {    
            ch3_static_count=ch3_global_count;
          }
          if(ch2_update_flag)
          {    
            ch2_static_count=ch2_global_count;
          }
          if(ch1_update_flag)
          {    
            ch1_static_count=ch1_global_count;
          }
        //    Serial.print("ch6:  ");
         // Serial.println(ch6_static_count);
        //    Serial.print("\t");
          
        //    Serial.print("ch5:  ");
         // Serial.println(ch5_static_count);
        //    Serial.print("\t");
          
        //    Serial.print("ch4:  ");
         // Serial.println(ch4_static_count);
        //    Serial.print("\t");
          
        //    Serial.print("ch3:  ");
        //  Serial.println(ch3_static_count);
        //    Serial.print("\t");
          
        //    Serial.print("ch2:  ");
        //  Serial.println(ch2_static_count);
        //    Serial.print("\t");
          
        //    Serial.print("ch1:  ");
         // Serial.println(ch1_static_count);
         // Serial.print("\n");
          
           ch6_global_count=0;
           ch6_static_count=0;
           ch6_global_flag=0;
           ch6_update_flag=0;
           
           ch5_global_count=0;
           ch5_static_count=0;
           ch5_global_flag=0;
           ch5_update_flag=0;
           
           ch4_global_count=0;
           ch4_static_count=0;
           ch4_global_flag=0;
           ch4_update_flag=0;
           
           ch3_global_count=0;
           ch3_static_count=0;
           ch3_global_flag=0;
           ch3_update_flag=0;
           
           ch2_global_count=0;
           ch2_static_count=0;
           ch2_global_flag=0;
           ch2_update_flag=0;
           
           ch1_global_count=0;
           ch1_static_count=0;
           ch1_global_flag=0;
           ch1_update_flag=0;     
           flag=0;
           interrupts();
       }
    
    if(rotaryFlag)
    {
       noInterrupts(); 
       update_rotaryFlag=rotaryFlag;
       leftRotation = (leftencoderValue/16);
       rightRotation = (rightencoderValue/16);
       Serial.print('\n');
        Serial.println(leftRotation);
        Serial.println(rightRotation);
               
          totalRotation = (leftRotation + rightRotation);
          theta=(leftRotation-rightRotation)/wheelBase;
          distance=totalRotation * multiplication_factor;
          x= distance * sin(theta);
          y= distance * cos(theta);
          
          Serial.println(theta);
          Serial.println(distance);
         Serial.print('\n');   
          update_rotaryFlag=0;
          rotaryFlag=0;
         interrupts();
    }
         
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);               // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(100);  
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
  
  if (leftsum == 0b1101 || leftsum == 0b0100 || leftsum == 0b0010 || leftsum == 0b1011) 
     leftencoderValue ++;
  if (leftsum == 0b1110 || leftsum == 0b0111 || leftsum == 0b0001 || leftsum == 0b1000) 
     leftencoderValue --;

  leftlastEncoded = leftencoded; //store this value for next time
  
  rotaryFlag=1;
// Serial.print("left \t");
 Serial.println(leftencoderValue);  
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
  rotaryFlag=1;
  Serial.print("\n\t");
  Serial.println(rightencoderValue);
}

void ch6_count()
{
  //Serial.println(millis());
  if(digitalRead(ch6_pin)==HIGH)
  {
    ch6_start= micros();
  }
  else
  {
    ch6_global_count=(uint16_t)(micros()-ch6_start);
    flag=HIGH;
    ch6_global_flag=HIGH;
  }
}
void ch5_count()
{
  //Serial.println(millis());
  if(digitalRead(ch5_pin)==HIGH)
  {
    ch5_start= micros();
  }
  else
  {
    ch5_global_count=(uint16_t)(micros()-ch5_start);
    flag=HIGH;
    ch5_global_flag=HIGH;
  }
}
void ch4_count()
{
  //Serial.println(millis());
  if(digitalRead(ch4_pin)==HIGH)
  {
    ch4_start= micros();
  }
  else
  {
    ch4_global_count=(uint16_t)(micros()-ch4_start);
    flag=HIGH;
    ch4_global_flag=HIGH;
  }
}
void ch3_count()
{
  //Serial.println(millis());
  if(digitalRead(ch3_pin)==HIGH)
  {
    ch3_start= micros();
  }
  else
  {
    ch3_global_count=(uint16_t)(micros()-ch3_start);
    flag=HIGH;
    ch3_global_flag=HIGH;
  }
}
void ch2_count()
{
  //Serial.println(millis());
  if(digitalRead(ch2_pin)==HIGH)
  {
    ch2_start= micros();
  }
  else
  {
    ch2_global_count=(uint16_t)(micros()-ch2_start);
    flag=HIGH;
    ch2_global_flag=HIGH;
  }
}
void ch1_count()
{
  //Serial.println(millis());
  if(digitalRead(ch1_pin)==HIGH)
  {
    ch1_start= micros();
  }
  else
  {
    ch1_global_count=(uint16_t)(micros()-ch1_start);
    flag=HIGH;
    ch1_global_flag=HIGH;
  }
}
