#include <PinChangeInt.h>
//#include <PinChangeIntConfig.h>

int led = 7;
int ch8_pin=11;
int ch7_pin=10;
int ch6_pin=9;
int ch5_pin=8;
int ch4_pin=6;
int ch3_pin=5;
int ch2_pin=4;
int ch1_pin=3;

volatile uint16_t ch8_start=0, ch8_global_count=0;
volatile uint16_t ch7_start=0, ch7_global_count=0;
volatile uint16_t ch6_start=0, ch6_global_count=0;
volatile uint16_t ch5_start=0, ch5_global_count=0;
volatile uint16_t ch4_start=0, ch4_global_count=0;
volatile uint16_t ch3_start=0, ch3_global_count=0;
volatile uint16_t ch2_start=0, ch2_global_count=0;
volatile uint16_t ch1_start=0, ch1_global_count=0;

volatile uint8_t flag=LOW;//global flag

volatile uint8_t ch8_global_flag=LOW;//global flag
volatile uint8_t ch7_global_flag=LOW;//global flag
volatile uint8_t ch6_global_flag=LOW;//global flag
volatile uint8_t ch5_global_flag=LOW;//global flag
volatile uint8_t ch4_global_flag=LOW;//global flag
volatile uint8_t ch3_global_flag=LOW;//global flag
volatile uint8_t ch2_global_flag=LOW;//global flag
volatile uint8_t ch1_global_flag=LOW;//global flag

// the setup routine runs once when you press reset:
void setup() 
{                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT); 
  Serial.begin(9600);

  PCintPort::attachInterrupt(ch8_pin,ch8_count,CHANGE); 
  PCintPort::attachInterrupt(ch7_pin,ch7_count,CHANGE); 
  PCintPort::attachInterrupt(ch6_pin,ch6_count,CHANGE); 
  PCintPort::attachInterrupt(ch5_pin,ch5_count,CHANGE); 
  PCintPort::attachInterrupt(ch4_pin,ch4_count,CHANGE); 
  PCintPort::attachInterrupt(ch3_pin,ch3_count,CHANGE); 
  PCintPort::attachInterrupt(ch2_pin,ch2_count,CHANGE); 
  PCintPort::attachInterrupt(ch1_pin,ch1_count,CHANGE); 
  Serial.println("press the button");
}

// the loop routine runs over and over again forever:
void loop() {

  volatile static uint16_t ch8_static_count;//local count
  volatile static uint16_t ch7_static_count;//local count
  volatile static uint16_t ch6_static_count;//local count
  volatile static uint16_t ch5_static_count;//local count
  volatile static uint16_t ch4_static_count;//local count
  volatile static uint16_t ch3_static_count;//local count
  volatile static uint16_t ch2_static_count;//local count
  volatile static uint16_t ch1_static_count;//local count
  
  volatile static uint8_t updateflags;//lcoal flag
  volatile static uint8_t ch8_update_flag;//lcoal flag
  volatile static uint8_t ch7_update_flag;//lcoal flag
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
    ch8_update_flag=ch8_global_flag;
    ch7_update_flag=ch7_global_flag;
    ch6_update_flag=ch6_global_flag;
    ch5_update_flag=ch5_global_flag;
    ch4_update_flag=ch4_global_flag;
    ch3_update_flag=ch3_global_flag;
    ch2_update_flag=ch2_global_flag;
    ch1_update_flag=ch1_global_flag;
    
    if(ch8_update_flag)
    {    
      ch8_static_count=ch8_global_count;
    }
    if(ch7_update_flag)
    {    
      ch7_static_count=ch7_global_count;
    }
    
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


//    Serial.print("ch1:  ");
    Serial.println(ch1_static_count);

//    Serial.print("ch2:  ");
    Serial.println(ch2_static_count);
//    Serial.print("\t");
  
//    Serial.print("ch3:  ");
    Serial.println(ch3_static_count);
//    Serial.print("\t");
    
//    Serial.print("ch4:  ");
    Serial.println(ch4_static_count);
//    Serial.print("\t");
    
//    Serial.print("ch5:  ");
    Serial.println(ch5_static_count);
//    Serial.print("\t");
  
//    Serial.print("ch6:  ");
    Serial.println(ch6_static_count);
//    Serial.print("\t");
    
//    Serial.print("ch7:  ");
    Serial.println(ch7_static_count);
//    Serial.print("\t");

//    Serial.print("ch8:  ");
    Serial.println(ch8_static_count);
//    Serial.print("\t");
    
    Serial.print("\n");
    
     ch8_global_count=0;
     ch8_static_count=0;
     ch8_global_flag=0;
     ch8_update_flag=0;
     
     ch7_global_count=0;
     ch7_static_count=0;
     ch7_global_flag=0;
     ch7_update_flag=0;
     
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
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(200);               // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(200);  
}

void ch8_count()
{
  //Seria8.println(millis());
  if(digitalRead(ch8_pin)==HIGH)
  {
    ch8_start= micros();
  }
  else
  {
    ch8_global_count=(uint16_t)(micros()-ch8_start);
    flag=HIGH;
    ch7_global_flag=HIGH;
  }
}

void ch7_count()
{
  //Serial.println(millis());
  if(digitalRead(ch7_pin)==HIGH)
  {
    ch7_start= micros();
  }
  else
  {
    ch7_global_count=(uint16_t)(micros()-ch7_start);
    flag=HIGH;
    ch7_global_flag=HIGH;
  }
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
