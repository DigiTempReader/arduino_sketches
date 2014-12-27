#include "ADXL345_new.h"
#include "L3G4200D_new.h"
#include <Wire.h>
#include <TimerOne.h>

#define SampleRate 10000

ADXL345 accel;
L3G4200D gyro;

bool readGyro;
unsigned long pT; //previous time
bool debug_symbol=0;

double Kp=40,Kd=0,Ki=0;
double Ierror=0;
int pwm_speed;
double previous_angle=0;

int Min_speed=0;
AccelRotation accelRot,accelRotL;
double angleF_roll;
double angleF_pitch,threshold_angle=0;
double xi,yi,zi;
double offset;
int temp;

void setup() 
{
  pinMode(7,OUTPUT);
  digitalWrite(7,HIGH); 
  
  Serial.begin(115200);
  Serial.println("Ready.");
  Wire.begin();
  Serial.println("Caliberating Accelerometer");
  accel.init(-1, 0, 8);
  accel.setSoftwareOffset(-0.023, 0, 0.03577027);
  accel.printCalibrationValues(40);
  
  
  digitalWrite(7,LOW);
  delay(2000);
  Serial.println("Caliberating Gyrometer");
  delay(2000);
  
  gyro.init(-0.18891-0.04382, -0.09454-0.05530, -0.31720-0.04951); 
  pT = 0;
  xi=yi=zi=0;
  readGyro = false;
  angleF_roll = angleF_pitch = 0;  
  Timer1.initialize(SampleRate);
  Timer1.attachInterrupt( timerIsr );
  digitalWrite(7,LOW);
  delay(1000);
 

}


void timerIsr()
{
  readGyro = true;
  temp++;
  if(temp==200)
    {
     offset++;
     temp=0;
    }
}



void loop() 
{
  pid_control();
  Serial.print(Kp);
  Serial.print("\t");
  Serial.print(Ki);  
  Serial.print("\t");
  Serial.print(Kd);
  Serial.print("\t");
  
}


void serialEvent() 
{
  while (Serial.available()) 
  {
    char inChar = (char)Serial.read(); 
    if (inChar == '+') 
      Kp+=1;
    else if(inChar == '-')
      Kp-=1;
    else if (inChar == '/') 
      Ki+=0.1;
    else if(inChar == '*')
      Ki-=0.1;
    else if (inChar == '8') 
      Kd+=1;
    else if(inChar == '9')
      Kd-=1;
  }
}




double get_angle()
{
  AccelRotation accelRot;
  accelRot = accel.readPitchRoll();
  AccelG accelG;
  accelG = accel.readAccelG();

  if(readGyro)
  {
    readGyro = false;
    unsigned long cT = micros();
     
    GyroDPS gDPS;
    gDPS = gyro.readGyroDPS();
     
    unsigned long dT = cT - pT;
    pT = cT;
    
      yi = yi + gDPS.y*(dT/1000000.0);
      int  yi2 = (int)yi+offset;
  
   
  //  Serial.print("Accel angle :\t"); 
    accelRot.pitch_2_axis-=90;
  //  Serial.print(accelRot.pitch_2_axis);
  //  Serial.print("\tyi2\t");
  //  Serial.print(yi2);
    angleF_pitch = 0.98*yi2 +0.02*accelRot.pitch_2_axis;
  //  Serial.print("\tNet angle:  ");
    Serial.println(angleF_pitch);
  }
  return angleF_pitch;
}


void pid_control()
{
  double myangle=get_angle();
double error=myangle-threshold_angle;
double dangle=myangle-previous_angle;
previous_angle=myangle;

double Perror=Kp*error;
double Derror=Kd*dangle;

Ierror=Ierror+Ki*error;

if(Ierror>255)
  Ierror=255;
else if(Ierror<-255)
  Ierror=-255;

pwm_speed=(int)(Min_speed+Perror+Ierror+Derror);

if(pwm_speed>255)
  pwm_speed=255;

if(pwm_speed<-255)
  pwm_speed=-255;
  
if(pwm_speed>0)
     move_backward();
else if(pwm_speed<0)
  {
    pwm_speed=abs(pwm_speed);
    move_forward();
  }


   if(debug_symbol==1)
     {
      Serial.print("error:  ");
      Serial.print(error) ;
//      Serial.print("\tPerror:  ");
//      Serial.print(Perror) ;
//      Serial.print("\tIerror:  ");
//      Serial.print(Ierror) ;
//      Serial.print("\tpwm_speed:  ");
//      Serial.println(pwm_speed) ;
     }

analogWrite(9,pwm_speed);
analogWrite(6,pwm_speed);
}



void move_forward()
{
if(debug_symbol==1)
  Serial.println("\nin forward");

digitalWrite(14,HIGH);
digitalWrite(15,LOW);
digitalWrite(12,LOW);
digitalWrite(13,HIGH);
}


void move_backward()
{
if(debug_symbol==1)
  Serial.println("\nin backward");

digitalWrite(14,LOW);
digitalWrite(15,HIGH);
digitalWrite(12,HIGH);
digitalWrite(13,LOW);

}

void move_stop()
{

analogWrite(9,0);
analogWrite(6,0);
//if(debug_symbol==1)
//  Serial.println(fspeed);

digitalWrite(14,HIGH);
digitalWrite(15,HIGH);
digitalWrite(12,HIGH);
digitalWrite(13,HIGH);
}


void setmode()
{
  
  pinMode(7,OUTPUT);  
//M3 with analog 6
  pinMode(12, OUTPUT); 
  pinMode(13, OUTPUT); 

//M4 with analog 9
  pinMode(14, OUTPUT); 
  pinMode(15, OUTPUT); 

//M1  with analog 10
//  pinMode(16, OUTPUT); 
//  pinMode(17, OUTPUT); 
//M2 with analog 11
//  pinMode(18, OUTPUT); 
//  pinMode(19, OUTPUT); 

digitalWrite(12,HIGH);
digitalWrite(13,LOW);

digitalWrite(14,LOW);
digitalWrite(15,HIGH);

//digitalWrite(16,HIGH);
//digitalWrite(17,LOW);

//digitalWrite(18,HIGH);
//digitalWrite(19,LOW);
  
//pinMode(6,OUTPUT);
pinMode(9,OUTPUT);
pinMode(6,OUTPUT);
//pinMode(11,OUTPUT);

//analogWrite(6,80);
analogWrite(9,100);
analogWrite(6,100);
//analogWrite(11,200);
}
