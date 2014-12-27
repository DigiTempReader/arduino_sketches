/*
 Fading
 
 This example shows how to fade an LED using the analogWrite() function.
 
 The circuit:
 * LED attached from digital pin 9 to ground.
 
 Created 1 Nov 2008
 By David A. Mellis
 modified 30 Aug 2011
 By Tom Igoe
 
 http://arduino.cc/en/Tutorial/Fading
 
 This example code is in the public domain.
 
 */


int ledPin = 9;    // LED connected to digital pin 9
int motor_pwm_value=0;

void setup()  { 
  
   Serial.begin(9600);
   
} 


void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    
    if (inChar == '+') 
     {
     if(motor_pwm_value > 110 && motor_pwm_value < 140)
       motor_pwm_value+=1;
     else
       motor_pwm_value+=10;
       digitalWrite(13,HIGH);
     }
    if(inChar == '-')
      {
     if(motor_pwm_value > 110 && motor_pwm_value < 140)
       motor_pwm_value-=1;
     else
       motor_pwm_value-=10;
       digitalWrite(13,LOW);
      }
  }
}



void loop()  { 
    // delay(500);
     analogWrite(9,motor_pwm_value);
   Serial.print("value of motor_pwm is\t");
   Serial.println(motor_pwm_value, DEC);
  
} 

 



