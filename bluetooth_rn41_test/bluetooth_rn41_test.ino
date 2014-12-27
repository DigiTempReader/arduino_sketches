
void setup()
{
Serial.begin(115200);
pinMode(13,OUTPUT);
}

void loop()
{
  
char inchar='\0';
if(Serial.available())
  {
   inchar=(char)Serial.read();
   if(inchar == '1')
    digitalWrite(13,HIGH);
   else
    digitalWrite(13,LOW);
  }
}


