#include <Arduino.h>

void setup();
void loop();
#line 1 "src/sketch.ino"
//These four relays are ACTIVE HIGH----------
int src_select_battery_relay=2;
int src_select_panel_relay=3;
int src_select_load_relay=4;
int fan_relay=5;
//-------------------------------------------


//These five load relays are Active LOW------
int load_resistor_5=8;
int load_resistor_10=9;
int load_resistor_20=10;
int load_resistor_40=11;
int load_resistor_80=12;
//-------------------------------------------


void setup()
{
	pinMode(2,OUTPUT);
	pinMode(3,OUTPUT);
	pinMode(4,OUTPUT);
	pinMode(5,OUTPUT);

	pinMode(8,OUTPUT);
	pinMode(9,OUTPUT);
	pinMode(10,OUTPUT);
	pinMode(11,OUTPUT);
	pinMode(12,OUTPUT);
}

void loop()
{
	digitalWrite(2,HIGH);
	digitalWrite(3,HIGH);
	digitalWrite(4,HIGH);
	digitalWrite(5,HIGH);
	
	digitalWrite(8,LOW);
	digitalWrite(9,LOW);
	digitalWrite(10,LOW);
	digitalWrite(11,LOW);
	digitalWrite(12,LOW);
}



