#include <SPI.h>              //Library for using SPI Communication 
#include <mcp2515.h>          //Library for using CAN Communication (https://github.com/autowp/arduino-mcp2515/)
 
struct can_frame canMsg; 
MCP2515 mcp2515(10);                 // SPI CS Pin 10
 
#include <Servo.h>
Servo servo1;
void setup(){
  servo1.attach(5);
  pinMode(6,1);
  Serial.begin(115200);                //Begins Serial Communication at 9600 baudrate
  SPI.begin();     
                    //Begins SPI communication

  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();                  //Sets CAN at normal mode
  Serial.println("------- CAN Read ----------");
  Serial.println("ID = 0E3  DLC   DATA");

 }
 
 
void loop()
{ 

  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK){
    if(canMsg.can_id==0x0E3){
      for (int i = 0; i<canMsg.can_dlc; i++)  {  // print the data
        int x = canMsg.data[i];
       if(x==0){
          servo1.write(180);}
       else{
          servo1.write(0);}
       
        Serial.print(canMsg.data[i],HEX);
        Serial.print(" ");
    
      }
    Serial.println();     }
}}