
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>
#include <std_msgs/UInt32.h>
#include <std_msgs/Float32.h>

ros::NodeHandle  nh;

std_msgs::String str_msg;
std_msgs::Int16 myint_16;
std_msgs::UInt32 myuint_32;
std_msgs::Float32 myfloat_32;


ros::Publisher chatter1("chatter1", &str_msg);
ros::Publisher chatter2("chatter2", &myint_16);
ros::Publisher chatter3("chatter3", &myuint_32);
ros::Publisher chatter4("chatter4", &myfloat_32);

char hello[13] = "hello world!";

void setup()
{
  nh.initNode();
  nh.advertise(chatter1);
  nh.advertise(chatter2);
  nh.advertise(chatter3);
  nh.advertise(chatter4);
  
}

void loop()
{
  str_msg.data = hello;
  myint_16.data = 10;
  myuint_32.data = 20;
  myfloat_32.data = 3.141592653589;
  
  //support is only upto 6 places
  
  chatter1.publish( &str_msg );
  chatter2.publish( &myint_16 );
  chatter3.publish( &myuint_32 );
  chatter4.publish( &myfloat_32 );
  
  nh.spinOnce();
  delay(1000);
}
