//These four relays are ACTIVE HIGH----------
int src_select_battery_relay=2;
int src_select_load_relay=3;
int src_select_solar_relay=5;
int fan_relay=4;
//-------------------------------------------


//These five load relays are Active LOW------
int load_resistor_5=12;
int load_resistor_10=9;
int load_resistor_20=10;
int load_resistor_40=8;
int load_resistor_80=11;
//-------------------------------------------
unsigned int net_adc_current,net_adc_panel,net_adc_bat;
int average_no=10;
float voltage_coff=15.0/1024.0;


int i=0;
//-------------------------------------------

void setup()
{
        pinMode(src_select_battery_relay,OUTPUT);
        pinMode(src_select_load_relay,OUTPUT);
        pinMode(src_select_solar_relay,OUTPUT);
        pinMode(fan_relay,OUTPUT);

        pinMode(load_resistor_80,OUTPUT);
        pinMode(load_resistor_40,OUTPUT);
        pinMode(load_resistor_20,OUTPUT);
        pinMode(load_resistor_10,OUTPUT);
        pinMode(load_resistor_5,OUTPUT);
        
        
        digitalWrite(src_select_battery_relay,LOW);
        digitalWrite(src_select_load_relay,LOW);
        digitalWrite(fan_relay,HIGH);
        digitalWrite(src_select_solar_relay,LOW);

        digitalWrite(load_resistor_5,HIGH);
        digitalWrite(load_resistor_10,HIGH);
        digitalWrite(load_resistor_20,HIGH);
        digitalWrite(load_resistor_40,HIGH);
        digitalWrite(load_resistor_80,LOW);
        pinMode(13,OUTPUT);
        Serial.begin(9600);      
}

void loop()
{
  digitalWrite(13,HIGH);
  for (i=0;i<average_no;i++)
  { 
    unsigned int adc_bat = analogRead(A0);
    unsigned int adc_panel = analogRead(A1);
    unsigned int adc_current = analogRead(A2);
    
    net_adc_bat     += adc_bat;
    net_adc_panel   += adc_panel;
    net_adc_current += adc_current;
    
  }
   net_adc_bat  /=  average_no;
   net_adc_panel  /=  average_no;
   net_adc_current  /=  average_no;
   
   
  // print out the value you read:
  Serial.print("Voltage_battery --");
  Serial.print(voltage_coff*net_adc_bat);
  Serial.print("\t\t");
  Serial.print("Current --");
  Serial.println(net_adc_current);
  
  delay(150);        // delay in between reads for stability
  digitalWrite(13,LOW);
  delay(200);  

}

