#include <Wire.h>

HMC5883L compass;
MagnetometerScaled scaled;
float heading;


int led = 13;

void setup()
{
    pinMode(led,OUTPUT);

  Wire.begin();
  compass = HMC5883L(); //new instance of HMC5883L library
  setupHMC5883L(); //setup the HMC5883L


}


void loop()
{

  heading=getHeading();
  Serial.println(heading);
}


void setupHMC5883L()
{
  //Setup the HMC5883L, and check for errors
  int error=0;  
  float myscale=1.3;
  
  error = compass.SetScale(myscale); //Set the scale of the compass.
  if(error != 0) Serial.println(compass.GetErrorText(error)); //check if there is an error, and print if so

  error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
  if(error != 0) Serial.println(compass.GetErrorText(error)); //check if there is an error, and print if so

}

float getHeading()
{
  //Get the reading from the HMC5883L and calculate the heading
  scaled = compass.ReadScaledAxis(); //scaled values from compass.
  float heading = atan2(scaled.YAxis, scaled.XAxis);

  // Correct for when signs are reversed.
  if(heading < 0) heading += 2*PI;
  if(heading > 2*PI) heading -= 2*PI;

  return heading * RAD_TO_DEG; //radians to degrees
}

