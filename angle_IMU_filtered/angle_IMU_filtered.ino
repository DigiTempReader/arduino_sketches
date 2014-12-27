#include <Wire.h>
#include <TimerOne.h>
#include "ADXL345_new.h"
#include "L3G4200D_new.h"
//Gyro sampling rate in micro seconds
#define SampleRate 10000
ADXL345 accel;
L3G4200D gyro;
bool readGyro;
double angleF_roll;
double angleF_pitch,threshold_pitch=0;
unsigned long pT; //previous time
bool debug_symbol=0;
double xi,yi,zi;
int temp=0;
double offset=0;


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
  if(temp==215)
    {
     offset++;
     temp=0;
    }
}
 
void loop()
{
  get_angle();
}

void get_angle()
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

    Serial.print("Accel angle :\t"); 
    Serial.print(accelRot.pitch_2_axis);
    //Serial.print("\tGyro Angle :\t");
   // Serial.print(yi);
  //  Serial.print("\tOffset\t");
  //  Serial.print(offset);
    Serial.print("\tyi2\t");
    Serial.print(yi2);
    angleF_pitch = 0.95*yi2 +0.05*accelRot.pitch_2_axis;
    Serial.print("\tNet angle\t");
    Serial.println(angleF_pitch);

  }
  //return angleF_pitch;
}
