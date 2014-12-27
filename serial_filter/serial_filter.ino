volatile byte mybyte;
boolean my_file_complete=false;
void setup()
{
Serial.begin(9600);
Serial.println("serial started");
}


void loop()
{
check_endof_file();
do_other_works();
}

void check_endof_file()
{
    while(Serial.available()==0);
    mybyte=(char)Serial.read(); 
    Serial.print((char)mybyte);
    if(mybyte==':')
      { // Colon check - 1
         while(Serial.available()==0);
         mybyte=(char)Serial.read();
         Serial.print((char)mybyte);
         if(mybyte=='0')
         {//first zero check -2
            while(Serial.available()==0);
            mybyte=(char)Serial.read();
            Serial.print((char)mybyte);
            if(mybyte=='0')
            {//second zero check -3
                 while(Serial.available()==0);
                 mybyte=(char)Serial.read(); 
                 Serial.print((char)mybyte);
                 if(mybyte=='0')
                 {//Third zero check -4
                     while(Serial.available()==0);
                     mybyte=(char)Serial.read(); 
                     Serial.print((char)mybyte);
                     if(mybyte=='0')
                     {//Fourth zero check -5 
                         while(Serial.available()==0);
                         mybyte=(char)Serial.read(); 
                         Serial.print((char)mybyte);
                         if(mybyte=='0')
                         {//fifth zero check -6
                             while(Serial.available()==0);
                             mybyte=(char)Serial.read(); 
                             Serial.print((char)mybyte);
                             if(mybyte=='0')
                             {//Sixth zero check - 7
                                 while(Serial.available()==0);
                                 mybyte=(char)Serial.read(); 
                                 Serial.print((char)mybyte);
                                 if(mybyte=='0')
                                   {//Seventh zero check -8
                                       while(Serial.available()==0);
                                       mybyte=(char)Serial.read(); 
                                       Serial.print((char)mybyte);
                                       if(mybyte=='1')
                                         {//9th as 1 check -9
                                             while(Serial.available()==0);
                                             mybyte=(char)Serial.read(); 
                                             Serial.print((char)mybyte);
                                             if(mybyte=='F')
                                               {//10th as F check -10
                                                   while(Serial.available()==0);
                                                   mybyte=(char)Serial.read(); 
                                                   Serial.print((char)mybyte);
                                                   if(mybyte=='F')
                                                     {//11th as F check -11
                                                        // while(Serial.available()==0);
                                                        // mybyte=(char)Serial.read(); 
                                                         Serial.print((char)mybyte);
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
 
if(my_file_complete==true)
  {
    my_file_complete=false;
    Serial.println("magic String recieved");
  }
} // function ends

void do_other_works()
{
  
}


