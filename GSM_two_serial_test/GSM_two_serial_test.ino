#include <util/delay.h>
#include <SoftwareSerial.h>
#include <MemoryFree.h>

SoftwareSerial mySerial(8, 9); // RX, TX
unsigned long file_size=0;
unsigned long no_of_bytes_recieved=0;
boolean my_file_complete=false;




void setup()  
{
  
  boolean continue_further=false;
  Serial.begin(9600);
  while (!Serial);
  Serial.println(F("Working OK on Original Serial !"));
  Serial.print(F("memory usage is \t"));
  Serial.println(getFreeMemory());
  Serial.flush();
  mySerial.begin(9600);
  mySerial.println(F("AT"));
  mySerial.flush();
  check_ok();
 // mySerial.println("AT+HTTPTERM");
 // mySerial.println("ATE0");
 // check_ok();
  _delay_ms(1000*10);
  mySerial.println(F("AT+SAPBR=3,1,\"APN\",\"INTERNET\""));
  mySerial.flush();
  check_ok();
  mySerial.println(F("AT+SAPBR=1,1"));
  mySerial.flush();
  check_ok();
  mySerial.println(F("AT+SAPBR=2,1"));
  mySerial.flush();
  check_ok();
  mySerial.println(F("AT+HTTPINIT"));
  mySerial.flush();
  check_ok();
  mySerial.println(F("AT+HTTPPARA=\"CID\",1"));
  mySerial.flush();
  check_ok();
//  mySerial.println("AT+HTTPPARA=\"URL\",\"http://115.115.95.74/gpsexpress/checkportdata/check_9047.php\"");
  mySerial.println(F("AT+HTTPPARA=\"URL\",\"http://myrobo.in/test.hex\""));

  mySerial.flush();
  check_ok();
  mySerial.println(F("AT+HTTPACTION=0"));
  mySerial.flush();
  check_ok();
  
  check_symbol('+');
  check_symbol(':');
  mySerial.flush();
  _delay_ms(5*1000);
  _delay_ms(1000);
  mySerial.println(F("AT+HTTPREAD"));
  mySerial.flush();
  check_symbol('+');
  check_symbol(':');
  get_file_size();
//  get_hex_file();
  check_endof_file();
//  check_ok();
if(file_size==no_of_bytes_recieved)
  {
    continue_further=true;
    Serial.println(F("Correct file recieved"));
  }
if(continue_further)
{

//further codde
}
  
}

void loop() // run over and over
{
  Serial.println(F("in loop"));
  _delay_ms(500);
}


void check_ok()
{
  boolean ok_flag=false;
  char mybyte=0;
  
  while(ok_flag!=true)
  {
    while(mySerial.available()==0);
      mybyte=(char)mySerial.read(); 
      Serial.print((char)mybyte);
      if(mybyte=='O')
        { // O check - 1
           while(mySerial.available()==0);
           mybyte=(char)mySerial.read();
           Serial.print((char)mybyte);
           if(mybyte=='K')
             {
               //Serial.print("okay recieved");
               ok_flag=true;
             }
        }
  }

}

void check_symbol(char value)
{
  boolean recieved_flag=false;
  char mybyte=0;
//  Serial.print("value to be check is\t");
  //Serial.println(value);
  
  while(recieved_flag!=true)
  {
    while(mySerial.available()==0);
    mybyte=(char)mySerial.read(); 
//    Serial.print((char)mybyte);
    if(mybyte==value)
      {
        recieved_flag=true;
       // Serial.println("recieved");
      }
  }
}



void get_file_size()
{
  char mybyte=0;
  boolean new_line_recieved=false;
  Serial.println(F("in get file size"));
  while(new_line_recieved!=true)
  {
     while(mySerial.available()==0);
     mybyte=(char)mySerial.read(); 
     
     if(mybyte!=13)
     {
        // Serial.print((char)mybyte);
         file_size= (file_size*10)+(mybyte-48);
     }
     else
     {
        // Serial.print((char)mybyte);
         new_line_recieved=true;
     }
     
  }
  Serial.print(F("file size recieved is\t"));
  Serial.print(file_size);
  Serial.println(F("bytes"));
  Serial.flush();  
}


void check_endof_file()
{
 char mybyte=0;
  while(my_file_complete==false)
  {
    while(mySerial.available()==0);
    mybyte=(char)mySerial.read(); 
    Serial.print((char)mybyte);
    no_of_bytes_recieved++;  
    if(mybyte==':')
      { // Colon check - 1
         while(mySerial.available()==0);
         mybyte=(char)mySerial.read();
         Serial.print((char)mybyte);
          no_of_bytes_recieved++;  
         if(mybyte=='0')
         {//first zero check -2
            while(mySerial.available()==0);
            mybyte=(char)mySerial.read();
            Serial.print((char)mybyte);
             no_of_bytes_recieved++;  
            if(mybyte=='0')
            {//second zero check -3
                 while(mySerial.available()==0);
                 mybyte=(char)mySerial.read(); 
                 Serial.print((char)mybyte);
                  no_of_bytes_recieved++;  
                 if(mybyte=='0')
                 {//Third zero check -4
                     while(mySerial.available()==0);
                     mybyte=(char)mySerial.read(); 
                     Serial.print((char)mybyte);
                      no_of_bytes_recieved++;  
                     if(mybyte=='0')
                     {//Fourth zero check -5 
                         while(mySerial.available()==0);
                         mybyte=(char)mySerial.read(); 
                         Serial.print((char)mybyte);
                          no_of_bytes_recieved++;  
                         if(mybyte=='0')
                         {//fifth zero check -6
                             while(mySerial.available()==0);
                             mybyte=(char)mySerial.read(); 
                             Serial.print((char)mybyte);
                              no_of_bytes_recieved++;  
                             if(mybyte=='0')
                             {//Sixth zero check - 7
                                 while(mySerial.available()==0);
                                 mybyte=(char)mySerial.read(); 
                                 Serial.print((char)mybyte);
                                  no_of_bytes_recieved++;  
                                 if(mybyte=='0')
                                   {//Seventh zero check -8
                                       while(mySerial.available()==0);
                                       mybyte=(char)mySerial.read(); 
                                       Serial.print((char)mybyte);
                                        no_of_bytes_recieved++;  
                                       if(mybyte=='1')
                                         {//9th as 1 check -9
                                             while(mySerial.available()==0);
                                             mybyte=(char)mySerial.read(); 
                                             Serial.print((char)mybyte);
                                              no_of_bytes_recieved++;  
                                             if(mybyte=='F')
                                               {//10th as F check -10
                                                   while(mySerial.available()==0);
                                                   mybyte=(char)mySerial.read(); 
                                                   Serial.print((char)mybyte);
                                                    no_of_bytes_recieved++;  
                                                   if(mybyte=='F')
                                                     {//11th as F check -11
                                                         Serial.print((char)mybyte);
                                                         my_file_complete=true;
                                                         no_of_bytes_recieved++;  
                                                  
                                                     }// - 11 ends
                                              }//10 ends
                                          }//9 ends  
                                   }//8 ends
                            }//7 ends
                      } //6 ends
                 }//5 ends
            }//4 ends 
        }//3 ends
     }//2 ends
  }//1 ends     
 }  //while ends
if(my_file_complete==true)
  {
    my_file_complete=false;
    Serial.println(F("magic String recieved"));
    Serial.print(F("no of bytes recieved \t"));
    Serial.print(no_of_bytes_recieved);
  }
} // function ends

