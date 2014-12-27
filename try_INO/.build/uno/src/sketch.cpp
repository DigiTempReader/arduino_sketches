#include <Arduino.h>

void setup();
void loop();
#line 1 "src/sketch.ino"
void setup()
{
    Serial.begin(9600);
}

void loop()
{
    Serial.println(millis());
    delay(1000);
}
