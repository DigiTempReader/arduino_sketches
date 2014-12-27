// TURTLEBOT PROJECT
//AUTHOR :  SAURABH
//DEMO CODE FOR DUAL DC MOTOR DRIVER _ 20A
//WE PURCHASED IT FROM 
//http://robokits.co.in/shop/index.php?main_page=product_info&cPath=73&products_id=342

//PIN CONFIGURATION OF EACH PORT
//1.GND
//2.DIRECTION - 1 FOR BACKWARD ;BY DEFAULT 0 SO FORWARD
//3.PWM SPEED CONTROL
//4.BREAK - 1 FOR BREAK, OTHERWISE 0
//5.5v

void test_driver();
int ledpin=13;
int BRK     = 2;
int MYPWM   = 3;
int DIR = 4; 



void setup()
{
pinMode(BRK,OUTPUT);
pinMode(MYPWM,OUTPUT);
pinMode(DIR,OUTPUT);
pinMode(5,OUTPUT);
pinMode(ledpin,OUTPUT);
test_driver();
}


void loop()
{
digitalWrite(ledpin,HIGH);
delay(100);
digitalWrite(ledpin,LOW);
delay(100);
}


void test_driver()
{

analogWrite(MYPWM,200);

//Go forward
digitalWrite(BRK,LOW);
digitalWrite(DIR,LOW);
delay(3000);

//Go backward
digitalWrite(BRK,LOW);
digitalWrite(DIR,HIGH);
delay(3000);

//NOW STOP
digitalWrite(BRK,HIGH);
delay(3000);
}
