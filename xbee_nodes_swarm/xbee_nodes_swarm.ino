void setup()
{

  Serial.begin(9600);
  pinMode(7,OUTPUT);
Serial.println("NODE 2 reporting!! ");
delay(500);

Serial.println("My staus::");
delay(500);

Serial.println("B#(0-9)");
delay(500);

}


void loop()
{
Serial.println("*B1");
digitalWrite(13,HIGH);
delay(100);
digitalWrite(13,LOW);
delay(100);

}
