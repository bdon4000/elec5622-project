#include "all.h"
double f1=0;
double f2=0;
double time_count0 =0;
double time_count1 = 0;
String data_string1=" duration1 is 0ms, f2 is 0HZ, v2 is 0r/min";
String data_string2=" duration2 is 0ms, f2 is 0HZ, v2 is 0r/min";
void INT0_Ser()
{
  
  static unsigned char count_T0 = 0;
  static double time_sub0 = 0,/*time_count0 = 0,*/v1=0,duration1=0;
  //noInterrupts(); 
  count_T0++;
    duration1=millis()-time_count0;
  if(duration1>100)
  {
  time_sub0 += millis()-time_count0;
  time_count0 = millis();
  duration1=0;
  }
  else
  {
   count_T0--;
    duration1=0;
  }
  
  if(count_T0==1)
  {
     duration1 = time_sub0;
     f1=60000/duration1;
     data_string1=" duration1 is "+String(duration1)+"ms,"+" cadence is "+String(f1)+/*"HZ,"+" v1 is "+String(v1)+*/" r/min";
    Serial.println(data_string1); 
    time_sub0 = 0;
    count_T0 = 0;
  }
  //interrupts();
}
void INT1_Ser()
{
  //noInterrupts();
  static unsigned char count_T1 = 0;
  static double time_sub1 = 0,/*time_count1 = 0,*/v2=0,duration2=0;
  
  count_T1++;
  duration2=millis()-time_count1;
  if(duration2>100)
  {
  time_sub1 += millis()-time_count1;
  time_count1 = millis();
  duration2=0;
  }
  else
  {
    count_T1--;
    duration2=0;
  }
  
  if(count_T1==1)
  {
     duration2 = time_sub1;
     
     f2=128.173*60/duration2;
     v2 = duration2*60;
     data_string2=" duration2 is "+String(duration2)+"ms,"+" speed is "+String(f2)+"km/h"/*+" v2 is "+String(v2)+" r/min"*/;
    Serial.println(data_string2); 
    time_sub1 = 0;
    count_T1 = 0;
  }
  //interrupts();
}
void hall_Init()
{
  Serial.begin(9600); //串口波特率为9600
  attachInterrupt(INT5_pin18, INT0_Ser, RISING);

  attachInterrupt(INT3_pin20, INT1_Ser, RISING);
    if((millis()-time_count1)>3000)
  {f2=0;}
  Serial.println("begin"); 
}
void hall_SD_Write()
{
   SD_Write("test.txt",data_string1);
   SD_Write("test.txt",data_string2); //速度数据写入SD卡中Speed.txt文件
}

