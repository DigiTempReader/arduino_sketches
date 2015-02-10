float adc_zero = 512;
float mean_voltage_acc = 0;
float voltage_rms = 0;

float scaling_constant=0.030;

float volt_per_division=(5/1024);
int samples_num = 200;

float adc_raw = 0;

void setup()
{
 Serial.begin(9600);
}


void loop()
{
unsigned long voltage_acc = 0;
float net_volt=0;
float net_current=0;

for(int i=0; i<samples_num; i++) 
 {  
 adc_raw = analogRead(0);
 voltage_acc += (adc_raw - adc_zero) * (adc_raw - adc_zero);  //rms
 }
//Serial.print(adc_raw);
//Serial.print("\t");
mean_voltage_acc=voltage_acc/samples_num;
voltage_rms=sqrt(mean_voltage_acc);
//Serial.print(voltage_rms);
//Serial.print("\t");
//net_volt=volt_per_division*voltage_rms;
net_volt=(5*voltage_rms)/1024;
//Serial.print(net_volt);
//Serial.print("\t");
net_current=net_volt/scaling_constant;
Serial.print("Current Value   :");
Serial.println(net_current);
}
