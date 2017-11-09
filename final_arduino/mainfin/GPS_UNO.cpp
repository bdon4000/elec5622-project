#include "all.h"
//此处为了兼容其他的多串口Arduino板子
#define GpsSerial Serial2 
#define DebugSerial Serial2
int L = 13; //LED指示灯引脚
String GPS_data = "";
struct GPS_Save_Data
{
  char GPS_Buffer[80];
  bool isGetData;   //是否获取到GPS数据
  bool isParseData; //是否解析完成
  char UTCTime[11];   //UTC时间
  char latitude[11];    //纬度
  char N_S[2];    //N/S
  char longitude[12];   //经度
  char E_W[2];    //E/W
  bool isUsefull;   //定位信息是否有效
  char altitude[11];
} Save_Data;

const unsigned int gpsRxBufferLength = 600;
char gpsRxBuffer[gpsRxBufferLength];
unsigned int ii = 0;
void errorLog(int num);
void printGpsBuffer();
void parseGpsBuffer();
void gpsRead();
void clrGpsRxBuffer(void);
void GPS_Init();
void GPS_Allot();

void GPS_SD_Write()
{
      SD_Write("test.txt",GPS_data); 
}
void GPS_Init()  //初始化内容
{
  GpsSerial.begin(9600);      //定义波特率9600，和我们店铺的GPS模块输出的波特率一致
  DebugSerial.begin(9600);
//  DebugSerial.println("ILoveMCU.taobao.com");
  DebugSerial.println("GPS Wating...");

  Save_Data.isGetData = false;
  Save_Data.isParseData = false;
  Save_Data.isUsefull = false;
}

void GPS_Allot()   //主循环
{
  gpsRead();  //获取GPS数据
  parseGpsBuffer();//解析GPS数据
  printGpsBuffer();//输出解析后的数据
  // DebugSerial.println("\r\n\r\nloop\r\n\r\n");
}

void errorLog(int num)
{
  DebugSerial.print("ERROR");
  DebugSerial.println(num);
  //while (1)
  //{
  //  digitalWrite(L, HIGH);
  //  delay(300);
  //  digitalWrite(L, LOW);
  //  delay(300);
 // }
}

void printGpsBuffer()
{
  String GPS_data_temp="";
  
  if (Save_Data.isParseData)
  {
    Save_Data.isParseData = false;
    
    DebugSerial.print("Save_Data.UTCTime = ");
    DebugSerial.println(Save_Data.UTCTime);

    if(Save_Data.isUsefull)
    {
      Save_Data.isUsefull = false;
      DebugSerial.print("Save_Data.latitude = ");
      DebugSerial.println(Save_Data.latitude);
      DebugSerial.print("Save_Data.N_S = ");
      DebugSerial.println(Save_Data.N_S);
      DebugSerial.print("Save_Data.longitude = ");
      DebugSerial.println(Save_Data.longitude);
      DebugSerial.print("Save_Data.E_W = ");
      DebugSerial.println(Save_Data.E_W);
      DebugSerial.print("Save_data.altitude = ");
      DebugSerial.println(Save_Data.altitude);
      
      GPS_data_temp +="$GPGGA,";                           //存入SD卡的数据
      GPS_data_temp += Save_Data.UTCTime;  
      GPS_data_temp += ",";
      GPS_data_temp += Save_Data.latitude;
      GPS_data_temp += ",";
      GPS_data_temp += Save_Data.N_S;
      GPS_data_temp += ",";
      GPS_data_temp += Save_Data.longitude;
      GPS_data_temp +=",";
      GPS_data_temp +=Save_Data.E_W;
      GPS_data_temp +=",";
      GPS_data_temp +=Save_Data.altitude;
      GPS_data = GPS_data_temp;
      GPS_data_temp  = "";
    }
    else
    {
      DebugSerial.println("GPS DATA is not usefull!");
    }
    
  }
}

void parseGpsBuffer()
{
  char *subString;
  char *subStringNext;
  if (Save_Data.isGetData)
  {
    Save_Data.isGetData = false;
    DebugSerial.println("**************");
    DebugSerial.println(Save_Data.GPS_Buffer);
    
    for (int i = 0 ; i <= 9 ; i++)
    {
      if (i == 0)
      {
        if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)
          errorLog(1);  //解析错误
      }
      else
      {
        subString++;
        if ((subStringNext = strstr(subString, ",")) != NULL)
        {
          char usefullBuffer[2]; 
          switch(i)
          {
            case 1:memcpy(Save_Data.UTCTime, subString, subStringNext - subString);break; //获取UTC时间
            case 2:memcpy(Save_Data.latitude, subString, subStringNext - subString);break;  //获取纬度信息
            case 3:memcpy(Save_Data.N_S, subString, subStringNext - subString);break; //获取N/S
            case 4:memcpy(Save_Data.longitude, subString, subStringNext - subString);break; //获取经度信息
            case 5:memcpy(Save_Data.E_W, subString, subStringNext - subString);break; //获取E/W
            case 9:memcpy(Save_Data.altitude, subString, subStringNext - subString);break; //获取海拔


            default:break;
          }

          subString = subStringNext;
          Save_Data.isParseData = true;
          //if(usefullBuffer[0] == '1')
            Save_Data.isUsefull = true;
          //else if(usefullBuffer[0] == '3' )
            //Save_Data.isUsefull = false;

        }
        //else
        //{
          //errorLog(2);  //解析错误
        //}
      }


    }
  }
}


void gpsRead() {
  while (GpsSerial.available())
  {
    gpsRxBuffer[ii++] = GpsSerial.read();
    if (ii == gpsRxBufferLength)clrGpsRxBuffer();
  }

  char* GPS_BufferHead;
  char* GPS_BufferTail;
  if ((GPS_BufferHead = strstr(gpsRxBuffer, "$GPGGA,")) != NULL || (GPS_BufferHead = strstr(gpsRxBuffer, "$GNGGA,")) != NULL )
  {
    if (((GPS_BufferTail = strstr(GPS_BufferHead, "\r\n")) != NULL) && (GPS_BufferTail > GPS_BufferHead))
    {
      memcpy(Save_Data.GPS_Buffer, GPS_BufferHead, GPS_BufferTail - GPS_BufferHead);
      Save_Data.isGetData = true;
      clrGpsRxBuffer();
    }
  }
}

void clrGpsRxBuffer(void)
{
  memset(gpsRxBuffer, 0, gpsRxBufferLength);      //清空
  ii = 0;
}

