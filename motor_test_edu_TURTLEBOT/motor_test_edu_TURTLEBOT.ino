#include <edu_motor.h>

Motor motor1(16,17);
Motor motor2(18,19);

void setup()
{
motor1.forward();
motor2.forward();
pinMode(7,OUTPUT);
}

void loop()
{
digitalWrite(7,HIGH);
delay(100);
digitalWrite(7,LOW);
delay(100);
}



