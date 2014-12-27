#include <PinChangeInt.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>

ros::NodeHandle  nh;

std_msgs::String str_msg;
std_msgs::Int16 myint1_16;
std_msgs::Int16 myint2_16;

ros::Publisher chatter1("chatter1", &str_msg);
ros::Publisher chatter2("chatter2", &myint1_16);
ros::Publisher chatter3("chatter3", &myint2_16);

char hello[13] = "hello world!";


////////odometer///////////////////////

int left1=8;//to be inverted later
int left2=9;
int right1=10;
int right2=11;
volatile int leftlastEncoded = 0;
volatile long leftencoderValue = 0;
long leftlastencoderValue = 0;
volatile int rightlastEncoded = 0;
volatile long rightencoderValue = 0;
long rightlastencoderValue = 0;

volatile int leftRotation = 0;
volatile int rightRotation = 0;
volatile float totalRotation=0;
volatile float theta=0;
int x=0;
int y=0;
volatile float distance=0.0;
int wheelBase=23;
/*****************************************************
**multiplication_factor= 2pi * r / 16

2*3.14*(2*2.54)/16=1.9939

avg_rotation=(left+right)/2
distance=avg rotation * multiplication_factor

or 

distance=total_rotation * new multiplication

 new multiplication_factor=1.9939/2=0.99695
*****************************************************/
const float multiplication_factor=0.99695;
volatile uint8_t rotaryFlag=LOW;//global flag for rotary

//int rightlastMSB = 0;
//int rightlastLSB = 0;
/////////////////////////////////////////
#include <Wire.h>
#include <HMC5883L.h>


HMC5883L compass;
MagnetometerScaled scaled;
float heading;


//////////rc ////////////////////////////

int led = 7;
void setup()
{
    pinMode(led,OUTPUT);
    setup_rotaryEncoder();

  Wire.begin();
  compass = HMC5883L(); //new instance of HMC5883L library
  setupHMC5883L(); //setup the HMC5883L

  nh.initNode();
  nh.advertise(chatter1);
  nh.advertise(chatter2);
  nh.advertise(chatter3);

}

void setup_rotaryEncoder()
{
  leftencoderValue=0;
  rightencoderValue=0;
  pinMode(left1, INPUT); 
  pinMode(left2, INPUT);
  pinMode(right1, INPUT); 
  pinMode(right2, INPUT);
  
  digitalWrite(left1, HIGH); //turn pullup resistor on
  digitalWrite(left2, HIGH); //turn pullup resistor on
  digitalWrite(right1, HIGH); //turn pullup resistor on
  digitalWrite(right2, HIGH); //turn pullup resistor on
  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 

  PCintPort::attachInterrupt(left1,left_updateencoder,CHANGE); 
  PCintPort::attachInterrupt(left2,left_updateencoder,CHANGE);
  PCintPort::attachInterrupt(right1,right_updateencoder,CHANGE); 
  PCintPort::attachInterrupt(right2,right_updateencoder,CHANGE);
}


void loop()
{
  volatile static uint8_t update_rotaryFlag;

  str_msg.data = hello;  

  heading=getHeading();
  myint1_16.data=heading;  
  myint2_16.data=distance;
  
  
  chatter1.publish( &str_msg );
  chatter2.publish( &myint1_16 );
  chatter3.publish( &myint2_16 );
  
  nh.spinOnce();
 // delay(1000);  
    
    if(rotaryFlag)
    
    {
       noInterrupts(); 
       update_rotaryFlag=rotaryFlag;
       leftRotation = (leftencoderValue/16);
       rightRotation = (rightencoderValue/16);
     /*
         Serial.print('\n');
        Serial.print(leftencoderValue);
        Serial.print("\t");
        Serial.println(rightencoderValue);
        Serial.print(leftRotation);
        Serial.print("\t");
        Serial.println(rightRotation);
      */
      
//          totalRotation = (leftencoderValue + rightencoderValue);
            totalRotation = 2*rightencoderValue;
  
        //  theta=(leftRotation-rightRotation)/wheelBase;
          distance=totalRotation * multiplication_factor;
          
          

          //x= distance * sin(theta);
          //y= distance * cos(theta);
          
//          Serial.println(distance);
//          Serial.println(theta);
//        Serial.print("\n");
//       */  
  
  
          update_rotaryFlag=0;
          rotaryFlag=0;
         interrupts();
    }
       
       

    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);               // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    delay(100);  

}


void left_updateencoder()
{
  int leftMSB = digitalRead(left1); //MSB = most significant bit
  int leftLSB = digitalRead(left2); //LSB = least significant bit
  if(leftMSB==0) 
        leftMSB=1;
    else 
        leftMSB=0;
  int leftencoded = (leftMSB << 1) |leftLSB; //converting the 2 pin value to single number
  int leftsum  = (leftlastEncoded << 2) | leftencoded; //adding it to the previous encoded value
  
  if (leftsum == 0b1101 || leftsum == 0b0100 || leftsum == 0b0010 || leftsum == 0b1011) 
     leftencoderValue ++;
  if (leftsum == 0b1110 || leftsum == 0b0111 || leftsum == 0b0001 || leftsum == 0b1000) 
     leftencoderValue --;

  leftlastEncoded = leftencoded; //store this value for next time
  
  rotaryFlag=1;
// Serial.print("left \t");
 //Serial.println(leftencoderValue);  
}
void right_updateencoder()
{
  int rightMSB = digitalRead(right1); //rightMSB = most significant bit
  int rightLSB = digitalRead(right2); //rightLSB = least significant bit

  int rightencoded = (rightMSB << 1) |rightLSB; //converting the 2 pin value to single number
  int rightsum  = (rightlastEncoded << 2) | rightencoded; //adding it to the previous encoded value

  if(rightsum == 0b1101 || rightsum == 0b0100 || rightsum == 0b0010 || rightsum == 0b1011) rightencoderValue ++;
  if(rightsum == 0b1110 || rightsum == 0b0111 || rightsum == 0b0001 || rightsum == 0b1000) rightencoderValue --;

  rightlastEncoded = rightencoded; //store this value for next time
  rotaryFlag=1;
 // Serial.print("\n\t");
 // Serial.println(rightencoderValue);
}



void setupHMC5883L()
{
  //Setup the HMC5883L, and check for errors
  int error=0;  
  float myscale=1.3;
  /*
  error = compass.SetScale(myscale); //Set the scale of the compass.
  if(error != 0) Serial.println(compass.GetErrorText(error)); //check if there is an error, and print if so

  error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
  if(error != 0) Serial.println(compass.GetErrorText(error)); //check if there is an error, and print if so
 */
 
}

float getHeading()
{
  //Get the reading from the HMC5883L and calculate the heading
  scaled = compass.ReadScaledAxis(); //scaled values from compass.
  float heading = atan2(scaled.YAxis, scaled.XAxis);

  // Correct for when signs are reversed.
  if(heading < 0) heading += 2*PI;
  if(heading > 2*PI) heading -= 2*PI;

  return heading * RAD_TO_DEG; //radians to degrees
}

