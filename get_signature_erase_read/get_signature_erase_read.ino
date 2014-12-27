 #include <SPI.h>

int reset_pin=10;
byte return_bytes[4]={0,0,0,0};

void setup()
{
Serial.begin(19200);
Serial.println("Get signature program");
SPI.begin();
SPI.setClockDivider(SPI_CLOCK_DIV64);
pinMode(13,OUTPUT);

start_programming();

get_signatures();
get_fuses();
//write_high_fuse();
delay(3000);
//read_flash(2);
//erase_chip();
//delay(2000);
//get_fuses();

//read_flash(10);
//read_eeprom();
//delay(5000);
read_flash(10);
}


void loop()
{
digitalWrite(13,HIGH);
delay(100);
digitalWrite(13,LOW);
delay(100);
}


void start_programming()
{
  Serial.println("Entering programming mode");
pinMode(reset_pin,OUTPUT);  
digitalWrite(reset_pin,LOW);
delay(25);

do{
return_bytes[0]=SPI.transfer(0xAC);
return_bytes[1]=SPI.transfer(0x53);
return_bytes[2]=SPI.transfer(0);
return_bytes[3]=SPI.transfer(0);

Serial.print(return_bytes[0],HEX);
Serial.print("\t");
Serial.print(return_bytes[1],HEX);
Serial.print("\t");
Serial.print(return_bytes[2],HEX);
Serial.print("\t");
Serial.println(return_bytes[3],HEX);
}
while (return_bytes[2]!=83);
Serial.println("Successfully entered programming mode");
}

void get_signatures()
{
Serial.println("Obtaining signatures");  
SPI.transfer(0x30);
SPI.transfer(0x00);
SPI.transfer(0x00);
byte add1=SPI.transfer(0);
Serial.print("signature address 1 is \t");
Serial.println(add1, HEX);

SPI.transfer(0x30);
SPI.transfer(0x00);
SPI.transfer(0x01);
byte add2=SPI.transfer(0);
Serial.print("signature address 2 is \t");
Serial.println(add2, HEX);

SPI.transfer(0x30);
SPI.transfer(0x00);
SPI.transfer(0x02);
byte add3=SPI.transfer(0);
Serial.print("signature address 3 is \t");
Serial.println(add3, HEX);

}

void erase_chip()
{
Serial.println("erasing chip");  
SPI.transfer(0xAC);
SPI.transfer(0x80);
SPI.transfer(0);
SPI.transfer(0);
delay(50);
Serial.println("chip erased");
}

void get_fuses()
{
byte array[4]={0};
Serial.println("Obtaining Fuses");  
Serial.print("Hfuse is\t");
array[0]=SPI.transfer(0x58);
array[1]=SPI.transfer(0x08);
array[2]=SPI.transfer(0);
array[3]=SPI.transfer(0);
Serial.println(array[3],HEX);

Serial.print("Lfuse is\t");
array[0]=SPI.transfer(0x50);
array[1]=SPI.transfer(0x00);
array[2]=SPI.transfer(0);
array[3]=SPI.transfer(0);
Serial.println(array[3],HEX);

Serial.print("Extended fuses are \t");
array[0]=SPI.transfer(0x50);
array[1]=SPI.transfer(0x08);
array[2]=SPI.transfer(0);
array[3]=SPI.transfer(0);
Serial.println(array[3],HEX);
}

void read_flash(int blocks)
{

unsigned char counter=0;
unsigned long address=0;
Serial.println("Reading whole Flash\t");
byte array[4]={0};

unsigned int address_m=0;
unsigned int address_l=0;
//address=(unsigned long)( (address_m*256)+(address_l*2) );
//Serial.print(address,HEX);
//Serial.print("\t");
 

for(address_m=0;address_m<blocks;address_m++)
  {
   for(address_l=0;address_l<256;address_l++)
    {
      array[0]=SPI.transfer(0x28);
      array[1]=SPI.transfer(address_m);
      array[2]=SPI.transfer(address_l);
      array[3]=SPI.transfer(0);
              Serial.print(array[3],HEX);
      array[0]=SPI.transfer(0x20);
      array[1]=SPI.transfer(address_m);
      array[2]=SPI.transfer(address_l);
      array[3]=SPI.transfer(0);
              Serial.print(array[3],HEX);
        Serial.print(" ");
      counter++;
      if(counter==8)
           {
            Serial.println("");
            counter=0;
          //  address=(unsigned long)( (address_m*256)+( (address_l*2)+2) );
           //  Serial.print(address,HEX);
         //   Serial.print("\t");
           }
          
    }//address_l for loop
    
  }//address_m for loop

}


void read_eeprom()
{
  int i=0;
  byte array[4]={0};
    for(i=0;i<256;i++)
      {
        array[0]=SPI.transfer(0xA0);
        array[1]=SPI.transfer(0);
        array[2]=SPI.transfer(i);
        array[3]=SPI.transfer(0);
        Serial.print("EEPROM value at");
        Serial.print(i);
        Serial.print("th address is ");
        Serial.println(array[3],HEX);      
      }
}


void write_high_fuse()
{
  byte array[4]={0};
  
        array[0]=SPI.transfer(0xAC);
        array[1]=SPI.transfer(0xA8);
        array[2]=SPI.transfer(0);
        array[3]=SPI.transfer(0xC4);
        Serial.print("High Fuse written successfully");

}


