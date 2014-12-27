//don
/*
Using
Serial0 or serial for ROS
Serial1           for IMU
Serial2           for Sabertooth
Serial3           for RC
*/

//#include <ros.h>
//#include <std_msgs/String.h>
#include "SabertoothSimplified.h"
SabertoothSimplified ST;


//////////movement correction///////////
float correction_forward=1;
float correction_back=1;
float correction_turn=1;
////////////////////////////////////////


//***************************************************Pin Interrupts Declaration************************************
//**************************RC declarations************************************************************************
int led = 13;
int ch1_pin=2;
int ch2_pin=3;
int ch3_pin=20;
int ch4_pin=21;

volatile uint16_t CH4_MAX=1820, CH4_MIN=1164;
volatile uint16_t CH2_MAX=1640, CH2_MIN=1320;

volatile uint16_t ch4_start=0, ch4_global_count=0;
volatile uint16_t ch3_start=0, ch3_global_count=0;
volatile uint16_t ch2_start=0, ch2_global_count=0;
volatile uint16_t ch1_start=0, ch1_global_count=0;

volatile uint8_t flag=LOW;//global flag

volatile uint8_t ch4_global_flag=LOW;//global flag
volatile uint8_t ch3_global_flag=LOW;//global flag
volatile uint8_t ch2_global_flag=LOW;//global flag
volatile uint8_t ch1_global_flag=LOW;//global flag
//***********************************************************************************************************
//************************************************************************************************************
//ros::NodeHandle  nh;
//
//std_msgs::String str_msg;
//ros::Publisher chatter("chatter", &str_msg);
//
//char hello[13] = "hello world!";
//************************************************************setup******************************************
void setup()
{
//  nh.initNode();
//  nh.advertise(chatter);

///////////motor setup//////////////////
    SabertoothTXPinSerial.begin(9600); // This is the baud rate you chose with the DIP switches.
    Serial1.begin(9600);
    Serial3.begin(9600);
    
     ST.motor(1, 30);
     ST.motor(2, 30);
     delay(300);
//**************************************** RC interrupts**********************************************
  pinMode(led, OUTPUT); 
  Serial.begin(9600);
  attachInterrupt(0, ch1_count, CHANGE);//pin 2 - ch1
  attachInterrupt(1, ch2_count, CHANGE);    //3 ch2
  attachInterrupt(3, ch3_count, CHANGE);    //21 ch3
  attachInterrupt(2, ch4_count, CHANGE);    //20 ch4
  Serial.println("press the button");
//****************************************pin interrupts**********************************************
}
void loop()
{

/////////////RC declarations/////////////////////////////
  volatile static uint16_t ch4_static_count;//local count
  volatile static uint16_t ch3_static_count;//local count
  volatile static uint16_t ch2_static_count;//local count
  volatile static uint16_t ch1_static_count;//local count
  
  volatile static uint8_t updateflags;//lcoal flag
  volatile static uint8_t ch4_update_flag;//lcoal flag
  volatile static uint8_t ch3_update_flag;//lcoal flag
  volatile static uint8_t ch2_update_flag;//lcoal flag
  volatile static uint8_t ch1_update_flag;//lcoal flag 
  
  volatile int ch4_val=0, ch2_val=0;
   
  if(flag)
  {
    noInterrupts();
    updateflags=flag;
    ch4_update_flag=ch4_global_flag;
    ch3_update_flag=ch3_global_flag;
    ch2_update_flag=ch2_global_flag;
    ch1_update_flag=ch1_global_flag;
    
    if(ch3_update_flag)
    {    
      ch3_static_count=ch3_global_count;
//      Serial.println(ch3_static_count);

    }
    if(ch1_update_flag)
    {    
      ch1_static_count=ch1_global_count;
//      Serial.println(ch1_static_count);
    }

   if(ch2_update_flag)
    {
      ch2_static_count=ch2_global_count;
//      Serial.println(ch2_static_count);
    }
    if(ch4_update_flag)
    {    
      ch4_static_count=ch4_global_count;
//      Serial.println(ch4_static_count);
    }
//     Serial.println(int(ch2_val));
//     Serial.println(int(ch4_val));
//     Serial.println("\n");
//   
     ch4_global_count=0;
     ch4_global_flag=0;
     ch4_update_flag=0;
     
     ch3_global_count=0;
     ch3_global_flag=0;
     ch3_update_flag=0;
     
     ch2_global_count=0;
     ch2_global_flag=0;
     ch2_update_flag=0;
     
     ch1_global_count=0;
     ch1_global_flag=0;
     ch1_update_flag=0;     
     
     flag=0;
     interrupts();

//   motor_movement(ch2_static_count, ch4_static_count);
   motor_movement(ch2_static_count, ch3_static_count);
    }
/////////////////////RC control complete/////////////////////////////////////

//    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
//    delay(100);               // wait for a second
//    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
//    delay(100);  
//    
}  
//************************************motor functions***************************************************************
void motor_movement(uint16_t m1, uint16_t m2)
{
   
     if (m1 < 1360)
        {   
//          ST.motor(1, +70);
          move_forward(70);
        
        }  

   else if(m1 > 1560)
        {    
//            ST.motor(1, -70);
             move_backward(70);
      }    

//   if((1360 < m1) && (m1 < 1560))
//       {
////           ST.motor(1, 0);  
//
//     }
    else if (m2 < 1420)
        {   
//          ST.motor(2, +70);
          move_turn(-80);
        }  

    else if(m2 > 1620)
        {    
//            ST.motor(2, -70);
          move_turn(+80);  
      }    

   else 
       move_stop();
   
//   
//   if((1420 < m2) && (m2 < 1620))
//       {
//          ST.motor(2, 0);
//       }
}

void move_forward(int power)
{
    int aux_power=power*correction_forward;
    ST.motor(1, power);
    ST.motor(2, power);
}

void move_backward(int power)
{
    power=-1*power;
    int aux_power=power*correction_back;
    ST.motor(1, power);
    ST.motor(2, aux_power);
}
void move_stop()
{
    ST.motor(1, 0);
    ST.motor(2, 0);
}
void move_turn(int power)
{
    int aux_power=-1*power*correction_turn;
    ST.motor(1, power);
    ST.motor(2, aux_power);
}

//****************************************************pin interrupts functions***********************************************************************
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
