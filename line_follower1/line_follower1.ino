/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */

int motorLeftpin1=2;
int motorLeftpin2=4;
int motorRightpin1=12;
int motorRightpin2=13;

int IRsensor1=19;
int IRsensor2=3;
int IRsensor3=9;

int sensor_val1=0;
int sensor_val2=0;
int sensor_val3=0;


void setup() {                
//initialize the digital pin as an output.
pinMode(2,OUTPUT);
pinMode(4,OUTPUT);
pinMode(12,OUTPUT);
pinMode(13,OUTPUT);
Serial.begin(9600);
pinMode(IRsensor1,INPUT);
pinMode(IRsensor2,INPUT);
pinMode(IRsensor3,INPUT);
}

void loop() 
{
sensor_val1=digitalRead(IRsensor1);
sensor_val2=digitalRead(IRsensor2);
sensor_val3=digitalRead(IRsensor3);

if((sensor_val3==0&&sensor_val1==1&&sensor_val2==1)||(sensor_val3==0&&sensor_val2==0)) 
{
  digitalWrite(2,HIGH);
digitalWrite(4,LOW);
digitalWrite(12,HIGH);
digitalWrite(13,LOW);
delay(100);
}

else if(sensor_val1==0&&sensor_val2==0)
{digitalWrite(2,LOW);
digitalWrite(4,HIGH);
digitalWrite(12,HIGH);
digitalWrite(13,LOW);
delay(300);}

else if(sensor_val1==0&&sensor_val3==0)
{digitalWrite(2,LOW);
digitalWrite(4,HIGH);
digitalWrite(12,HIGH);
digitalWrite(13,LOW);
delay(300);}


else if(sensor_val1==0)
{digitalWrite(2,LOW);
digitalWrite(4,HIGH);
digitalWrite(12,HIGH);
digitalWrite(13,LOW);
delay(100);
}



else if(sensor_val2==0)
{digitalWrite(2,HIGH);
digitalWrite(4,LOW);
digitalWrite(12,LOW);
digitalWrite(13,HIGH);
delay(100);}



}
// wait for a second

