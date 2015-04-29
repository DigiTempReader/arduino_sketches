//These four relays are ACTIVE HIGH----------
int src_select_battery_relay=2;
int src_select_load_relay=3;
int src_select_solar_relay=5;
int fan_relay=4;
//-------------------------------------------


//These five load relays are Active LOW------
int load_resistor_5ohm   = 12;
int load_resistor_10ohm  = 9;
int load_resistor_20ohm  =10;
int load_resistor_40ohm  =8;
int load_resistor_80ohm  =11;
//-------------------------------------------
unsigned int net_adc_panel,net_adc_bat,net_adc_load;
float net_adc_current;
float current;
int average_no=10;
float voltage_coff=15.0/1024.0;

unsigned int adc_bat;
unsigned int adc_panel;
unsigned int adc_load;
unsigned int adc_current;



int i=0;
//-------------------------------------------

void setup()
{
        pinMode(src_select_battery_relay,OUTPUT);
        pinMode(src_select_load_relay,OUTPUT);
        pinMode(src_select_solar_relay,OUTPUT);
        pinMode(fan_relay,OUTPUT);

        pinMode(load_resistor_80ohm,OUTPUT);
        pinMode(load_resistor_40ohm,OUTPUT);
        pinMode(load_resistor_20ohm,OUTPUT);
        pinMode(load_resistor_10ohm,OUTPUT);
        pinMode(load_resistor_5ohm,OUTPUT);
        
        
        digitalWrite(src_select_battery_relay,LOW);
        digitalWrite(src_select_load_relay,LOW);
        digitalWrite(fan_relay,HIGH);
        digitalWrite(src_select_solar_relay,LOW);

        digitalWrite(load_resistor_5ohm,LOW);
        digitalWrite(load_resistor_10ohm,LOW);
        digitalWrite(load_resistor_20ohm,LOW);
        digitalWrite(load_resistor_40ohm,LOW);
        digitalWrite(load_resistor_80ohm,HIGH);
        pinMode(13,OUTPUT);
        Serial.begin(9600);      
}

void loop()
{
 // digitalWrite(13,HIGH);
  for (i=0;i<average_no;i++)
  { 
    adc_current = analogRead(A4);
    current = adc_current * (5.0 / 1023.0);
    adc_bat = analogRead(A0);
    delay(10);
    adc_panel = analogRead(A1);
    delay(10);
    adc_load = analogRead(A2);
    delay(10);
    
    net_adc_bat     += adc_bat;
    net_adc_panel   += adc_panel;
    net_adc_load    += adc_load;
    net_adc_current += current;
    
  }
   net_adc_bat      /=  average_no;
   net_adc_panel    /=  average_no;
   net_adc_load     /=  average_no;
   net_adc_current  /=  average_no;
   
   
  // print out the value you read:

  Serial.print("Voltage_battery --");
  Serial.print(voltage_coff*net_adc_bat);
  Serial.print("\t\t");
  Serial.print("Voltage_Panel --");
  Serial.print(voltage_coff*net_adc_panel);
  Serial.print("\t\t");
  Serial.print("Voltage_LOAD --");
  Serial.print(voltage_coff*net_adc_load);
  Serial.print("\t\t");
  Serial.print("Current --");
  Serial.println(net_adc_current);
  
  delay(150);        // delay in between reads for stability
  digitalWrite(13,LOW);
  delay(200);  

}

