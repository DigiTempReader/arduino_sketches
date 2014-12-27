 #include <SPI.h>

int reset_pin=10;
byte return_bytes[4]={0,0,0,0};

void setup()
{
Serial.begin(115200);
Serial.println("Get signature program");
SPI.begin();
SPI.setClockDivider(SPI_CLOCK_DIV64);
pinMode(13,OUTPUT);

start_programming();

get_signatures();


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

}

void get_signatures()
{
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
