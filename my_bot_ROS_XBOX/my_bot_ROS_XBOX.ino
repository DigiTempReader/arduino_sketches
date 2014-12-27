#include <edu_motor.h>
#include <Arduino.h>
#include <Servo.h> 
#include <ros.h>
#include <std_msgs/UInt16.h>

ros::NodeHandle  nh;

Servo servo;
Motor motor1(16,17);
Motor motor2(18,19);
int motor1_speed=100;
int motor2_speed=100;
int all_off_flag=0;
int all_on_flag=1;



void servo_cb( const std_msgs::UInt16& cmd_msg)
{
//TO KNOW OFF/ON STATE
  if(cmd_msg.data == 7)
   {
     all_off_flag=1;
   }
 if(cmd_msg.data == 9)
   {
     all_on_flag=1;
   }
//******************************** 
 
 
 if(all_on_flag==1)
 {
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
   else if(cmd_msg.data == 25)
      {
       motor1_speed=125;
       motor2_speed=125;
      }
  else if(cmd_msg.data == 50)
      {
       motor1_speed=150;
       motor2_speed=150;
      }
 else if(cmd_msg.data == 75)
      {
       motor1_speed=175;
       motor2_speed=175;
      }
  else if(cmd_msg.data == 100)
      {
       motor1_speed=200;
       motor2_speed=200;
      }
  else if(cmd_msg.data == 125)
      {
       motor1_speed=225;
       motor2_speed=225;
      }
  else if(cmd_msg.data == 150)
      {
       motor1_speed=250;
       motor2_speed=250;
      }
  else 
   {
     motor1.halt();
     motor2.halt();
   }
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
//  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  motor1.forward();
  motor2.forward();
  delay(2000);
  motor1.halt();
  motor2.halt();
  servo.attach(3); //attach it to pin 9
  servo.write(90);
}

void loop()
{
  nh.spinOnce();
  delay(1);
  motor1.setspeed(motor1_speed);
  motor2.setspeed(motor2_speed);
//  digitalWrite(13,HIGH);
  //delay(100);
  //digitalWrite(13,LOW);
  //delay(100);

}
