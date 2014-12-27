#include <Arduino.h>
#include <ros.h>
#include <std_msgs/UInt16.h>

ros::NodeHandle  nh;


void servo_cb( const std_msgs::UInt16& cmd_msg)
{
//  servo.write(cmd_msg.data);   
  
  if(cmd_msg.data == 2)
   {
     digitalWrite(13,HIGH); 
   }
  else if(cmd_msg.data == 8)
   {
   digitalWrite(13,LOW);
   }
  else if(cmd_msg.data == 4)
   {
     digitalWrite(13,HIGH);
   }
  else if(cmd_msg.data == 6)
   {
   digitalWrite(13,LOW);
   }
  else 
   {
   
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
