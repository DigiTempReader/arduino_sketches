


void setup() {                
  pinMode(13, OUTPUT);  
  DDRC = 0xff;
  
}

void loop() {
  digitalWrite(13, HIGH);   // set the LED on
   PORTC =0xff;
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // set the LED off
  PORTC =0x00; 
  delay(1000);              // wait for a second
}


