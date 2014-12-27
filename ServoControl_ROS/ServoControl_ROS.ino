#include <edu_motor.h>
#include <Arduino.h>
//#include <Servo.h> 
#include <ros.h>
#include <std_msgs/UInt16.h>

ros::NodeHandle  nh;

//Servo servo;
Motor motor1(2,4);
Motor motor2(7,8);

void servo_cb( const std_msgs::UInt16& cmd_msg)
{
//  servo.write(cmd_msg.data);   
  
  if(cmd_msg.data == 2)
   {
     motor1.backward();
     motor2.backward();
   }
  else if(cmd_msg.data == 8)
   {
     motor1.forward();
     motor2.forward();
   }
  else if(cmd_msg.data == 4)
   {
     motor1.forward();
     motor2.backward();
   }
  else if(cmd_msg.data == 6)
   {
     motor1.backward();
     motor2.forward();
   }
  else 
   {
     motor1.halt();
     motor2.halt();
   }
   
}


ros::Subscriber<std_msgs::UInt16> sub("my_bot", servo_cb);

void setup()
{
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
//  servo.attach(9); attach it to pin 9
}

void loop()
{
  nh.spinOnce();
  delay(1);
}
