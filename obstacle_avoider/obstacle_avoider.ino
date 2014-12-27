#include <NewPing.h>
#include <edu_motor.h>
#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
Motor motor1(16,17);                // a maximum of eight servo objects can be created 
Motor motor2(18,19);

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

unsigned int left_dis=0;
unsigned int right_dis=0;

void setup() 
{ 
    myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
    Serial.begin(115200);
//  motor1.setspeed(10);
//  motor2.setspeed(10);
motor1.forward();
motor2.forward();
} 
 
 
void loop() 
{ 
  delay(100);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  unsigned int dis=uS / US_ROUNDTRIP_CM;
  Serial.print("Ping: ");
  Serial.print(dis); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm"); 
  
  if(dis > 1 && dis < 15)
    {
    motor1.halt();
    motor2.halt();
    //turning left of servo
    myservo.write(2);
    uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
    left_dis=uS / US_ROUNDTRIP_CM;
    Serial.println(left_dis);
    delay(100);
      if( left_dis > 1 && left_dis <15)
        {
          myservo.write(175);
          uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
          right_dis=uS / US_ROUNDTRIP_CM;
          Serial.println(right_dis);
          delay(500);
          if(right_dis > 1 && right_dis < 15)
            {
             motor1.forward();
             motor2.backward();
             delay(500);
            }
        }
       else
        {
         motor1.backward();
         motor2.forward();
         delay(1000); 
        } 
    delay(200);
    }

 else 
   {
     myservo.write(90);
     motor1.forward();
     motor2.forward();
   }
   delay(10);
} 
