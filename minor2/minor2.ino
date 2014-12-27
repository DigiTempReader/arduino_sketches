#include <Servo.h> 

Servo thumb;  // create servo object to control a servo 
Servo index;  // create servo object to control a servo 
Servo middle;  // create servo object to control a servo 
Servo ring;  // create servo object to control a servo 
Servo little;  // create servo object to control a servo 
Servo little2;

int thumb_p=141;// variable to store the servo position
int index_p=51;
int middle_p=135;
int ring_p=133;
int little_p=115;

unsigned char all_open_flag=0;
unsigned char all_close_flag=0;
unsigned char show_one_flag=0;
unsigned char show_two_flag=0;
unsigned char show_three_flag=0;
unsigned char show_four_flag=0;
unsigned char thumb_open_flag=0;
unsigned char thumb_close_flag=0;

unsigned char index_open_flag=0;
unsigned char index_close_flag=0;

unsigned char middle_open_flag=0;
unsigned char middle_close_flag=0;

unsigned char ring_open_flag=0;
unsigned char ring_close_flag=0;

unsigned char little_open_flag=0;
unsigned char little_close_flag=0;



void setup() 
{ 
    thumb.attach(3);  // attaches the servo on pin 9 to the servo object
    index.attach(5);  // attaches the servo on pin 9 to the servo object
    middle.attach(6);  // attaches the servo on pin 9 to the servo object
    ring.attach(9);  // attaches the servo on pin 9 to the servo object
    little.attach(10);  // attaches the servo on pin 9 to the servo object
    little2.attach(11);
    
    Serial.begin(115200);
//all open
    thumb.write(thumb_p);
    index.write(index_p);              // tell servo to go to position in variable 'pos' 
    middle.write(middle_p);              // tell servo to go to position in variable 'pos' 
    ring.write(ring_p);              // tell servo to go to position in variable 'pos' 
    little.write(little_p); 
    little2.write(little_p); 
    
    Serial.println("initial");
        
    Serial.println(thumb_p);
    Serial.println(index_p);
    Serial.println(middle_p);
    Serial.println(ring_p);
    Serial.println(little_p);
    Serial.println(little_p);

} 
 
void loop() 
{ 
if(all_open_flag==1)
  all_open();
if(all_close_flag==1)
  all_close();
if(show_one_flag==1)
  show_one();
if(show_two_flag==1)
  show_two();
if(show_three_flag==1)
  show_three();
if(show_four_flag==1)
  show_four();
  
if(thumb_open_flag==1)
  {thumb_open();  thumb_open_flag=0;}
if(thumb_close_flag==1)
  {thumb_close();  thumb_close_flag=0;}

if(index_open_flag==1)
  {index_open();    index_open_flag=0;}
if(index_close_flag==1)
  {index_close();    index_close_flag=0;}


if(middle_open_flag==1)
  {middle_open();    middle_open_flag=0;}
if(middle_close_flag==1)
  {middle_close();    middle_close_flag=0;}


if(ring_open_flag==1)
  {ring_open();    ring_open_flag=0;}
if(ring_close_flag==1)
  {ring_close();    ring_close_flag=0;}

if(little_open_flag==1)
  {little_open();    little_open_flag=0;}
if(little_close_flag==1)
  {little_close();    little_close_flag=0;}

} 

void serialEvent() {
  while (Serial.available())
  {
      // get the new byte:
      char inChar = (char)Serial.read(); 
      switch(inChar)
      {
        case 'a': all_open_flag=1;
                  break;
        case 'b': all_close_flag=1;
                  break;
        case 'c': show_one_flag=1;
                  break;
        case 'd': show_two_flag=1;
                  break;
        case 'e': show_three_flag=1;
                  break;
        case 'f': show_four_flag=1;
                  break;
        case 'm': thumb_open_flag=1;
                  break;
        case 'n': thumb_close_flag=1;
                  break;
        case 'o': index_open_flag=1;
                  break;
        case 'p': index_close_flag=1;
                  break;
        case 'q': middle_open_flag=1;
                  break;
        case 'r': middle_close_flag=1;
                  break;
        case 's': ring_open_flag=1;
                  break;
        case 't': ring_close_flag=1;
                  break;
        case 'u': little_open_flag=1;
                  break;
        case 'v': little_close_flag=1;
                  break;
                 
        case '1': slow_open();
                  break;
        case '2': slow_close();
                  break;
        
        default: {
                  all_open_flag=0;
                  all_close_flag=0;
                  show_one_flag=0;
                  show_two_flag=0;
                  show_three_flag=0;
                  show_four_flag=0;
                  thumb_open_flag=0;
                  thumb_close_flag=0;
                 }
      }
    }
}


void all_open()
{
all_open_flag=0;
Serial.println("in all open");
thumb_open();
index_open();
middle_open();
ring_open();
little_open();
}

void all_close()
{
all_close_flag=0;
Serial.println("In all close");

thumb_close();
index_close();
middle_close();
ring_close();
little_close();

}


