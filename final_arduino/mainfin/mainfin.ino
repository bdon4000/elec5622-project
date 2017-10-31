#include "all.h"

unsigned long time_limit=0;
void setup() 
{
  hall_Init();
  Pulse_Init();
  GPS_Init();
  SD_Init();
//  tft.begin(identifier);
}

void loop() 
{
  Pulse_Allot();
  GPS_Allot();
  if(millis()-time_limit>5000)
  {
    GPS_SD_Write();
    PulseSensor_SD_Write();
    hall_SD_Write();
    time_limit = millis();

  }
}
