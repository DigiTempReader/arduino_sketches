/*

The circuit:
 * LCD RS pin to digital pin 2
 * LCD Enable pin to digital pin 3
 * LCD D4 pin to digital pin 4
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 6
 * LCD D7 pin to digital pin 7
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
*/

/*
  SD card datalogger

 * analog sensors on analog ins 0, 1, and 2

 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 10
*/


//#include <LiquidCrystal.h>
#include <Wire.h>
#include <SD.h>
const int chipSelect = 10;


void setup() 
{
  Serial.begin(9600);                               //UART setup, baudrate = 9600bps
  Serial.print("initiallisining...\n");                

  pinMode(13,OUTPUT); // Pin of the LED to be Switched ON / OFF

  Wire.begin();
  Serial.print("Initializing SD card...");
  pinMode(10, OUTPUT);
  
  if (!SD.begin(chipSelect))
  {
    Serial.println("Card failed, or not present");
    return;
  }
    Serial.println("card initialized.");
    delay(4000);
}



void loop() 
{
//write_sd();
}


/*
void write_sd()
{
//****************************************SD CARD WORKING***************************************
String dataString = "";

  // read three sensors and append to the string:
  for (int analogPin = 0; analogPin < 3; analogPin++) 
  {
    int sensor = analogRead(analogPin);
    dataString += String(sensor);
    if (analogPin < 2) 
    {
      dataString += ","; 
    }
  }
  
   dataString += String("\tLPG:"); 
   dataString += String(MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_LPG) );
   dataString += String( "ppm" );

   dataString += String("\tCO:"); 
   dataString += String(MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_CO) );
   dataString += ( "ppm" );
   
   dataString += String("\tSMOKE:"); 
   dataString += String(MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_SMOKE) );
   dataString += String( "ppm" );
  
   delay(200);
  
  
  
lcd.clear();
lcd.setCursor(0,0);
lcd.print("writing in SD");
delay(2000);

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }  
  // if the file isn't open, pop up an error:
  else
  {
    Serial.println("error opening datalog.txt");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("File I/O error");
    delay(2000);
  }

}
*/


