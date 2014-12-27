/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(13, OUTPUT);     
  pinMode(7,OUTPUT);
  
}

void loop() {
  digitalWrite(13, HIGH);   // set the LED on
  digitalWrite(7, HIGH);   // set the LED on
  
  delay(100);              // wait for a second
  digitalWrite(13, LOW);    // set the LED off
  digitalWrite(7, LOW);    // set the LED off
  
  delay(100);  // wait for a second
}
