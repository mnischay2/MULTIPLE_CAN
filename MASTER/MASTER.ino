#include <SPI.h>          //Library for using SPI Communication 
#include <mcp2515.h>      //Library for using CAN Communication (https://github.com/autowp/arduino-mcp2515/)
 
struct can_frame canMsg1;
struct can_frame canMsg2;
struct can_frame canMsg3;
struct can_frame canMsg4;
MCP2515 mcp2515(10);
int s1=4 ;
int s2=5 ;
int s3=6 ;
//int s4=A0 ;
 
void setup(){
  canMsg1.can_id  = 0x0F6;           //CAN id as 0x036
  canMsg1.can_dlc = 1;               //CAN data length as 8

  canMsg2.can_id  = 0x0FF;           //CAN id as 0x036
  canMsg2.can_dlc = 1;               //CAN data length as 8

  canMsg3.can_id  = 0x0B9;           //CAN id as 0x036
  canMsg3.can_dlc = 1;               //CAN data length as 8

  canMsg4.can_id  = 0x0E3;           //CAN id as 0x036
  canMsg4.can_dlc = 1;       
          //CAN data length as 8
  pinMode(s1,INPUT_PULLUP);
  pinMode(s2,INPUT_PULLUP);
  pinMode(s3,INPUT_PULLUP);
  pinMode(A0,INPUT);
  
  while (!Serial);
  Serial.begin(115200);
 
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();
  Serial.println("Example: Write to CAN");

}
 
 
void loop(){
  int h=0; 
  int i=0; 
  int j=0; 
  int s=digitalRead(s1);
  int t=digitalRead(s2);
  int u=digitalRead(s3);
  int v=analogRead(A0)/3;
  if (s==1){
    h=0;
   canMsg1.data[0] = 0x00;
  }

  else{
    h=1;
  canMsg1.data[0] = 0x01;  
  }

  if (t==1){
    i=0;
   canMsg2.data[0] = 0x00;
  }

  else{
    i=1;
  canMsg2.data[0] = 0x01;  
  }

  if (u==1){
    j=0;
   canMsg4.data[0] = 0x00;
  }

  else{
    j=1;
  canMsg4.data[0] = 0x01;  
  }

  canMsg3.data[0] = v;  
  

  Serial.print("switch 1 state= ");
  Serial.println(h);
  Serial.print("switch 2 state= ");
  Serial.println(i);
  Serial.print("switch 3 state= ");
  Serial.println(j);
  Serial.print("potentiometer state= ");
  Serial.println(v);
  mcp2515.sendMessage(&canMsg1);     //Sends the CAN message
  mcp2515.sendMessage(&canMsg2);     //Sends the CAN message
  mcp2515.sendMessage(&canMsg3);     //Sends the CAN message
  mcp2515.sendMessage(&canMsg4);     //Sends the CAN message
 // delay(1000);
  }