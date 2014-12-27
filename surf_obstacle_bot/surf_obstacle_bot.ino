#include <NewPing.h>

 
#define TRIGGER_PIN  3  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

unsigned int distance;
int pos=0;
void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
pinMode(13, OUTPUT);  
pinMode(12, OUTPUT);  


pinMode(2, OUTPUT);  
pinMode(7, OUTPUT);  

pinMode(4, OUTPUT);  
pinMode(8, OUTPUT);  

pinMode(5, OUTPUT);  
pinMode(6, OUTPUT);  

delay(300);

    pos=100;
    analogWrite(5,pos);
    analogWrite(6,pos);

}

void loop() {  
  
    analogWrite(5,pos);
    analogWrite(6,pos);

  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  distance=uS / US_ROUNDTRIP_CM;
  Serial.print(distance); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");  // wait for a second
  delay(50);
//  keep_moving();
  move_forward();
     if(distance < 20 && distance > 1)
      {
          digitalWrite(12,LOW);
          move_left();
          delay(500);
          move_stop();
          delay(500);
          //new distance
          
  uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  distance=uS / US_ROUNDTRIP_CM;
  delay(50);
  
        if(1<distance<20)
          move_right();
          delay(500);
          move_right();
          delay(500);
          move_stop();
          delay(200); 
      }     
     else
       digitalWrite(12,HIGH);
}


void keep_moving()
{
  if(distance < 20 && distance > 1)
   {
     pos=pos-(20-distance);
     digitalWrite(12,LOW);
     move_stop();
     delay(500);
     move_left();
     delay(200);
     move_stop();
     delay(200);
     unsigned int uS2 = sonar.ping(); // Send ping, get ping time in microseconds (uS).
     distance=uS2 / US_ROUNDTRIP_CM;
     delay(100);
     if(distance < 20 && distance > 1)
      { 
        move_left();
        delay(200);
        move_stop();
        delay(100);

        move_left();
        delay(200);
        move_stop();
        delay(100);

        if(distance < 20 && distance > 1)
          move_left();
          delay(200);
          move_stop();
          delay(500);
      }     
   }
 else if (distance > 100 && distance <190)
   {
     pos=pos+distance/2;
     digitalWrite(12,HIGH);
   }
 else if(distance > 30 && distance < 100)
     pos=100;
     
 else if(distance >190)
     distance = 200;
  
  
}


void move_forward()
{
digitalWrite(7,LOW);
digitalWrite(2,HIGH);
digitalWrite(8,LOW);
digitalWrite(4,HIGH);
}


void move_right()
{
digitalWrite(7,HIGH);
digitalWrite(2,LOW);
digitalWrite(8,LOW);
digitalWrite(4,HIGH);
}


void move_left()
{
digitalWrite(7,LOW);
digitalWrite(2,HIGH);
digitalWrite(8,HIGH);
digitalWrite(4,LOW);
}


void move_back()
{
digitalWrite(7,HIGH);
digitalWrite(2,LOW);
digitalWrite(8,HIGH);
digitalWrite(4,LOW);
}


void move_stop()
{
digitalWrite(2,HIGH);
digitalWrite(7,HIGH);
digitalWrite(4,HIGH);
digitalWrite(8,HIGH);
}