void show_one()
{
show_one_flag=0;
Serial.println("In show one");
thumb_close();
index_open();
middle_close();
ring_close();
little_close();

}

void show_two()
{
show_two_flag=0;
Serial.println("In show two");
thumb_close();
index_open();
middle_open();
ring_close();
little_close();
  
}

void show_three()
{
  show_three_flag=0;
  Serial.println("In show three");
thumb_close();
index_open();
middle_open();
ring_open();
little_close();

}

void show_four()
{
  show_four_flag=0;
  Serial.println("In show four");
thumb_close();
index_open();
middle_open();
ring_open();
little_open();

}


void slow_open()
{
  Serial.println("In slow open");
  thumb_p+=3;
  ring_p -=3;
  index_p +=3;
  middle_p -=3;
  little_p -=3;
  
       thumb.write(thumb_p);
      index.write(index_p);              // tell servo to go to position in variable 'pos' 
      middle.write(middle_p);              // tell servo to go to position in variable 'pos' 
      ring.write(ring_p);              // tell servo to go to position in variable 'pos' 
      little.write(little_p);       // tell servo to go to position in variable 'pos' 
       
}

void slow_close()
{
  thumb_p -=3;
  ring_p +=3;
  index_p -=3;
  middle_p +=3;
  little_p +=3;
      
      thumb.write(thumb_p);
      index.write(index_p);              // tell servo to go to position in variable 'pos' 
      middle.write(middle_p);              // tell servo to go to position in variable 'pos' 
      ring.write(ring_p);              // tell servo to go to position in variable 'pos' 
      little.write(little_p);       // tell servo to go to position in variable 'pos' 
      Serial.println("In slow close");
}

void thumb_close()
{
  
  if(thumb_p < 45)
    thumb_p=45;
  if(thumb_p > 141)
    thumb_p=141;
    
  Serial.println("closing thumb");
  if(thumb_p >= 45 && thumb_p <= 141)
    {
      while(thumb_p!=45)
        {
          thumb_p--;
         delay(10);
        }
    }
    thumb.write(thumb_p);
}

void thumb_open()
{

  if(thumb_p < 45)
    thumb_p=45;
  if(thumb_p > 141)
    thumb_p=141;
  Serial.println("opening thumb");
  if(thumb_p >= 45 && thumb_p <= 141)
    {
      while(thumb_p!=141)
        {
          thumb_p++;
         delay(10);
        }
    }
    
    thumb.write(thumb_p);
}

void index_close()
{

  if(index_p < 51 )
    index_p = 51;
  if(index_p > 160 )
    index_p = 160;
  Serial.println("closing index");
  if(index_p >= 51 && index_p <= 160)
    {
      while(index_p!=158)
        {
          index_p++;
         delay(10);
        }
    }
    
    index.write(index_p);
}

void index_open()
{

  if(index_p < 51 )
    index_p = 51;
  if(index_p > 160 )
    index_p = 160;
    
  Serial.println("opening index");
  if(index_p >= 51 && index_p <= 160)
    {
      while(index_p!=51)
        {
          index_p--;
         delay(10);
        }
    }

    index.write(index_p);
}

void middle_close()
{
  
if(middle_p < 14)
  middle_p=14;
if(middle_p > 135)
  middle_p=135;
  
  Serial.println("closing middle");
  if(middle_p >= 14 && middle_p <= 135)
    {
      while(middle_p!=14)
        {
          middle_p--;
         delay(10);
        }
    }

    middle.write(middle_p);
}

void middle_open()
{

if(middle_p < 14)
  middle_p=14;
if(middle_p > 135)
  middle_p=135;
  
  
  Serial.println("opening middle");
  if(middle_p >= 14 && middle_p <= 135)
    {
      while(middle_p!=135)
        {
          middle_p++;
         delay(10);
        }
    }
    
    middle.write(middle_p);
}

void ring_close()
{

if(ring_p < 49)
  middle_p=49;
if(middle_p > 133)
  middle_p=133;
  
  
  Serial.println("closing ring");
  if(ring_p >= 49 && ring_p <= 133)
    {
      while(ring_p!=49)
        {
          ring_p--;
         delay(10);
        }
    }
    
    ring.write(ring_p);
}


void ring_open()
{

if(middle_p < 49)
  middle_p=49;
if(middle_p > 133)
  middle_p=133;
  
  
  Serial.println("opening ring");
  if(ring_p >= 49 && ring_p <= 133)
    {
      while(ring_p!=133)
        {
          ring_p++;
         delay(10);
        }
    }
    
    ring.write(ring_p);
}


void little_close()
{

if(little_p < 23)
  little_p=23;
if(middle_p > 115)
  little_p=115;
  
  
  Serial.println("closing little");
  if(little_p >= 23 && little_p <= 115)
    {
      while(little_p!=23)
        {
          little_p--;
         delay(10);
        }
    }
    
    little.write(little_p);
}

void little_open()
{

  Serial.println("opening little");
  if(little_p >= 23 && little_p <= 115)
    {
      while(little_p!=115)
        {
          little_p++;
         delay(10);
        }
    }
    
    little.write(little_p);
}

