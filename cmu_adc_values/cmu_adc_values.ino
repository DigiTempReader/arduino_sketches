
unsigned int net_adc_current,net_adc_panel,net_adc_bat;
int average_no=10;

int i=0;
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  
}

// the loop routine runs over and over again forever:
void loop()
{
  digitalWrite(13,HIGH);
  // read the input on analog pin 0:
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
  Serial.print(net_adc_bat);
  Serial.print("\t\t");
  Serial.print("Voltage_Panel --");
  Serial.print(net_adc_panel);
  Serial.print("\t\t");
  Serial.print("Current --");
  Serial.println(net_adc_current);
  
  delay(150);        // delay in between reads for stability
  digitalWrite(13,LOW);
  delay(200);
}
