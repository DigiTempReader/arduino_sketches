#include <Servo.h> 

Servo thumb;  // create servo object to control a servo 
Servo index;  // create servo object to control a servo 
Servo middle;  // create servo object to control a servo 
Servo ring;  // create servo object to control a servo 
Servo little;  // create servo object to control a servo 
             
int thumb_p=15;// variable to store the servo position
int ring_p=165;
int middle_p=165;
int index_p=15;
int little_p=165;

 
void setup() 
{ 
    thumb.attach(3);  // attaches the servo on pin 9 to the servo object
    index.attach(5);  // attaches the servo on pin 9 to the servo object
    middle.attach(6);  // attaches the servo on pin 9 to the servo object
    ring.attach(9);  // attaches the servo on pin 9 to the servo object
    little.attach(10);  // attaches the servo on pin 9 to the servo object
    
Serial.begin(9600);
    thumb.write(thumb_p);
    index.write(index_p);              // tell servo to go to position in variable 'pos' 
    middle.write(middle_p);              // tell servo to go to position in variable 'pos' 
    ring.write(ring_p);              // tell servo to go to position in variable 'pos' 
    little.write(little_p); 
    
    Serial.println("initial");
        
    Serial.println(15);
    Serial.println(165);
    Serial.println(165);
    Serial.println(165);
    Serial.println(165);

} 
 
void loop() 
{ 
} 
void serialEvent() {
  while (Serial.available())
  {
      // get the new byte:
      char inChar = (char)Serial.read(); 
      switch(inChar)
      {
        case '1': thumbOpen();
                  break;
        case '2': thumbClose();
                  break;
        case '3': indexOpen();
                  break;
        case '4': indexClose();
                  break;
        case '5': middleOpen();
                  break;
        case '6': middleClose();
                  break;
        case '7': ringOpen();
                  break;
       case '8': ringClose();
                 break;
       case '9': littleOpen();
                 break;
       case '0': littleClose();
                 break;
       default: 
                 Serial.println("press the correct key");
               break;
      }
    }
}
void thumbOpen()
{
  thumb_p+=1;
  thumb.write(thumb_p);
  Serial.println("thumb open");
  Serial.println(thumb_p);
}

void thumbClose()
{
  thumb_p -=1;
  thumb.write(thumb_p);
  Serial.println("thumb close");
  Serial.println(thumb_p);
}
void indexOpen()
{
  index_p+=1;
  index.write(index_p);
  Serial.println("index open");
  Serial.println(index_p);
}

void indexClose()
{
  index_p -=1;
  thumb.write(index_p);
  Serial.println("index close");
  Serial.println(index_p);
}
void middleOpen()
{
  middle_p+=1;
  thumb.write(middle_p);
  Serial.println("middle open");
  Serial.println(middle_p);
}

void middleClose()
{
  middle_p -=1;
  middle.write(middle_p);
  Serial.println(middle_p);
}
void ringOpen()
{
  ring_p+=1;
  ring.write(ring_p);
  Serial.println("ring open");
  Serial.println(ring_p);
}

void ringClose()
{
  ring_p -=1;
  ring.write(ring_p);
  Serial.println("ring close");
  Serial.println(ring_p);
}
void littleOpen()
{
  little_p+=1;
  little.write(little_p);
  Serial.println("little open");
  Serial.println(little_p);
}

void littleClose()
{
  little_p -=1;
  little.write(little_p);
  Serial.println("little close");
  Serial.println(little_p);
}

