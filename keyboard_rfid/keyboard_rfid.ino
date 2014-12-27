/*
  LiquidCrystal Library - Hello World
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD
 and shows the time.
 
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

/*  PS2Keyboard library example
  
  PS2Keyboard now requries both pins specified for begin()

  keyboard.begin(data_pin, irq_pin);
  
  Valid irq pins:
     Arduino Uno:  2, 8
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



// include the library code:
#include <LiquidCrystal.h>
#include <PS2Keyboard.h>
#include <EEPROM.h>



// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(18, 19, 14, 15, 16, 17);

const int DataPin = 8;
const int IRQpin =  2;

char mystring[12]= "";
int i,ctr=0;
int name_count=0;

int base[]={0,30,60,90,120};
unsigned char fill_flag[5]={0,0,0,0,0};
unsigned char my_check_flag=0;

PS2Keyboard keyboard;

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  keyboard.begin(DataPin, IRQpin);
  Serial.begin(9600);
  
  lcd.print(" RFID");
  lcd.setCursor(5,1);
  lcd.print("ATTANDENCE");
    
  delay(2000);
  show_reception();
  
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  
  digitalWrite(12,HIGH);
  digitalWrite(13,HIGH);
     delay(500);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
    delay(500);
  digitalWrite(12,HIGH);
   
}


//************************************************* LOOP  ******************************************************************
void loop() 
{
              digitalWrite(13,HIGH);
              delay(200);
              if(my_check_flag==1)
                {
                 my_check();
                 my_check_flag=0;
                }
              digitalWrite(13,LOW);
              delay(300);
}




void serialEvent() {
  while (Serial.available()) {
      mystring[i] = Serial.read();  
     i++;
     if(i==12)
       my_check_flag=1;
  }
  
}


//***********************************************************MY  CHECK********************************************************

void my_check()
{
  
  Serial.println("In my_check");
  int x=0;
  int flag=0;
  char reader=0;
      i=0;
      digitalWrite(13,HIGH);    
      digitalWrite(12,LOW);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("CARD SWIPED");
      lcd.setCursor(0,1);
      delay(500);
      digitalWrite(12,HIGH);
      digitalWrite(13,LOW);
      
      
        flag=check_existence();
        switch(flag)
        {
          case 0        :  {
                              mycase_0(); 
                              break;              
                           }
          
          case 1        :  {
                              lcd.clear();
                              lcd.print("mycase_1 called");
                                delay(2000);
                              lcd.clear();
                             lcd.setCursor(0,0);
                             lcd.print("Welcome Mr."); 
                             lcd.setCursor(0,1);
                             for(x=0;x<10;x++)
                               {
                                 reader = (char)EEPROM.read(base[0]+15+x);
                                 lcd.print(reader);
                               }
                               delay(2000);
                               lcd.setCursor(0,0);
                               lcd.print("Press a key");
                               take_input(1);
                               show_reception();
                               break; 
                           }

          case 2        :  {
                              lcd.clear();
                              lcd.print("mycase_2 called");
                              delay(2000);
                             lcd.clear();
                             lcd.setCursor(0,0);
                             lcd.print("Welcome Mr."); 
                             lcd.setCursor(0,1);
                             for(x=0;x<10;x++)
                               {
                                 reader = (char)EEPROM.read(base[1]+15+x);
                                 lcd.print(reader);
                               }
                               delay(2000);
                               lcd.setCursor(0,0);
                               lcd.print("Press a key");
                               take_input(2);
                               show_reception();
                              break; 
                           }
          case 3        :  {
                              lcd.clear();
                              lcd.print("mycase_3 called");
                              delay(2000);
                             lcd.clear();
                             lcd.setCursor(0,0);
                             lcd.print("Welcome Mr."); 
                             lcd.setCursor(0,1);
                           for(x=0;x<10;x++)
                               {
                                 reader = (char)EEPROM.read(base[2]+15+x);
                                 lcd.print(reader);
                               }
                               delay(2000);
                               lcd.setCursor(0,0);
                               lcd.print("Press a key");
                               take_input(3);
                               show_reception();
                               break; 
                           }
          case 4        :  {
                              lcd.clear();
                              lcd.print("mycase_4 called");
                              delay(2000);
                             lcd.clear();
                             lcd.setCursor(0,0);
                             lcd.print("Welcome Mr."); 
                             lcd.setCursor(0,1);
                             for(x=0;x<10;x++)
                               {
                                 reader = (char)EEPROM.read(base[3]+15+x);
                                 lcd.print(reader);
                               }
                               delay(2000);
                               lcd.setCursor(0,0);
                               lcd.print("Press a key");
                               take_input(4);
                               show_reception();
                               break; 
                           }
          case 5        :  {
                              lcd.clear();
                              lcd.print("mycase_5 called");
                              delay(2000);
                              lcd.clear();
                             lcd.setCursor(0,0);
                             lcd.print("Welcome Mr."); 
                             lcd.setCursor(0,1);
                             for(x=0;x<10;x++)
                               {
                                 reader = (char)EEPROM.read(base[4]+15+x);
                                 lcd.print(reader);
                               }
                               delay(2000);
                               lcd.setCursor(0,0);
                               lcd.print("Press a key");
                               take_input(5);
                               show_reception();
                               break; 
                           }

         default        :  {
                              lcd.setCursor(0,0);
                              lcd.print("NO NEW ENTRY");
                              Serial.println("In default");
                              break;
                           }
        }
}

//***********************************************************CHECK FOR EXISTENCE OF NAME********************************************************

int check_existence()
{
 
Serial.println("in check_existence");
int x=0;
 for(x=0;x<5;x++)
   {
     if(fill_flag[x]==1)
      {
       if(mystring[0]==EEPROM.read(base[x]) && mystring[1]==EEPROM.read(base[x]+1) && mystring[2]==EEPROM.read(base[x]+2) && mystring[3]==EEPROM.read(base[x]+3) && mystring[4]==EEPROM.read(base[x]+4) && mystring[5]==EEPROM.read(base[x]+5) && mystring[6]==EEPROM.read(base[x]+6) && mystring[7]==EEPROM.read(base[x]+7) && mystring[8]==EEPROM.read(base[x]+8) && mystring[9]==EEPROM.read(base[x]+9) && mystring[10]==EEPROM.read(base[x]+10) && mystring[11]==EEPROM.read(base[x]+11))
        { 
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("match occured");  
         delay(1000);
         lcd.setCursor(0,1);
         Serial.println("match occured");
         return (x+1);  
       }
      }
   }
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("NO MATCH! :(" );
         Serial.println("NO MATCH! :(" );
         delay(1000);
         return 0;   
}


//***********************************************************INPUT NAME********************************************************
void input_name(int who)
{
  char c='\0';
  unsigned char reader=0;
  unsigned char tmp=0;
   while(1)
  {
        if(c == 10 || name_count == 10 || c == PS2_ENTER ) 
          {
           for (tmp=0;tmp<10;tmp++)
           {
             reader= (char) EEPROM.read(base[0]+15+tmp);
             Serial.print(reader);
           }
           lcd.clear();
           Serial.println("name written successfully");
           lcd.setCursor(0,0);
           lcd.print("Name written");
           name_count=0;
           delay(1000);
           lcd.clear();
           lcd.setCursor(0,0);
           break;
          }
          
          if (keyboard.available()) 
         {
           c = keyboard.read();
           if(who == 1 )
             EEPROM.write(base[0]+name_count+15,c);
           else if(who == 2)
             EEPROM.write(base[1]+name_count+15,c);
           else if(who == 3)
             EEPROM.write(base[2]+name_count+15,c);
           else if(who == 4)
             EEPROM.write(base[3]+name_count+15,c);
           else if(who == 5)
             EEPROM.write(base[4]+name_count+15,c);
           
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
              lcd.print(c);
              Serial.print(c);
            }
          } 
  }

}

//*********************************************SHOW RECEPTION***********************************************************************
void show_reception()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" PLZ. SWIPE");
  lcd.setCursor(3,1);
  lcd.print("YOUR CARD");
}  


//*********************************************MY CASE 0***********************************************************************
void mycase_0()
{
  lcd.clear();
  lcd.print("mycase_0 called");
  lcd.setCursor(0,1);
  
  int flag_counter=0;
  int x=0,reader=0;
   
                        for(flag_counter = 0; flag_counter < 5; flag_counter++)
                             { if(fill_flag[flag_counter] == 0)
                               {
                                 fill_flag[flag_counter] = 1;
                                 lcd.clear();
                                 lcd.setCursor(0,0);
                                 lcd.print("Writing At");
                                 lcd.setCursor(0,1);
                                 lcd.print(flag_counter);
                                 delay(1000);
                                 lcd.clear();
                                 Serial.println("now checking while writing from EEPROM");
                                 for(x=0;x<12;x++)
                                    {
                                     EEPROM.write(base[flag_counter]+x,mystring[x]);
                                     reader = (char) EEPROM.read(base[flag_counter]+x); 
                                     Serial.print(reader);
                                    }
                                    Serial.println("");
                                                    
                                lcd.clear();
                                lcd.setCursor(0,0);
                                Serial.println("enter your name");
                                lcd.print("Enter Your Name");
                                lcd.setCursor(0,1);
                                input_name(flag_counter+1);
                                delay(2000);
                                lcd.clear();
                                lcd.setCursor(0,0);
                                show_reception();     
                                break;
                               }
                              
                             }  
}


//********************************************* TAKE INPUT ***********************************************************************
void take_input(int var_del)
{
  char c='\0';
  while(1)
  {
    if (keyboard.available()) 
         {
           c = keyboard.read();
            if (c == PS2_ENTER)
            {
              lcd.print(" ***");
              delay(500);
              break;
            } 
            else if (c == PS2_DELETE)
            {
              lcd.print("-Del");
              del_attandee(var_del);
              break;
            } 
         }
  }
}


void del_attandee(int var_del)
{
  fill_flag[var_del-1]=0;
  unsigned char x=0;
  for(x=0;x<12;x++)
    EEPROM.write(base[var_del-1]+x,0);
}
