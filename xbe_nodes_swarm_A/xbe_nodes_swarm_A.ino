void setup()
{

  Serial.begin(9600);
  pinMode(13,OUTPUT);
Serial.println("NODE 1 reporting!! ");
delay(500);

Serial.println("My staus::");
delay(500);

Serial.println("A#(0-9)");
delay(500);

}


void loop()
{
Serial.println("*B1");
digitalWrite(13,HIGH);
delay(200);
digitalWrite(13,LOW);
delay(200);

}
