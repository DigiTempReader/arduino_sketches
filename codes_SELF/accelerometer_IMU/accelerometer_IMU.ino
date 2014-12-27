#include "ADXL345_new.h"
#include <Wire.h>
ADXL345 accel;
 
void setup()
{
   
  Serial.begin(115200);
   
  Serial.println("Ready.");
  Wire.begin();
 
  accel.init(-1, 0, 8);
  accel.setSoftwareOffset(-0.023, 0, 0.03577027);
  accel.printCalibrationValues(40);
 
}
 
void loop()
{
  //ACCEL
  delay(300);
  
  AccelRotation accelRot;
   
  accelRot = accel.readPitchRoll();
//  Serial.print("{P0|Pitch|127,255,0|");
  Serial.print("Pitcc  :  ");
  Serial.println(accelRot.pitch); 
 // Serial.print("|Roll|255,255,0|");
   Serial.print("Roll :   ");
  Serial.println(accelRot.roll);
//  Serial.println("}");

if(accelRot.pitch+10 > 90)
  Serial.println("move forward");
else if (accelRot.pitch+10 < 90)
  Serial.println("move backward");
}
