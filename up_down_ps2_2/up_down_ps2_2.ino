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
#include <Wire.h>


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9, 10, 3, 4, 5, 6);

const int DataPin = 8;
const int IRQpin =  2;

PS2Keyboard keyboard;
int counter=0;
int addr=100;
unsigned char value=0;

int lastbuttonstate_11=0;
int lastbuttonstate_12=0;

void eeprom_i2c_write(byte address,byte from_addr, byte data)
{
Wire.beginTransmission(address);
Wire.write(from_addr);
Wire.write(data);
Wire.endTransmission();
}


byte eeprom_i2c_read(int address, int from_addr)
{
Wire.beginTransmission(address);
Wire.write(from_addr);
Wire.endTransmission();
Wire.requestFrom(address,1);
if(Wire.available())
  return Wire.read();
else
  return 0xff;
  
}


void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  keyboard.begin(DataPin, IRQpin);
  Wire.begin();
  //int i=0;
  int ee_hvalue=0;
  int ee_lvalue=0;
  
  
  lcd.print(" Welcome");    
  pinMode(13,OUTPUT);
  pinMode(12,INPUT);
  pinMode(11,INPUT);
  
  lcd.setCursor(1,1);
  //For the first time, writing the initial two bytes as Zero in EEPROM
  if(eeprom_i2c_read(0x50,0) == 0xff);
  {
   eeprom_i2c_write(B01010000,0,0);
   eeprom_i2c_write(B01010000,1,0);
  }
  
    
  delay(2000);
  lcd.clear();
  ee_hvalue=eeprom_i2c_read(B01010000,0);
  ee_lvalue=eeprom_i2c_read(B01010000,1);
  counter = (ee_hvalue*256)+(ee_lvalue);
  
}


//************************************************* LOOP  ******************************************************************
void loop() 
{
  int button_value_12=digitalRead(12);
  int button_value_11=digitalRead(11);
  char c='\0';
  int i=0;
  int ee_hvalue=0;
  int ee_lvalue=0;
 
  if(button_value_12 != lastbuttonstate_12)
  {
    if(button_value_12==1)
    {
      counter++;
      ee_hvalue=counter/255;
      ee_lvalue=counter%255;
      
      eeprom_i2c_write(B01010000,0,ee_hvalue);
      eeprom_i2c_write(B01010000,1,ee_lvalue);
      
      lcd.clear();
    }
  }
    
  if(button_value_11 != lastbuttonstate_11)
  {  
    if(button_value_11==1 && counter>1)
    {
      counter--;
      ee_hvalue=counter/255;
      ee_lvalue=counter%255;
      
      eeprom_i2c_write(B01010000,0,ee_hvalue);
      eeprom_i2c_write(B01010000,1,ee_lvalue);
      lcd.clear();
    }
  }
    
  lastbuttonstate_11 = button_value_11;
  lastbuttonstate_12 = button_value_12;
  
  lcd.print(counter);
  lcd.setCursor(0,0);

    if (keyboard.available()) 
         {
           c = keyboard.read();
            if (c == PS2_DELETE)
            {
              lcd.setCursor(1,1);
              lcd.print("Deleting...");
              delay(2000);
              lcd.clear();
              counter=0;
              eeprom_i2c_write(B01010000,0,0);
              eeprom_i2c_write(B01010000,1,0);
              
              lcd.clear();
            }               
       }
  lcd.setCursor(0,0);     
}

