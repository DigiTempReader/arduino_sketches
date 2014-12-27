/*  PS2Keyboard library example
  
  PS2Keyboard now requries both pins specified for begin()

  keyboard.begin(data_pin, irq_pin);
  
  Valid irq pins:
     Arduino Uno:  2, 3
     Arduino Due:  All pins, except 13 (LED)
     Arduino Mega: 2, 3, 18, 19, 20, 21
     Teensy 2.0:   All pins, except 13 (LED)
     Teensy 2.0:   5, 6, 7, 8
     Teensy 1.0:   0, 1, 2, 3, 4, 6, 7, 16
     Teensy++ 2.0: 0, 1, 2, 3, 18, 19, 36, 37
     Teensy++ 1.0: 0, 1, 2, 3, 18, 19, 36, 37
     Sanguino:     2, 10, 11
  
  for more information you can read the original wiki in arduino.cc
  at http://www.arduino.cc/playground/Main/PS2Keyboard
  or http://www.pjrc.com/teensy/td_libs_PS2Keyboard.html
  
  Like the Original library and example this is under LGPL license.
  
  Modified by Cuninganreset@gmail.com on 2010-03-22
  Modified by Paul Stoffregen <paul@pjrc.com> June 2010
*/
   
#include <PS2Keyboard.h>

const int DataPin = 8;
const int IRQpin =  2;



char mystring[12]= "";
int i,ctr=0;
int name_count=0;
boolean card1_flag=false;
boolean card2_flag=false;
char card1_name[15]="";
char card2_name[15]="";



PS2Keyboard keyboard;

void setup() {
  delay(1000);
  keyboard.begin(DataPin, IRQpin);
  Serial.begin(9600);
  Serial.println("Keyboard Test:");


  Serial.println("it's started");
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  
  digitalWrite(12,HIGH);
  digitalWrite(13,HIGH);
     delay(500);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
   delay(200);
}

void loop() {
   mycheck();
}


void serialEvent() {
  while (Serial.available()) {
      mystring[i] = Serial.read();  
     i++;
  }
  
}

void mycheck()
{
  int x=0;
if(i==12)
    {
      if(mystring[0]=='4' && mystring[1]=='2' && mystring[2]=='0' && mystring[3]=='0' && mystring[4]=='6' && mystring[5]=='6' && mystring[6]=='0' && mystring[7]=='7' && mystring[8]=='8' && mystring[9]=='B' && mystring[10]=='A' && mystring[11]=='8')
       { 
         digitalWrite(13,HIGH);
         delay(1000);
         digitalWrite(13,LOW);
       if(card2_flag == false)
           {Serial.println("enter ur name, sir");
            input_name(2);   
            card2_flag=true;
           }
       else
           {Serial.print("Owner of Card 2 has entered --NAME--");
            for(x=0;x<15;x++)
            Serial.print(card2_name[x]);
            Serial.print('\n');
           }
     }
       
      if(mystring[0]=='4' && mystring[1]=='2' && mystring[2]=='0' && mystring[3]=='0' && mystring[4]=='6' && mystring[5]=='C' && mystring[6]=='9' && mystring[7]=='9' && mystring[8]=='8' && mystring[9]=='B' && mystring[10]=='3' && mystring[11]=='C')
       { 
         digitalWrite(13,HIGH);
         delay(1000);
         digitalWrite(13,LOW);
         
         if(card1_flag == false)
           {Serial.println("enter ur name, sir");
            input_name(1);   
            card1_flag=true;
           }
         else
           {Serial.print("Owner of Card 1 has entered --NAME--");
             for(x=0;x<15;x++)
            Serial.print(card1_name[x]);
            Serial.print('\n');
           }  
     }
       
   i=0;    
  }
}

int input_name(int who)
{
  char c='\0';
  
   while(1)
  {
    if(c == 10 || name_count == 15)
      {
       Serial.println("name written successfully");
       name_count=0;
       return 1;
      }
  if (keyboard.available()) 
  {
    
   c = keyboard.read();
   
   if(who == 1 )
   card1_name[name_count]=c;
   else if(who == 2)
   card2_name[name_count]=c;
   
   name_count++; 
    
    if (c == PS2_ENTER) {
      Serial.println();
    } else if (c == PS2_TAB) {
      Serial.print("[Tab]");
    } else if (c == PS2_ESC) {
      Serial.print("[ESC]");
    } else if (c == PS2_PAGEDOWN) {
      Serial.print("[PgDn]");
    } else if (c == PS2_PAGEUP) {
      Serial.print("[PgUp]");
    } else if (c == PS2_LEFTARROW) {
      Serial.print("[Left]");
    } else if (c == PS2_RIGHTARROW) {
      Serial.print("[Right]");
    } else if (c == PS2_UPARROW) {
      Serial.print("[Up]");
    } else if (c == PS2_DOWNARROW) {
      Serial.print("[Down]");
    } else if (c == PS2_DELETE) {
      Serial.print("[Del]");
    } 
    else
    {
      Serial.print(c);
    }
  } 
 }

}

