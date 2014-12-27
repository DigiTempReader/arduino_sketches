const int chipSelect = 10;
/*
 SD card read/write
  
 This example shows how to read and write data to and from an SD card file 	
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 	 
 */
#include <SoftwareSerial.h> 
#include <MemoryFree.h>
#include <util/delay.h>

#include <SdFat.h>
SdFat sd;
SdFile myFile,myFile2;

SoftwareSerial mySerial(10, 11); // RX, TX
boolean my_file_complete=false;

//byte mybyte=0;

void setup() 
{
  
  Serial.begin(9600);
  while (!Serial) {}  // wait for Leonardo
  Serial.print(F("Free Memory = "));
  Serial.println(getFreeMemory());

  mySerial.begin(9600);
  mySerial.println(F("Software Serial Started"));
  Serial.println(F("Type any character to start"));
  while (Serial.read() <= 0) {}
  _delay_ms(400);  // catch Due reset problem
  
  // Initialize SdFat or print a detailed error message and halt
  // Use half speed like the native library.
  // change to SPI_FULL_SPEED for more performance.
  if (!sd.begin(chipSelect, SPI_HALF_SPEED)) sd.initErrorHalt();

  // open the file for write at end like the Native SD library
  if (!myFile.open("test.txt", O_RDWR | O_CREAT | O_TRUNC)) {
    sd.errorHalt("opening test.txt for write failed");
  }
  // if the file opened okay, write to it:
  Serial.print(F("Writing to test.txt..."));
  myFile.println(F("testing 1, 2, 3."));

  Serial.println(("now closing the file"));
  // close the file:
  boolean isclosed=myFile.close();
  Serial.println(isclosed);
  Serial.println(F("done."));

  // re-open the file for reading:
  if (!myFile.open("test.txt", O_READ)) {
    sd.errorHalt("opening test.txt for read failed");
  }
  Serial.println(F("test.txt:"));

  // read from the file until there's nothing else in it:
  int data;
  while ((data = myFile.read()) >= 0) Serial.write(data);
  // close the file:
  myFile.close();
  Serial.println(F("setup over"));
  get_file_from_serial();
}

void loop() 
{
//  my_other_works();
}

void my_other_works()
{

}

void get_file_from_serial()
{
  int rem_value=0;
  if(sd.exists("RECVD.HEX"))
    rem_value=sd.remove("RECVD.HEX");
  else
    Serial.println(F("file doesn't exists"));
  if(rem_value==1)
    Serial.println(F("file successfully removed"));
    
if (!myFile2.open("RECVD.HEX", O_RDWR | O_CREAT | O_TRUNC)) 
  {
  sd.errorHalt("opening RECVD.HEX for write failed");
  }
Serial.println(F("file opened successfully, now writing in SD file"));
while(1)
  {
    recieve_till_endof_file();
    if(my_file_complete==true)
    {
    Serial.println(F("file writing completed, exiting "));
    myFile2.close();
    my_file_complete=false;
    break;
    } //IF closes
  }//While closes
  
Serial.println(F("end of recieve file till end "));
if(sd.exists("RECVD.HEX"))
  Serial.println(F("file exists, now reading"));
  if (!myFile2.open("RECVD.HEX", O_READ)) {
    sd.errorHalt("opening RECVD.TXT for read failed");
  }
  Serial.println(F("RECVD.HEX:"));

  // read from the file until there's nothing else in it:
  int data;
  while ((data = myFile2.read()) >= 0) Serial.print(data);
  // close the file:
  myFile2.close();
  Serial.println(F("read success"));
} // GET_FILE_FROM_SERIAL closes




void recieve_till_endof_file()
{
  byte mybyte=0;
    while(Serial.available()==0);
    mybyte=(char)Serial.read(); 
    Serial.print((char)mybyte);
    myFile2.print((char)mybyte);
    if(mybyte==':')
      { // Colon check - 1
         while(Serial.available()==0);
         mybyte=(char)Serial.read();
         Serial.print((char)mybyte);
         myFile2.print((char)mybyte);
         if(mybyte=='0')
         {//first zero check -2
            while(Serial.available()==0);
            mybyte=(char)Serial.read();
            Serial.print((char)mybyte);
            myFile2.print((char)mybyte);
            if(mybyte=='0')
            {//second zero check -3
                 while(Serial.available()==0);
                 mybyte=(char)Serial.read(); 
                 Serial.print((char)mybyte);
                 myFile2.print((char)mybyte);
                 if(mybyte=='0')
                 {//Third zero check -4
                     while(Serial.available()==0);
                     mybyte=(char)Serial.read(); 
                     Serial.print((char)mybyte);
                     myFile2.print((char)mybyte);
                     if(mybyte=='0')
                     {//Fourth zero check -5 
                         while(Serial.available()==0);
                         mybyte=(char)Serial.read(); 
                         Serial.print((char)mybyte);
                         myFile2.print((char)mybyte);
                         if(mybyte=='0')
                         {//fifth zero check -6
                             while(Serial.available()==0);
                             mybyte=(char)Serial.read(); 
                             Serial.print((char)mybyte);
                             myFile2.print((char)mybyte);
                             if(mybyte=='0')
                             {//Sixth zero check - 7
                                 while(Serial.available()==0);
                                 mybyte=(char)Serial.read(); 
                                 Serial.print((char)mybyte);
                                 myFile2.print((char)mybyte);
                                 if(mybyte=='0')
                                   {//Seventh zero check -8
                                       while(Serial.available()==0);
                                       mybyte=(char)Serial.read(); 
                                       Serial.print((char)mybyte);
                                       myFile2.print((char)mybyte);
                                       if(mybyte=='1')
                                         {//9th as 1 check -9
                                             while(Serial.available()==0);
                                             mybyte=(char)Serial.read(); 
                                             Serial.print((char)mybyte);
                                             myFile2.print((char)mybyte);
                                             if(mybyte=='F')
                                               {//10th as F check -10
                                                   while(Serial.available()==0);
                                                   mybyte=(char)Serial.read(); 
                                                   Serial.print((char)mybyte);
                                                   myFile2.print((char)mybyte);
                                                   if(mybyte=='F')
                                                     {//11th as F check -11
                                                        // while(Serial.available()==0);
                                                        // mybyte=(char)Serial.read(); 
                                                        // Serial.print((char)mybyte);
                                                        // myFile2.print((char)mybyte);
                                                         my_file_complete=true;
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
 
} // function ends


