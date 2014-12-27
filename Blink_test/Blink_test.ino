/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(13, OUTPUT);    
  pinMode(2, OUTPUT);    
  pinMode(3, OUTPUT);    
  pinMode(4, OUTPUT);    
  pinMode(5, OUTPUT);    
  
}

void loop() {
  digitalWrite(13, HIGH);   // set the LED on
  digitalWrite(2, HIGH);   // set the LED on
  digitalWrite(3, HIGH);   // set the LED on
  digitalWrite(4, HIGH);   // set the LED on
  digitalWrite(5, HIGH);   // set the LED on
 
  delay(500);            // wait for a second
  digitalWrite(13, LOW);    // set the LED off
  digitalWrite(2, LOW);    // set the LED off
  digitalWrite(3, LOW);    // set the LED off
  digitalWrite(4, LOW);    // set the LED off
  digitalWrite(5, LOW);    // set the LED off
  
  delay(500);              // wait for a second
}
