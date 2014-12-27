

/*

Using
Serial0 or serial for ROS
Serial1           for IMU
Serial2           for Sabertooth
Serial3           for RC


*/


#include <ros.h>
#include <std_msgs/String.h>
#include "SabertoothSimplified.h"

#include <Wire.h>
#include "HMC5883L.h"

#include <PinChangeInt.h>


SabertoothSimplified ST;

HMC5883L compass;
MagnetometerScaled scaled;


//***************************************************Pin Interrupts Declaration************************************



int led = 13;
int ch6_pin=11;
int ch5_pin=10;
int ch4_pin=9;
int ch3_pin=8;
int ch2_pin=7;
int ch1_pin=6;

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


//************************************************************************************************************
ros::NodeHandle  nh;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char hello[13] = "hello world!";

void setup()
{
  nh.initNode();
  nh.advertise(chatter);
  SabertoothTXPinSerial.begin(9600); // This is the baud rate you chose with the DIP switches.

  Serial1.begin(9600);
  Serial3.begin(9600);
  
  Wire.begin();
  compass = HMC5883L(); //new instance of HMC5883L library
  setupHMC5883L(); //setup the HMC5883L

//****************************************pin interrupts**********************************************
  pinMode(led, OUTPUT); 
//  Serial.begin(9600);
  PCintPort::attachInterrupt(ch6_pin,ch6_count,CHANGE); 
  PCintPort::attachInterrupt(ch5_pin,ch5_count,CHANGE); 
  PCintPort::attachInterrupt(ch4_pin,ch4_count,CHANGE); 
  PCintPort::attachInterrupt(ch3_pin,ch3_count,CHANGE); 
  PCintPort::attachInterrupt(ch2_pin,ch2_count,CHANGE); 
  PCintPort::attachInterrupt(ch1_pin,ch1_count,CHANGE); 
//  Serial.println("press the button");

//****************************************pin interrupts**********************************************


}

void loop()
{
  pin_interrupt_loop();
  str_msg.data = hello;
  chatter.publish( &str_msg );
  nh.spinOnce();
  //delay(1000);
  
  ST.motor(1, 127);  // Go forward at full power.
  delay(2000);       // Wait 2 seconds.
  ST.motor(1, 0);    // Stop.
  delay(2000);       // Wait 2 seconds.
  ST.motor(1, -127); // Reverse at full power.
  delay(2000);       // Wait 2 seconds.
  ST.motor(1, 0);    // Stop.
  delay(2000);


    float heading = getHeading();
    Serial1.println(scaled.XAxis);
    Serial1.println(scaled.YAxis);
    Serial1.println(scaled.ZAxis);
    Serial1.print("                ");
    Serial1.println(heading);
    delay(100); //only here to slow down the serial print

}



void setupHMC5883L(){
  //Setup the HMC5883L, and check for errors
  int error;  
  error = compass.SetScale(1.3); //Set the scale of the compass.
  if(error != 0) Serial1.println(compass.GetErrorText(error)); //check if there is an error, and print if so

  error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
  if(error != 0) Serial.println(compass.GetErrorText(error)); //check if there is an error, and print if so
}

float getHeading(){
  //Get the reading from the HMC5883L and calculate the heading
  scaled = compass.ReadScaledAxis(); //scaled values from compass.
  float heading = atan2(scaled.ZAxis, scaled.YAxis);

  // Correct for when signs are reversed.
  if(heading < 0) heading += 2*PI;
  if(heading > 2*PI) heading -= 2*PI;

  return heading * RAD_TO_DEG; //radians to degrees
}



void pin_interrupt_loop()
{

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
     Serial3.println(ch6_static_count);
//    Serial.print("\t");
    
//    Serial.print("ch5:  ");
    Serial3.println(ch5_static_count);
//    Serial.print("\t");
    
//    Serial.print("ch4:  ");
    Serial3.println(ch4_static_count);
//    Serial.print("\t");
    
//    Serial.print("ch3:  ");
    Serial3.println(ch3_static_count);
//    Serial.print("\t");
    
//    Serial.print("ch2:  ");
    Serial3.println(ch2_static_count);
//    Serial.print("\t");
    
//    Serial.print("ch1:  ");
    Serial3.println(ch1_static_count);
//    Serial.print("\n");
    
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

} 

//****************************************************pin interrupts functions***********************************************************************


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
