#include <EtherCard.h>
 
// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x73,0x49,0x69,0x2D,0x30,0x61 };
static byte myip[] = {192,168,1,20};
static byte mygw[] = {192,168,1,1};
static byte mydns[] = {59,179,243,70};
static byte mynetmask[] = {255,255,255,0};
 
byte Ethernet::buffer[1000];
//BufferFiller bfill;
 
void setup () {
  Serial.begin(57600);
  Serial.println("in setup");
  if (ether.begin(sizeof Ethernet::buffer, mymac,8) == 0)
    Serial.println(F("Failed to access Ethernet controller"));
  
  
  ether.staticSetup(myip,mygw,mydns,mynetmask);
  
    ether.printIp("MY IP:\t",ether.myip);
    ether.printIp("Netmask:\t",ether.netmask);
    ether.printIp("gwip:\t",ether.gwip);
    ether.printIp("dnsip:\t",ether.dnsip);
    
  Serial.println("outta setup");
}
 
void loop () {
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);


  if (pos)  // check if valid tcp data is received
    {
      BufferFiller bfill = ether.tcpOffset();
      bfill.emit_p(PSTR("<h1>hello</h1>"));
      ether.httpServerReply(bfill.position());
        
    }

}
