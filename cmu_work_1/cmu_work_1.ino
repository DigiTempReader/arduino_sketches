
unsigned int vol_panel;
unsigned int vol_bat;
unsigned int current;
int i;
int averager=10;

void setup() 
{
  Serial.begin(9600);
  Serial.print("starting");
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
pinMode(12,OUTPUT);


digitalWrite(2,HIGH);
digitalWrite(3,HIGH);
digitalWrite(4,LOW);
digitalWrite(5,LOW);
digitalWrite(6,LOW);
digitalWrite(7,LOW);
digitalWrite(8,LOW);
digitalWrite(9,LOW);
digitalWrite(10,LOW);
digitalWrite(11,LOW);
digitalWrite(12,LOW);

digitalWrite(3,LOW);
digitalWrite(2,LOW);

}

void loop() 
{
  vol_panel=0;
  vol_bat=0;
  current=0;
  i=0;
  for(i=0;i<averager;i++)
    {
     vol_panel += analogRead(A0);
     vol_bat   += analogRead(A1);
     current   += analogRead(A2);
    }
    vol_panel /= averager;
    vol_bat   /= averager;
    current   /= averager;
   
  Serial.print("Voltage -- ");
  Serial.print(vol_panel);
  Serial.print("\t\tVoltage -- ");
  Serial.print(vol_bat);
  Serial.print("\t\tCurrent -- ");
  Serial.println(current);
  
  delay(300);
  digitalWrite(8,HIGH);
  delay(3000);
  digitalWrite(8,LOW);  
  delay(3000);
  
  digitalWrite(9,HIGH);
  delay(3000);
  digitalWrite(9,LOW);  
  delay(3000);
  
  digitalWrite(10,HIGH);
  delay(3000);
  digitalWrite(10,LOW);  
  delay(3000);
  digitalWrite(11,HIGH);
  delay(3000);
  digitalWrite(11,LOW);  
  delay(3000);
  
  digitalWrite(12,HIGH);
  delay(3000);
  digitalWrite(12,LOW);  
  delay(3000);
 
 digitalWrite(8,HIGH);
 digitalWrite(9,HIGH);
 digitalWrite(10,HIGH);
 digitalWrite(11,HIGH);
 digitalWrite(12,HIGH);
 
 delay(5000);
 
 digitalWrite(8,LOW);
 digitalWrite(9,LOW);
 digitalWrite(10,LOW);
 digitalWrite(11,LOW);
 digitalWrite(12,LOW);
 
 delay(5000);
}
  
  
void serialEvent() 
  {
    while (Serial.available())
    {
      // get the new byte:
      char inChar = (char)Serial.read(); 
      if (inChar == '1') 
      {
        digitalWrite(8,~digitalRead(8));
      }
      if (inChar == '2') 
      {
        digitalWrite(9,~digitalRead(9));
      } 
      if (inChar == '3') 
      {
        digitalWrite(10,~digitalRead(10));
      } 
      if (inChar == '4') 
      {
        digitalWrite(11,~digitalRead(11));
      } 
      if (inChar == '5') 
      {
        digitalWrite(12,~digitalRead(12));
      } 
 
  
    }
  }
