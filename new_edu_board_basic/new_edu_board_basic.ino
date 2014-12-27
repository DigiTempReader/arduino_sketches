/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */

void setup() 
{                
  pinMode(7, OUTPUT); 


//M3 with analog 6
  pinMode(12, OUTPUT); 
  pinMode(13, OUTPUT); 

//M4 with analog 9
  pinMode(14, OUTPUT); 
  pinMode(15, OUTPUT); 
  

//M1  with analog 10
  pinMode(16, OUTPUT); 
  pinMode(17, OUTPUT); 

//M2 with analog 11

  pinMode(18, OUTPUT); 
  pinMode(19, OUTPUT); 


digitalWrite(12,HIGH);
digitalWrite(13,LOW);

digitalWrite(14,LOW);
digitalWrite(15,HIGH);


digitalWrite(16,HIGH);
digitalWrite(17,LOW);

digitalWrite(18,HIGH);
digitalWrite(19,LOW);
  
pinMode(6,OUTPUT);
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);

analogWrite(6,80);
analogWrite(9,200);

analogWrite(10,80);
analogWrite(11,200);
  
}

void loop() {
  digitalWrite(7, HIGH);   // set the LED on
  delay(100);              // wait for a second
  digitalWrite(7, LOW);    // set the LED off
  delay(100);              // wait for a second
}
