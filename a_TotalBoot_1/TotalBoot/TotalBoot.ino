//*********************ROS addition***************************

#include <Arduino.h>
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/String.h>

ros::NodeHandle  nh;
std_msgs::String str_msg;


ros::Publisher chatter("chatter", &str_msg);
//ros::Subscriber<std_msgs::UInt16> sub("my_bot", servo_cb);


char hello[] = "hello from Motor Controller!";

#include <SoftwareSerial.h>
#include "SabertoothSimplified.h"
#include <Wire.h>
#include <HMC5883L.h>


HMC5883L compass;
MagnetometerScaled scaled;
//****************SUBSCRIBER DECLARATION**************************
//****************************************************************

int led=7;
////////////saber tooth///////////////
SoftwareSerial SWSerial(NOT_A_PIN, 11); // RX on no pin (unused), TX on pin 11 (to S1).
SabertoothSimplified ST(SWSerial); // Use SWSerial as the serial port.
//////////////////////////////////////////
//////////movement correction///////////
float correction_forward=1;
float correction_back=1;
float correction_turn=1;
////////////////////////////////////////
/////////////////////////////////////////
void setup()
{
  //SWSerial.begin(57600);
  //**********************INITIALLISATION ROS NODES*************
  nh.initNode();
  //nh.subscribe(sub);
  nh.advertise(chatter);
  //************************************************************
  ////////////magneto-setup//////////////
  //Serial.begin(9600);
  Wire.begin();
  compass = HMC5883L(); //new instance of HMC5883L library
  setupHMC5883L(); //setup the HMC5883L


}


void loop()
{
  str_msg.data = hello;
  chatter.publish( &str_msg );
  nh.spinOnce();
/*
  move_forward(100);
  delay(500);
  move_stop();
  delay(500);
  nh.spinOnce();
*/
}


//********************FUNCTIONS*******************************

void move_forward(int power)
{
    int aux_power=power*correction_forward;
    ST.motor(1, power);
    ST.motor(2, aux_power);
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

void setupHMC5883L()
{
  //Setup the HMC5883L, and check for errors
  int error=0;  
  float myscale=1.3;
  error = compass.SetScale(myscale); //Set the scale of the compass.
  if(error != 0) Serial.println(compass.GetErrorText(error)); //check if there is an error, and print if so

  error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
  if(error != 0) Serial.println(compass.GetErrorText(error)); //check if there is an error, and print if so
}

float getHeading()
{
  //Get the reading from the HMC5883L and calculate the heading
  scaled = compass.ReadScaledAxis(); //scaled values from compass.
  float heading = atan2(scaled.YAxis, scaled.XAxis);

  // Correct for when signs are reversed.
  if(heading < 0) heading += 2*PI;
  if(heading > 2*PI) heading -= 2*PI;

  return heading * RAD_TO_DEG; //radians to degrees
}

