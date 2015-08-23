

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"



RF24 radio(9,10);
const long interval = 5000;   
unsigned long previousMillis = 0;   
  unsigned long currentMillis =0;






const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };


typedef enum { role_ping_out = 1, role_pong_back } role_e;


const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};


role_e role;

void setup(void)
{
 
  
 
  
  pinMode(2, OUTPUT);
  
  digitalWrite(2,LOW);
   pinMode(6, OUTPUT);

digitalWrite(6,0);
 

   



 

  
  printf_begin();
  printf("\n\rRF24/examples/pingpair/\n\r");
  printf("ROLE: %s\n\r",role_friendly_name[role]);

 

  radio.begin();

  
  radio.setRetries(15,15);

 
  radio.setPayloadSize(8);

 
  if ( role == role_ping_out )
  {
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]);
  }
  else
  {
    radio.openWritingPipe(pipes[1]);
    radio.openReadingPipe(1,pipes[0]);
  }

 

  radio.startListening();

  

  radio.printDetails();
}

void loop(void)
{
  unsigned long currentMillis = millis();

  

  

   
    if ( radio.available() )
    {
    
      unsigned long got_time;
      bool done = false;
      while (!done)
      {
        
        done = radio.read( &got_time, sizeof(unsigned long) );

       
        printf("Got payload %lu...",got_time);



      }

      
   previousMillis = currentMillis;   
     
      radio.startListening();
    }



    
  if(currentMillis - previousMillis >= interval) {

digitalWrite(6,0);

  
  }
  else{digitalWrite(6,1);}
Serial.print(currentMillis - previousMillis);      printf("--.\n\r");
delay(50);
  
    
  }


