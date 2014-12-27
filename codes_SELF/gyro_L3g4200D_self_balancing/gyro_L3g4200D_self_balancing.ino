//Gyro sampling rate in micro seconds
#include <L3G4200D_new.h>
#include <Wire.h>
#include <TimerOne.h>

#define SampleRate 10000
L3G4200D gyro;
bool readGyro;
double xi,yi,zi;

unsigned long pT;

void setup()
{
   
  Serial.begin(115200);
   
  Serial.println("Ready.");
  Wire.begin();
  gyro.init(-0.18891-0.04382, -0.09454-0.05530, -0.31720-0.04951); //Don’t  use my calibration values
  pT = 0;
   xi = yi = zi = 0;
  readGyro = false;
  Timer1.initialize(SampleRate);
  Timer1.attachInterrupt( timerIsr );
}


void timerIsr()
{
  readGyro = true;
}


void loop()
{
//GYRO
  if(readGyro)
  {
    readGyro = false;
    unsigned long cT = micros();
     
    GyroDPS gDPS;
    gDPS = gyro.readGyroDPS();
     
    unsigned long dT = cT - pT;
    pT = cT;
     
 //   Serial.print("{P2|X|255,0,0|");
//    Serial.print("gDPS's x value :\t");
 //   Serial.print(gDPS.x);
     
     
//    Serial.print("|Y|0,255,0|");
//    Serial.print("\tY value :\t");
//    Serial.print(gDPS.y);
     
//    Serial.print("|Z|0,0,255|");
//    Serial.print("\tZ value :\t");
//    Serial.println(gDPS.z);
//    Serial.println("}");
     
     
//    Serial.print("{P4|Roll|0,255,0|");
//    Serial.print("Roll :\t");
//    xi = xi + gDPS.x*(dT/1000000.0);
//    Serial.print(xi);
    yi = yi + gDPS.y*(dT/1000000.0);
    Serial.print("Pitch :\t");
//    Serial.print("|Pitch|255,0,0|");
    Serial.println(yi);
     
//    zi = zi + gDPS.z*(dT/1000000.0);
//    Serial.print("|Yaw|100,100,255|");
//    Serial.print("\tYaw :\t");
//    Serial.println(zi);
//    Serial.println("}");  
// delay(10);
  }
  //END GYRO
}
