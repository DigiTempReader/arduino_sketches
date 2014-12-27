/*
Switches ON and OFF a LED at a Preset Time of Hour based on RTC
 */

#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 RTC;

#define ON_HOUR 13// Hour of the On Time
#define ON_MIN 0// Minute of the On Time
#define OFF_HOUR 13// Hour of the Off Time
#define OFF_MIN 1// Minute of the Off Time

void setup()
{
  Serial.begin(9600);
  pinMode(13,OUTPUT); // Pin of the LED to be Switched ON / OFF
  Wire.begin();
  RTC.begin();
  RTC.adjust(DateTime("DEC 31 2011","12:59:45")); // Setting the time to a fixed value. If you want to use the system time comment this line and use the option below
  // following line sets the RTC to the date & time this sketch was compiled
  // RTC.adjust(DateTime(__DATE__, __TIME__)); //uncomment this line to set time to system time

}

void loop()
{
  DateTime now = RTC.now();// Getting the current Time and storing it into a DateTime object

  if(now.hour()==ON_HOUR && now.minute()==ON_MIN)
    digitalWrite(13,HIGH);
  if(now.hour()==OFF_HOUR && now.minute()==OFF_MIN)
    digitalWrite(13,LOW);
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  delay(1000);

}



