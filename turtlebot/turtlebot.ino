



#include <PinChangeInt.h>
//#include <PinChangeIntConfig.h>

int led=13;

int ch2_pin=7;
int ch1_pin=6;
int MOTOR1_1=2;
int MOTOR1_2=3;
int MOTOR2_1=4;
int MOTOR2_2=5;


void test_driver();


volatile uint16_t ch2_start=0, ch2_global_count=0;
volatile uint16_t ch1_start=0, ch1_global_count=0;


volatile uint16_t CH2_MAX=0, CH2_MIN=1500;
volatile uint16_t CH1_MAX=0, CH1_MIN=1500;

volatile uint8_t flag=LOW;//global flag

volatile uint8_t ch2_global_flag=LOW;//global flag
volatile uint8_t ch1_global_flag=LOW;//global flag

// the setup routine runs once when you press reset:
void setup() 
{                
  // initialize the digital pin as an output.
  Serial.begin(9600);
  PCintPort::attachInterrupt(ch2_pin,ch2_count,CHANGE); 
  PCintPort::attachInterrupt(ch1_pin,ch1_count,CHANGE); 
  Serial.println("HIT the button");

pinMode(led, OUTPUT);  

pinMode(MOTOR1_1,OUTPUT);
pinMode(MOTOR1_2,OUTPUT);

pinMode(MOTOR2_1,OUTPUT);
pinMode(MOTOR2_2,OUTPUT);
//
//Go STOP
digitalWrite(MOTOR1_1,LOW);
digitalWrite(MOTOR1_1,LOW);

digitalWrite(MOTOR2_1,LOW);
digitalWrite(MOTOR2_2,LOW);

}

void loop() {
  volatile static uint16_t ch2_static_count;//local count
  volatile static uint16_t ch1_static_count;//local count
  
  volatile static uint8_t updateflags;//lcoal flag
  volatile static uint8_t ch2_update_flag;//lcoal flag
  volatile static uint8_t ch1_update_flag;//lcoal flag 
  volatile uint16_t ch1_val=0, ch2_val=0;
  
  if(flag)
  {
    noInterrupts();
    updateflags=flag;
    ch2_update_flag=ch2_global_flag;
    ch1_update_flag=ch1_global_flag;
    
    if(ch2_update_flag)
    {    
      ch2_static_count=ch2_global_count;
      if(ch2_static_count > CH2_MAX){ CH2_MAX=ch2_static_count ; }
      if(ch2_static_count < CH2_MIN){ CH2_MIN=ch2_static_count ; }
    }
    if(ch1_update_flag)
    {    
      ch1_static_count=ch1_global_count;
      if(ch1_static_count > CH1_MAX){ CH1_MAX=ch1_static_count ; }
      if(ch1_static_count < CH1_MIN){ CH1_MIN=ch1_static_count ; }
    }
    
    ch2_val=map(ch2_static_count, CH2_MIN, CH2_MAX, 0, 255);
    ch1_val=map(ch1_static_count, CH1_MIN, CH1_MAX, 0, 255);
 
 
   if(ch1_val>200)
       move_forward();
   else if(ch1_val<70)
       move_backward();
   else 
       move_stop();   
    
//   movement(ch2_val, ch1_val);
   Serial.println(ch1_val);
   Serial.print("\t");     
   Serial.println(ch2_val);
   Serial.print("\n");     
   
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


void test_driver()
{


}


void move_forward()
{
digitalWrite(MOTOR1_1,HIGH);
digitalWrite(MOTOR1_2,LOW);

digitalWrite(MOTOR2_1,LOW);
digitalWrite(MOTOR2_2,HIGH);
}


void move_backward()
{

digitalWrite(MOTOR1_1,LOW);
digitalWrite(MOTOR1_2,HIGH);

digitalWrite(MOTOR2_1,HIGH);
digitalWrite(MOTOR2_2,LOW


);
}

void move_stop()
{

digitalWrite(MOTOR1_1,LOW);
digitalWrite(MOTOR1_2,LOW);

digitalWrite(MOTOR2_1,LOW);
digitalWrite(MOTOR2_2,LOW

);
}


