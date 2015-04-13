void setup() 
{
  Serial.begin(9600);
  Serial.print("starting");
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
pinMode(12,OUTPUT);

digitalWrite(8,LOW);
digitalWrite(9,LOW);
digitalWrite(10,LOW);
digitalWrite(11,LOW);
digitalWrite(12,LOW);
}


void loop()
{
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

 digitalWrite(8,LOW);
 digitalWrite(9,LOW);
 digitalWrite(10,LOW);
 digitalWrite(11,LOW);
 digitalWrite(12,HIGH); 
 delay(2000);
 
 digitalWrite(8,HIGH);
 digitalWrite(9,HIGH);
 digitalWrite(10,HIGH);
 digitalWrite(11,HIGH);
 digitalWrite(12,HIGH);
 delay(5000);
 
}

